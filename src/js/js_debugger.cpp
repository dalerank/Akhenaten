#include "js_debugger.h"

#include "mujs/jsi.h"       // js_State internals
#include "mujs/jsvalue.h"   // js_Value, js_Object, js_Property, js_Environment
#include "mujs/jsrun.h"     // js_Environment

#include "core/log.h"
#include "core/variant.h"

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <numeric>
#include <sstream>

#ifdef _WIN32
#pragma comment(lib, "ws2_32.lib")
typedef int socklen_t;
#endif

MujsDebugger g_mujs_debugger;

// ─────────────────────────────────────────────────────────────────────────────
// Platform helpers
// ─────────────────────────────────────────────────────────────────────────────

static bool sock_platform_init() {
#ifdef _WIN32
    WSADATA wd;
    return WSAStartup(MAKEWORD(2, 2), &wd) == 0;
#else
    return true;
#endif
}

static void sock_platform_cleanup() {
#ifdef _WIN32
    WSACleanup();
#endif
}

cstring json_jstr(const cstring &s) {
    cstring r = "\"";
    for (unsigned char c : s) {
        switch (c) {
        case '"':  r += "\\\""; break;
        case '\\': r += "\\\\"; break;
        case '\n': r += "\\n";  break;
        case '\r': r += "\\r";  break;
        case '\t': r += "\\t";  break;
        default:
            if (c < 0x20) {
                char buf[8];
                snprintf(buf, sizeof(buf), "\\u%04x", c);
                r += buf;
            } else {
                r += static_cast<char>(c);
            }
            break;
        }
    }
    r += '"';
    return r;
}

static cstring bvariant_to_json_value(const bvariant &v) {
    char buffer[64] = { 0 };
    switch (v.value_type()) {
    case bvariant::etype_none: return "null";
    case bvariant::etype_bool: return v.as_bool() ? "true" : "false";
    case bvariant::etype_int32:
        snprintf(buffer, sizeof(buffer), "%d", v.as_int32());
        return buffer;
    case bvariant::etype_uint32:
        snprintf(buffer, sizeof(buffer), "%u", v.as_uint32());
        return buffer;
    case bvariant::etype_uint64:
        snprintf(buffer, sizeof(buffer), "%llu", (unsigned long long)v.as_uint64());
        return buffer;
    case bvariant::etype_u16:
        snprintf(buffer, sizeof(buffer), "%u", (unsigned)v.as_u16());
        return buffer;
    case bvariant::etype_float:
        snprintf(buffer, sizeof(buffer), "%g", v.as_float());
        return buffer;
    case bvariant::etype_str: return json_jstr(cstring(v.as_str().c_str()));
    case bvariant::etype_ptr: return "null";
    case bvariant::etype_vec2i:
    {
        const vec2i &p = v.as_vec2i();
        snprintf(buffer, sizeof(buffer), "[%d,%d]", p.x, p.y);
        return buffer;
    }
    case bvariant::etype_tile2i:
    {
        const tile2i &t = v.as_tile2i();
        snprintf(buffer, sizeof(buffer), "[%d,%d]", t.x(), t.y());
        return buffer;
    }
    case bvariant::etype_grid_area:
    {
        const grid_area &a = v.as_grid_area();
        snprintf(buffer, sizeof(buffer), "[%d,%d,%d,%d]", a.tmin_x, a.tmin_y, a.tmax_x, a.tmax_y);
        return buffer;
    }
    default:
        return "null";
    }
}

cstring json_from_bvariant_map(const bvariant_map &m, pcstr raw_tail_key = nullptr, const cstring &raw_tail_value = "") {
    cstring out = "{";
    bool first = true;
    for (const auto &kv : m.values) {
        if (!first) out += ",";
        first = false;
        out += json_jstr(kv.first.c_str());
        out += ":";
        out += bvariant_to_json_value(kv.second);
    }

    if (raw_tail_key && !raw_tail_value.empty()) {
        out += ",";
        out += json_jstr(raw_tail_key);
        out += ":";
        out += raw_tail_value;
    }

    out += "}";
    return out;
}


// ─────────────────────────────────────────────────────────────────────────────
// Public API
// ─────────────────────────────────────────────────────────────────────────────

