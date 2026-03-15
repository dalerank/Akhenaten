#pragma once

#include "mujs/mujs.h"

struct js_Object;

#include <string>
#include <vector>
#include <map>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <atomic>

// ─── Platform socket types ───────────────────────────────────────────────────
#ifdef _WIN32
#  ifndef WIN32_LEAN_AND_MEAN
#    define WIN32_LEAN_AND_MEAN
#  endif
#  include <winsock2.h>
typedef SOCKET sock_t;
#  define JS_DBG_SOCK_INVALID INVALID_SOCKET
#  define js_dbg_sock_close   closesocket
#else
#  include <sys/socket.h>
#  include <netinet/in.h>
#  include <unistd.h>
typedef int sock_t;
#  define JS_DBG_SOCK_INVALID (-1)
#  define js_dbg_sock_close   close
#endif

// ─── Step modes ──────────────────────────────────────────────────────────────
enum class DebugStepMode {
    None,       // running freely, only stop on breakpoints
    Pause,      // stop at the very next OP_LINE
    StepIn,     // same as Pause (stop on next line, any depth)
    StepOver,   // stop when call depth returns to ≤ step_depth_
    StepOut,    // stop when call depth drops below step_depth_
};

// ─── Breakpoint ───────────────────────────────────────────────────────────────
struct MujsBreakpoint {
    std::string file;   // as received from VSCode (absolute path)
    int         line;
};

// ─── Debug Adapter Server ─────────────────────────────────────────────────────
// Lives in a background thread; the game thread blocks here at breakpoints.
// Thread-safety:
//   • mtx_  guards: breakpoints_, step_mode_, step_depth_, paused_
//   • J_    is read from the debugger thread ONLY while game thread is blocked
//           (waiting on cv_), so no extra lock is needed for J_ inspection.
class MujsDebugger {
public:
    void start(js_State *J, int port = 4711);
    void stop();
    void update_state(js_State *J);

    bool is_running() const { return running_; }
    int  port()       const { return port_; }

    void set_verbose(bool v) { verbose_ = v; }
    void on_line(js_State *J, const char *file, int line);

    static std::string jstr(const std::string &s);

private:
    // ── State ────────────────────────────────────────────────────────────────
    js_State *J_ = nullptr;
    int         port_ = 4711;
    bool        verbose_ = false;

    sock_t      server_sock_ = JS_DBG_SOCK_INVALID;
    sock_t      client_sock_ = JS_DBG_SOCK_INVALID;
    std::thread server_thread_;
    std::atomic<bool> running_{ false };

    std::mutex              mtx_;
    std::condition_variable cv_;
    bool            paused_ = false;
    DebugStepMode   step_mode_ = DebugStepMode::None;
    int             step_depth_ = 0;
    std::string     step_start_file_;
    int             step_start_line_ = 0;

    std::vector<MujsBreakpoint> breakpoints_;

    // Object expansion: ref_id >= 1000 -> (parent_ref, property_name)
    std::map<int, std::pair<int, std::string>> object_ref_map_;
    int next_variable_ref_ = 1000;

    int seq_ = 1;
    int next_seq() { return seq_++; }

    // ── Hook logic (game thread) ─────────────────────────────────────────────
    bool should_break(const char *file, int line);
    void block_until_command();

    // ── Network (server thread) ──────────────────────────────────────────────
    void server_loop(int port);
    void handle_client();
    bool send_packet(const std::string &json);
    bool recv_packet(std::string &out);

    // ── DAP messaging (server thread, game thread paused) ───────────────────
    void handle_request(const std::string &body);
    void send_event(const std::string &event, const std::string &body);
    void send_response(int req_seq, const std::string &command,
        bool success, const std::string &body = "{}");
    void send_stopped_event(const char *reason, const char *file, int line);

    // ── Inspection (server thread, safe while game thread is on cv_.wait) ───
    std::string build_stack_trace_json(int levels);
    std::string build_scopes_json(int frame_id);
    std::string build_variables_json(int var_ref);
    js_Object *get_object_for_ref(int var_ref);
    std::string build_evaluate_response(const std::string &expression, int frame_id);

    // ── JSON parsing helpers ─────────────────────────────────────────────────
    static std::string extract_str(const std::string &json, const std::string &key);
    static int         extract_int(const std::string &json, const std::string &key, int def = 0);
    static std::string basename_of(const char *path);
    static bool        file_matches(const char *trace_file, const std::string &bp_file);
};

// Global singleton — accessed from the static OP_LINE hook lambda.
extern MujsDebugger g_mujs_debugger;