void MujsDebugger::start(js_State *J, int port) {
    if (running_) {
        return;
    }

    J_ = J;
    port_ = port;
    running_ = true;
    server_thread_ = std::thread([this, port] () { server_loop(port); });
}

void MujsDebugger::stop() {
    running_ = false;

    if (server_sock_ != JS_DBG_SOCK_INVALID) {
        js_dbg_sock_close(server_sock_);
        server_sock_ = JS_DBG_SOCK_INVALID;
    }

    if (client_sock_ != JS_DBG_SOCK_INVALID) {
        js_dbg_sock_close(client_sock_);
        client_sock_ = JS_DBG_SOCK_INVALID;
    }

    // Unblock game thread if it is waiting
    {
        std::lock_guard<std::mutex> lock(mtx_);
        paused_ = false;
        step_mode_ = DebugStepMode::None;
    }
    cv_.notify_all();

    if (server_thread_.joinable()) {
        server_thread_.join();
    }
    sock_platform_cleanup();
}

void MujsDebugger::update_state(js_State *J) {
    // Called after VM restart (game thread, no lock needed for J_)
    J_ = J;
}

// ─────────────────────────────────────────────────────────────────────────────
// Hook — called from OP_LINE (game thread)
// ─────────────────────────────────────────────────────────────────────────────

void MujsDebugger::on_line(js_State *J, const char *file, int line) {
    if (!running_) {
        return;
    }

    if (client_sock_ == JS_DBG_SOCK_INVALID) {
        return; // no client yet
    }

    J_ = J; // keep pointer current for inspection

    if (verbose_) {
        logs::info("JS DBG trace: %s:%d", file ? file : "<null>", line);
    }

    if (!should_break(file, line)) {
        return;
    }

    logs::info("JS DBG stopped: %s:%d", file ? file : "<null>", line);
    send_stopped_event("breakpoint", file, line);
    block_until_command();
}

bool MujsDebugger::should_break(const char *file, int line) {
    std::lock_guard<std::mutex> lock(mtx_);

    if (step_mode_ == DebugStepMode::Pause || step_mode_ == DebugStepMode::StepIn) {
        step_mode_ = DebugStepMode::None;
        return true;
    }

    if (step_mode_ == DebugStepMode::StepOver) {
        int cur_depth = J_ ? J_->tracetop : 0;
        if (cur_depth <= step_depth_) {
            bool same = (step_start_line_ == line && step_start_file_ == (file ? file : ""));
            if (!same) {
                step_mode_ = DebugStepMode::None;
                return true;
            }
        }

        return false;
    }

    if (step_mode_ == DebugStepMode::StepOut) {
        int cur_depth = J_ ? J_->tracetop : 0;
        if (cur_depth < step_depth_) {
            step_mode_ = DebugStepMode::None;
            return true;
        }

        return false;
    }

    // Breakpoints
    for (const auto &bp : breakpoints_) {
        if (bp.line == line && file_matches(file, bp.file)) {
            return true;
        }
    }

    return false;
}

void MujsDebugger::block_until_command() {
    std::unique_lock<std::mutex> lock(mtx_);
    paused_ = true;

    cv_.wait(lock, [this] { return !paused_ || !running_; });
}

// ─────────────────────────────────────────────────────────────────────────────
// Network — server thread
// ─────────────────────────────────────────────────────────────────────────────

void MujsDebugger::server_loop(int port) {
    if (!sock_platform_init()) {
        logs::info("JS Debugger: socket platform init failed");
        return;
    }

    server_sock_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_sock_ == JS_DBG_SOCK_INVALID) {
        logs::info("JS Debugger: socket() failed");
        sock_platform_cleanup();
        return;
    }

    int opt = 1;
    setsockopt(server_sock_, SOL_SOCKET, SO_REUSEADDR,
        reinterpret_cast<const char *>(&opt), sizeof(opt));

    sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(static_cast<unsigned short>(port));
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_sock_, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) != 0) {
        logs::info("JS Debugger: bind() failed on port %d", port);
        js_dbg_sock_close(server_sock_);
        server_sock_ = JS_DBG_SOCK_INVALID;
        sock_platform_cleanup();
        return;
    }

    listen(server_sock_, 1);
    logs::info("JS Debugger: listening on TCP port %d — attach with VSCode (mujs type)", port);

    while (running_) {
        sockaddr_in client_addr = {};
        socklen_t   client_len = sizeof(client_addr);

        sock_t csock = accept(server_sock_,
            reinterpret_cast<sockaddr *>(&client_addr),
            &client_len);
        if (csock == JS_DBG_SOCK_INVALID) {
            if (!running_) break;
            continue;
        }

        client_sock_ = csock;
        logs::info("JS Debugger: VSCode client connected");

        handle_client();

        js_dbg_sock_close(csock);
        client_sock_ = JS_DBG_SOCK_INVALID;
        logs::info("JS Debugger: VSCode client disconnected");

        // Ensure game thread is not stuck after client disconnect
        {
            std::lock_guard<std::mutex> lock(mtx_);
            step_mode_ = DebugStepMode::None;
            paused_ = false;
        }
        cv_.notify_all();
    }

    if (server_sock_ != JS_DBG_SOCK_INVALID) {
        js_dbg_sock_close(server_sock_);
        server_sock_ = JS_DBG_SOCK_INVALID;
    }

    sock_platform_cleanup();
}

// DAP packet framing: "Content-Length: N\r\n\r\n<body>"
bool MujsDebugger::send_packet(const cstring &json) {
    if (client_sock_ == JS_DBG_SOCK_INVALID) {
        return false;
    }

    cstring packet;
    packet += "Content-Length: ";
    packet += bstring32(json.size());
    packet += "\r\n\r\n";
    packet += json;

    int total = static_cast<int>(packet.size());
    int sent = 0;

    while (sent < total) {
        int n = send(client_sock_, packet.c_str() + sent, total - sent, 0);
        if (n <= 0) {
            return false;
        }
        sent += n;
    }

    return true;
}

bool MujsDebugger::recv_packet(cstring &out) {
    // Read header byte-by-byte until \r\n\r\n
    cstring header;
    char c;

    while (true) {
        int n = recv(client_sock_, &c, 1, 0);
        if (n <= 0) return false;
        header += c;
        size_t sz = header.size();
        if (sz >= 4) {
            // cstring::substr(start,end) needs end position; -1 is clamped and gives empty string
            cstring tail = header.substr(sz - 4, sz);
            if (tail == "\r\n\r\n") {
                break;
            }
        }
    }

    auto pos = header.find("Content-Length: ");
    if (pos == std::string::npos) {
        return false;
    }
    size_t sz = header.size();
    int content_len = std::stoi(header.substr(pos + 16, sz).c_str());

    out.resize(content_len);
    int received = 0;
    while (received < content_len) {
        int n = recv(client_sock_, &out[received], content_len - received, 0);
        if (n <= 0) {
            return false;
        }
        received += n;
    }
    return true;
}

void MujsDebugger::handle_client() {
    cstring packet;
    while (running_ && recv_packet(packet)) {
        handle_request(packet);
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// DAP messaging
// ─────────────────────────────────────────────────────────────────────────────

void MujsDebugger::send_event(const cstring &event, const cstring &body) {
    send_packet(json_from_bvariant_map({
        { "seq", next_seq() },
        { "type", "event" },
        { "event", event }
    }, "body", body));
}

void MujsDebugger::send_response(int req_seq, const cstring &command, bool success, const cstring &body) {
    send_packet(json_from_bvariant_map({
        { "seq", next_seq() },
        { "type", "response" },
        { "request_seq", req_seq },
        { "success", success },
        { "command", command }
    }, "body", body));
}

void MujsDebugger::send_stopped_event(pcstr reason, pcstr file, int line) {
    object_ref_map_.clear();
    next_variable_ref_ = 1000;

    send_event("stopped", json_from_bvariant_map({
        { "reason", reason },
        { "description", cstring("Paused on ") + reason },
        { "threadId", 1 },
        { "allThreadsStopped", true }
    }));
}

// ─────────────────────────────────────────────────────────────────────────────
// Variable / stack inspection
// (called from server thread; game thread is blocked on cv_.wait — safe)
// ─────────────────────────────────────────────────────────────────────────────

// Convert a js_Value to a human-readable JSON string (the "value" DAP field).
static cstring js_value_display(js_State *J, const js_Value *v) {
    char buf[64];
    switch (static_cast<js_Type>(v->type)) {
    case JS_TUNDEFINED: return json_jstr("undefined");
    case JS_TNULL:      return json_jstr("null");
    case JS_TBOOLEAN:   return json_jstr(v->u.boolean ? "true" : "false");
    case JS_TNUMBER:
        snprintf(buf, sizeof(buf), "%g", v->u.number);
        return json_jstr(buf);
    case JS_TSHRSTR:    return json_jstr(cstring("\"") + v->u.shrstr + "\"");
    case JS_TLITSTR:    return json_jstr(cstring("\"") + (v->u.litstr ? v->u.litstr : "") + "\"");
    case JS_TMEMSTR:    return json_jstr(cstring("\"") + (v->u.memstr ? v->u.memstr->p : "") + "\"");
    case JS_TOBJECT:
        if (!v->u.object) return json_jstr("null");
        switch (v->u.object->type) {
        case JS_CARRAY:    return json_jstr("[...]");
        case JS_CFUNCTION:
        case JS_CCFUNCTION:return json_jstr("[Function]");
        default:           return json_jstr("{...}");
        }
    default: return json_jstr("<unknown>");
    }
}

static const char *js_value_type(const js_Value *v) {
    switch (static_cast<js_Type>(v->type)) {
    case JS_TUNDEFINED: return "undefined";
    case JS_TNULL:      return "null";
    case JS_TBOOLEAN:   return "boolean";
    case JS_TNUMBER:    return "number";
    case JS_TSHRSTR:
    case JS_TLITSTR:
    case JS_TMEMSTR:    return "string";
    case JS_TOBJECT:    return "object";
    default:            return "unknown";
    }
}

cstring MujsDebugger::build_evaluate_response(const cstring &expression, int /*frame_id*/) {
    if (!J_ || !J_->E) {
        return "{\"result\":\"\",\"variablesReference\":0}";
    }

    // Trim
    size_t start = expression.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) {
        return "{\"result\":\"\\\"\\\"\",\"variablesReference\":0}";
    }

    size_t end = expression.find_last_not_of(" \t\r\n");
    cstring expr = expression.substr(start, end - start + 1);

    // Only support simple identifier (one word)
    if (expr.empty()) {
        return "{\"result\":\"\\\"\\\"\",\"variablesReference\":0}";
    }

    for (size_t i = 0; i < expr.size(); ++i) {
        char c = expr.data()[i];
        bool ok = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || c == '$' || (i > 0 && c >= '0' && c <= '9');
        if (!ok) {
            return "{\"result\":\"" + json_jstr("Unsupported expression (use a variable name)") + "\",\"variablesReference\":0}";
        }
    }

    const char *name = expr.c_str();
    js_Property *prop = nullptr;
    int parent_ref = 0;

    js_Environment *env = J_->E;
    prop = env->variables->vgetproperty(name);
    if (prop) parent_ref = 1;
    else {
        while (env->outer) env = env->outer;
        prop = env->variables->vgetproperty(name);
        if (prop) parent_ref = 2;
    }

    if (!prop) {
        return "{\"result\":" + json_jstr("undefined") + ",\"variablesReference\":0}";
    }

    const js_Value *v = &prop->value;
    int ref = 0;
    if (static_cast<js_Type>(v->type) == JS_TOBJECT && v->u.object) {
        ref = next_variable_ref_++;
        object_ref_map_[ref] = { parent_ref, expr };
    }

    cstring result = json_from_bvariant_map({ { "variablesReference", ref } }, 
                                                "result", js_value_display(J_, v));

    return result;
}

cstring MujsDebugger::build_stack_trace_json(int levels) {
    if (!J_ || J_->tracetop < 0) {
        return "{\"stackFrames\":[],\"totalFrames\":0}";
    }

    int top = J_->tracetop;
    int count = (levels <= 0 || levels > top + 1) ? (top + 1) : levels;

    cstring frames = "[";
    for (int i = 0; i < count; ++i) {
        int idx = top - i;
        if (idx < 0) {
            break;
        }

        const js_StackTrace &t = J_->trace[idx];
        pcstr name = t.name ? t.name : "<anonymous>";
        pcstr file = t.file ? t.file : "<unknown>";
        int line = t.line > 0 ? t.line : 1;

        if (i > 0) {
            frames += ",";
        }

        cstring source_json = json_from_bvariant_map({
            { "name", basename_of(file) },
            { "path", file }
        });
        frames += json_from_bvariant_map({
            { "id", i },
            { "name", name },
            { "line", line },
            { "column", 0 }
        }, "source", source_json);
    }
    frames += "]";

    return json_from_bvariant_map({
        { "totalFrames", count }
    }, "stackFrames", frames);
}

// variablesReference encoding:
//   1 = Local  (J_->E)
//   2 = Global (walk up to J_->GE)
cstring MujsDebugger::build_scopes_json(int /*frame_id*/) {
    cstring local = json_from_bvariant_map({
        { "name", "Local" },
        { "variablesReference", 1 },
        { "expensive", false }
    });
    cstring global = json_from_bvariant_map({
        { "name", "Global" },
        { "variablesReference", 2 },
        { "expensive", true }
    });
    return "{\"scopes\":[" + local + "," + global + "]}";
}

js_Object *MujsDebugger::get_object_for_ref(int var_ref) {
    if (!J_ || !J_->E) {
        return nullptr;
    }

    if (var_ref == 1) {
        return J_->E->variables;
    }

    if (var_ref == 2) {
        js_Environment *env = J_->E;
        while (env->outer) {
            env = env->outer;
        }

        return env->variables;
    }

    if (var_ref < 1000) {
        return nullptr;
    }

    auto it = object_ref_map_.find(var_ref);
    if (it == object_ref_map_.end()) {
        return nullptr;
    }

    int parent_ref = it->second.first;
    const cstring &name = it->second.second;

    js_Object *parent = get_object_for_ref(parent_ref);
    if (!parent) {
        return nullptr;
    }

    js_Property *prop = parent->vgetproperty(name.c_str());
    if (!prop || static_cast<js_Type>(prop->value.type) != JS_TOBJECT) {
        return nullptr;
    }

    return prop->value.u.object;
}

cstring MujsDebugger::build_variables_json(int var_ref) {
    if (!J_) {
        return "{\"variables\":[]}";
    }

    js_Object *obj = nullptr;

    if (var_ref == 1 || var_ref == 2) {
        js_Environment *env = J_->E;
        if (!env) {
            return "{\"variables\":[]}";
        }

        if (var_ref == 2) {
            while (env->outer) env = env->outer;
        }

        obj = env->variables;
    } else if (var_ref >= 1000) {
        obj = get_object_for_ref(var_ref);
    }

    if (!obj) {
        return "{\"variables\":[]}";
    }

    cstring list = "[";
    bool first = true;
    for (js_Property *p = obj->head; p; p = p->next) {
        if (!p->name) {
            continue;
        }

        if (!first) {
            list += ",";
        }
        first = false;

        const js_Value *v = &p->value;
        int ref = 0;
        if (static_cast<js_Type>(v->type) == JS_TOBJECT && v->u.object) {
            ref = next_variable_ref_++;
            object_ref_map_[ref] = { var_ref, p->name };
        }

        cstring value_display = js_value_display(J_, v);
        list += json_from_bvariant_map({
            { "name", p->name },
            { "type", js_value_type(v) },
            { "variablesReference", ref }
        }, "value", value_display);
    }
    list += "]";
    return "{\"variables\":" + list + "}";
}

// ─────────────────────────────────────────────────────────────────────────────
// DAP request dispatcher
// ─────────────────────────────────────────────────────────────────────────────

void MujsDebugger::handle_request(const cstring &body) {
    cstring cmd = extract_str(body, "command");
    int         req_seq = extract_int(body, "seq");

    if (cmd == "initialize") {
        send_response(req_seq, cmd, true, json_from_bvariant_map({
            { "supportsConfigurationDoneRequest", true },
            { "supportsStepBack", false },
            { "supportsRestartRequest", false },
            { "supportsEvaluateForHovers", false }
        }));
        send_event("initialized", "{}");
    } else if (cmd == "attach" || cmd == "launch") {
        send_response(req_seq, cmd, true);
    } else if (cmd == "configurationDone") {
        send_response(req_seq, cmd, true);
    } else if (cmd == "threads") {
        send_response(req_seq, cmd, true,
            "{\"threads\":[{\"id\":1,\"name\":\"JS Main Thread\"}]}");
    } else if (cmd == "setBreakpoints") {
        cstring src_path = extract_str(body, "path");
        if (src_path.empty()) {
            src_path = extract_str(body, "name");
        }

        // Collect requested line numbers from the "breakpoints" array
        hvector<int, 16> lines;
        int32_t bpos = body.find("\"breakpoints\"");
        if (bpos >= 0) {
            int32_t astart = body.find('[', bpos);
            int32_t aend = (astart >= 0) ? body.find(']', astart) : -1;
            if (astart >= 0 && aend >= 0 && aend >= astart) {
                // cstring::substr(start, end) takes END POSITION; length = end - start
                cstring arr = body.substr(astart, aend + 1);
                int32_t p = 0;
                while ((p = arr.find("\"line\":", p)) >= 0) {
                    p += 7;
                    while (p < arr.size() && arr.data()[p] == ' ') {
                        ++p;
                    }
                    int l = 0;
                    while (p < arr.size() && isdigit(static_cast<unsigned char>(arr.data()[p]))) {
                        l = l * 10 + (arr.data()[p++] - '0');
                    }
                    if (l > 0) lines.push_back(l);
                }
            }
        }

        {
            std::lock_guard<std::mutex> lock(mtx_);
            // Remove old breakpoints for this file
            breakpoints_.erase(
                std::remove_if(breakpoints_.begin(), breakpoints_.end(),
                [&] (const MujsBreakpoint &bp) {
                return file_matches(bp.file.c_str(), src_path.c_str());
            }),
                breakpoints_.end());
            // Add new ones
            for (int l : lines)
                breakpoints_.push_back({ src_path.c_str(), l });
        }

        // Log so user sees add/remove breakpoints (stderr = terminal, logs = log file)
        {
            const char *base = strrchr(src_path.c_str(), '/');
            if (!base) base = strrchr(src_path.c_str(), '\\');
            base = base ? base + 1 : src_path.c_str();
            if (lines.empty()) {
                logs::info("JS DBG setBreakpoints: %s (none)", base);
            } else {
                cstring strlines(frameAlloc());
                char buffer[32] = { 0 };
                int result = std::accumulate(lines.begin(), lines.end(), 0, [&] (auto &p, auto &item) { 
                    strlines += js_itoa(buffer, item);
                    strlines += ",";
                    return 0;
                });
                logs::info("JS DBG setBreakpoints: %s lines [%s]", base, strlines.c_str());
            }
        }

        // Include "source" in each breakpoint so VSCode can bind it to the open document.
        // Without source, VSCode shows "Unbound breakpoint".
        cstring bps = "[";
        for (size_t i = 0; i < lines.size(); ++i) {
            if (i > 0) bps += ",";
            cstring source_json = json_from_bvariant_map({ { "path", src_path } });
            bps += json_from_bvariant_map({
                { "verified", true },
                { "line", lines[i] }
            }, "source", source_json);
        }
        bps += "]";
        send_response(req_seq, cmd, true, "{\"breakpoints\":" + bps + "}");
    } else if (cmd == "stackTrace") {
        int levels = extract_int(body, "levels", 0);
        send_response(req_seq, cmd, true, build_stack_trace_json(levels));
    } else if (cmd == "scopes") {
        int frame_id = extract_int(body, "frameId", 0);
        send_response(req_seq, cmd, true, build_scopes_json(frame_id));
    } else if (cmd == "variables") {
        int var_ref = extract_int(body, "variablesReference", 0);
        send_response(req_seq, cmd, true, build_variables_json(var_ref));
    } else if (cmd == "evaluate") {
        cstring expr = extract_str(body, "expression");
        int frame_id = extract_int(body, "frameId", 0);
        send_response(req_seq, cmd, true, build_evaluate_response(expr, frame_id));
    } else if (cmd == "continue") {
        send_response(req_seq, cmd, true, "{\"allThreadsContinued\":true}");
        {
            std::lock_guard<std::mutex> lock(mtx_);
            step_mode_ = DebugStepMode::None;
            paused_ = false;
        }
        cv_.notify_all();
    } else if (cmd == "next") {
        {
            std::lock_guard<std::mutex> lock(mtx_);
            step_mode_ = DebugStepMode::StepOver;
            step_depth_ = J_ ? J_->tracetop : 0;
            step_start_line_ = J_ ? J_->trace[J_->tracetop].line : 0;
            step_start_file_ = J_ && J_->trace[J_->tracetop].file
                ? J_->trace[J_->tracetop].file : "";
            paused_ = false;
        }
        send_response(req_seq, cmd, true);
        cv_.notify_all();
    } else if (cmd == "stepIn") {
        {
            std::lock_guard<std::mutex> lock(mtx_);
            step_mode_ = DebugStepMode::StepIn;
            paused_ = false;
        }
        send_response(req_seq, cmd, true);
        cv_.notify_all();
    } else if (cmd == "stepOut") {
        {
            std::lock_guard<std::mutex> lock(mtx_);
            step_mode_ = DebugStepMode::StepOut;
            step_depth_ = J_ ? J_->tracetop : 0;
            paused_ = false;
        }
        send_response(req_seq, cmd, true);
        cv_.notify_all();
    } else if (cmd == "pause") {
        {
            std::lock_guard<std::mutex> lock(mtx_);
            step_mode_ = DebugStepMode::Pause;
        }
        send_response(req_seq, cmd, true);
    } else if (cmd == "disconnect") {
        send_response(req_seq, cmd, true);
        {
            std::lock_guard<std::mutex> lock(mtx_);
            step_mode_ = DebugStepMode::None;
            paused_ = false;
        }

        cv_.notify_all();

        if (client_sock_ != JS_DBG_SOCK_INVALID) {
            js_dbg_sock_close(client_sock_);
            client_sock_ = JS_DBG_SOCK_INVALID;
        }
    }
    // ── unknown / unsupported ─────────────────────────────────────────────
    else {
        // Reply with success so VSCode doesn't stall
        send_response(req_seq, cmd, true);
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// JSON helpers
// ─────────────────────────────────────────────────────────────────────────────

MujsDebugger::~MujsDebugger() {
    stop();
}

// Extracts the string value of a JSON key at any nesting level.
// Only handles simple (non-nested) string values.
cstring MujsDebugger::extract_str(const cstring &json, const cstring &key) {
    cstring needle = "\"" + key + "\"";
    auto pos = json.find(needle);
    if (pos == std::string::npos) {
        return {};
    }

    pos += needle.size();
    while (pos < json.size() && (json[pos] == ':' || json[pos] == ' ')) ++pos;
    if (pos >= json.size() || json[pos] != '"') return {};

    ++pos; // skip opening quote
    cstring result;
    while (pos < json.size() && json[pos] != '"') {
        if (json[pos] == '\\' && pos + 1 < json.size()) {
            ++pos;
            switch (json[pos]) {
            case '"':  result += '"';  break;
            case '\\': result += '\\'; break;
            case 'n':  result += '\n'; break;
            case 'r':  result += '\r'; break;
            case 't':  result += '\t'; break;
            default:   result += json[pos]; break;
            }
        } else {
            result += json[pos];
        }
        ++pos;
    }
    return result;
}

int MujsDebugger::extract_int(const cstring &json,
    const cstring &key, int def) {
    cstring needle = "\"" + key + "\"";
    auto pos = json.find(needle);
    if (pos == std::string::npos) {
        return def;
    }

    pos += needle.size();
    while (pos < json.size() && (json[pos] == ':' || json[pos] == ' ')) ++pos;
    if (pos >= json.size()) return def;

    int sign = 1;
    if (json[pos] == '-') { sign = -1; ++pos; }
    if (pos >= json.size() || !isdigit(static_cast<unsigned char>(json[pos]))) {
        return def;
    }

    int val = 0;
    while (pos < json.size() && isdigit(static_cast<unsigned char>(json[pos]))) {
        val = val * 10 + (json[pos++] - '0');
    }
    return sign * val;
}

cstring MujsDebugger::basename_of(pcstr path) {
    if (!path || !*path) {
        return "<unknown>";
    }

    pcstr p = path + strlen(path) - 1;
    while (p > path && *p != '/' && *p != '\\') {
        --p;
    }
    return (*p == '/' || *p == '\\') ? cstring(p + 1) : cstring(path);
}

bool MujsDebugger::file_matches(pcstr trace_file, const xstring &bp_file) {
    if (!trace_file) {
        return false;
    }

    if (bp_file == trace_file) {
        return true;
    }

    // Basename match fallback
    return basename_of(trace_file) == basename_of(bp_file.c_str());
}
