#include "platform/discord_rpc.h"

#if !defined(GAME_PLATFORM_ANDROID) && !defined(GAME_PLATFORM_BROWSER)

#include "core/log.h"
#include "game/game.h"
#include "game/game_events.h"
#include "game/simulation_time.h"
#include "scenario/scenario.h"
#include "core/app.h"

#include <cstdint>
#include <cstring>
#include <cstdio>
#include <ctime>

#ifdef GAME_PLATFORM_WIN
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/select.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#endif

struct discord_rpc_t::impl {
    char app_id[64] = {};
    bool logged_fail = false;
    int64_t start_timestamp = 0;
    xstring pending_details;
    xstring pending_state;
    uint32_t nonce = 0;

#ifdef GAME_PLATFORM_WIN
    void* pipe_handle = (void*)(intptr_t)(-1);
#else
    int fd = -1;
#endif

    bool is_connected() const;
    bool raw_write(const void* buf, uint32_t len);
    void close_pipe();
    bool open_pipe();
    bool read_blocking(void* buf, uint32_t len);
    void drain_incoming();
    bool send_packet(uint32_t opcode, const char* json);
    static void json_escape(const char* src, char* dst, size_t dst_cap);
    bool do_handshake();
    bool try_connect();
    void do_send_activity(const xstring& details, const xstring& state);

    void init(const char* id);
    void shutdown();
    void tick();
    void set_activity(const xstring& details, const xstring& state);
    void clear_activity();
};

#ifdef GAME_PLATFORM_WIN

bool discord_rpc_t::impl::is_connected() const {
    return pipe_handle != (void*)(intptr_t)(-1);
}

bool discord_rpc_t::impl::raw_write(const void* buf, uint32_t len) {
    DWORD written = 0;
    return WriteFile((HANDLE)pipe_handle, buf, (DWORD)len, &written, nullptr) && written == len;
}

void discord_rpc_t::impl::close_pipe() {
    CloseHandle((HANDLE)pipe_handle);
    pipe_handle = (void*)(intptr_t)(-1);
}

bool discord_rpc_t::impl::open_pipe() {
    for (int i = 0; i <= 9; ++i) {
        wchar_t path[48];
        swprintf(path, 48, L"\\\\.\\pipe\\discord-ipc-%d", i);
        HANDLE h = CreateFileW(path, GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, 0, nullptr);
        if (h != INVALID_HANDLE_VALUE) {
            pipe_handle = (void*)h;
            return true;
        }
    }
    return false;
}

bool discord_rpc_t::impl::read_blocking(void* buf, uint32_t len) {
    char* ptr = (char*)buf;
    uint32_t remaining = len;
    while (remaining > 0) {
        DWORD rb = 0;
        if (!ReadFile((HANDLE)pipe_handle, ptr, remaining, &rb, nullptr) || rb == 0) return false;
        ptr += rb;
        remaining -= rb;
    }
    return true;
}

void discord_rpc_t::impl::drain_incoming() {
    DWORD avail = 0;
    while (PeekNamedPipe((HANDLE)pipe_handle, nullptr, 0, nullptr, &avail, nullptr) && avail >= 8) {
        uint8_t hdr[8];
        DWORD rb = 0;
        if (!ReadFile((HANDLE)pipe_handle, hdr, 8, &rb, nullptr) || rb < 8) { close_pipe(); return; }
        uint32_t plen = (uint32_t)hdr[4] | ((uint32_t)hdr[5] << 8) | ((uint32_t)hdr[6] << 16) | ((uint32_t)hdr[7] << 24);
        while (plen > 0) {
            uint8_t tmp[256];
            DWORD chunk = (plen < 256) ? plen : 256;
            DWORD r = 0;
            if (!ReadFile((HANDLE)pipe_handle, tmp, chunk, &r, nullptr) || r == 0) { close_pipe(); return; }
            plen -= r;
        }
    }
}

#else // POSIX

bool discord_rpc_t::impl::is_connected() const {
    return fd >= 0;
}

bool discord_rpc_t::impl::raw_write(const void* buf, uint32_t len) {
    const char* ptr = (const char*)buf;
    uint32_t remaining = len;
    while (remaining > 0) {
        ssize_t n = write(fd, ptr, remaining);
        if (n <= 0) return false;
        ptr += n;
        remaining -= (uint32_t)n;
    }
    return true;
}

void discord_rpc_t::impl::close_pipe() {
    close(fd);
    fd = -1;
}

bool discord_rpc_t::impl::open_pipe() {
    const char* dirs[3] = {
        getenv("XDG_RUNTIME_DIR"),
        getenv("TMPDIR"),
        "/tmp"
    };

    for (int di = 0; di < 3; ++di) {
        if (!dirs[di] || !dirs[di][0]) continue;
        for (int i = 0; i <= 9; ++i) {
            int sock = socket(AF_UNIX, SOCK_STREAM, 0);
            if (sock < 0) return false;

            struct sockaddr_un addr;
            memset(&addr, 0, sizeof(addr));
            addr.sun_family = AF_UNIX;
            snprintf(addr.sun_path, sizeof(addr.sun_path), "%s/discord-ipc-%d", dirs[di], i);

            if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == 0) {
                fd = sock;
                return true;
            }
            close(sock);
        }
    }
    return false;
}

bool discord_rpc_t::impl::read_blocking(void* buf, uint32_t len) {
    char* ptr = (char*)buf;
    uint32_t remaining = len;
    while (remaining > 0) {
        fd_set rfds;
        FD_ZERO(&rfds);
        FD_SET(fd, &rfds);
        struct timeval tv = {2, 0};
        if (select(fd + 1, &rfds, nullptr, nullptr, &tv) <= 0) return false;
        ssize_t n = read(fd, ptr, remaining);
        if (n <= 0) return false;
        ptr += n;
        remaining -= (uint32_t)n;
    }
    return true;
}

void discord_rpc_t::impl::drain_incoming() {
    char buf[512];
    while (true) {
        ssize_t n = recv(fd, buf, sizeof(buf), MSG_DONTWAIT);
        if (n <= 0) {
            if (n < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) return;
            close_pipe();
            return;
        }
    }
}

#endif // GAME_PLATFORM_WIN

bool discord_rpc_t::impl::send_packet(uint32_t opcode, const char* json) {
    uint32_t len = (uint32_t)strlen(json);
    uint8_t hdr[8] = {
        (uint8_t)(opcode),       (uint8_t)(opcode >> 8),
        (uint8_t)(opcode >> 16), (uint8_t)(opcode >> 24),
        (uint8_t)(len),          (uint8_t)(len >> 8),
        (uint8_t)(len >> 16),    (uint8_t)(len >> 24),
    };
    return raw_write(hdr, 8) && raw_write(json, len);
}

void discord_rpc_t::impl::json_escape(const char* src, char* dst, size_t dst_cap) {
    size_t i = 0;
    if (!src) { dst[0] = 0; return; }
    while (*src && i + 2 < dst_cap) {
        unsigned char c = (unsigned char)*src++;
        if (c == '"' || c == '\\') { dst[i++] = '\\'; dst[i++] = c; }
        else if (c >= 0x20) { dst[i++] = c; }
    }
    dst[i] = 0;
}

bool discord_rpc_t::impl::do_handshake() {
    char json[128];
    snprintf(json, sizeof(json), "{\"v\":1,\"client_id\":\"%s\"}", app_id);
    if (!send_packet(0, json)) return false;

    uint8_t hdr[8];
    if (!read_blocking(hdr, 8)) return false;

    uint32_t plen = (uint32_t)hdr[4] | ((uint32_t)hdr[5] << 8) | ((uint32_t)hdr[6] << 16) | ((uint32_t)hdr[7] << 24);
    if (plen > 8192) return false;

    char tmp[256];
    while (plen > 0) {
        uint32_t chunk = (plen < sizeof(tmp)) ? plen : (uint32_t)sizeof(tmp);
        if (!read_blocking(tmp, chunk)) return false;
        plen -= chunk;
    }
    return true;
}

bool discord_rpc_t::impl::try_connect() {
    if (!open_pipe()) return false;
    if (!do_handshake()) { close_pipe(); return false; }
    return true;
}

void discord_rpc_t::impl::do_send_activity(const xstring& details, const xstring& state) {
    char esc_details[128], esc_state[128];
    json_escape(details.c_str(), esc_details, sizeof(esc_details));
    json_escape(state.c_str(), esc_state, sizeof(esc_state));

    int pid =
#ifdef GAME_PLATFORM_WIN
        (int)GetCurrentProcessId();
#else
        (int)getpid();
#endif

    char json[512];
    snprintf(json, sizeof(json),
        "{\"cmd\":\"SET_ACTIVITY\","
        "\"args\":{"
        "\"pid\":%d,"
        "\"activity\":{"
        "\"details\":\"%s\","
        "\"state\":\"%s\","
        "\"timestamps\":{\"start\":%lld},"
        "\"assets\":{\"large_image\":\"icon\",\"large_text\":\"Akhenaten\"}"
        "}},"
        "\"nonce\":\"%u\"}",
        pid, esc_details, esc_state, (long long)start_timestamp, ++nonce);

    if (!send_packet(1, json)) {
        logs::warn("discord_rpc: send failed, disconnecting");
        close_pipe();
    }
}

void discord_rpc_t::impl::init(const char* id) {
    strncpy(app_id, id, sizeof(app_id) - 1);
    app_id[sizeof(app_id) - 1] = 0;
    start_timestamp = (int64_t)time(nullptr);
    logged_fail = false;

    if (!try_connect()) {
        logs::info("discord_rpc: Discord not running, Rich Presence disabled");
        logged_fail = true;
    } else {
        logs::info("discord_rpc: connected to Discord IPC");
    }
}

void discord_rpc_t::impl::shutdown() {
    if (is_connected()) {
        send_packet(2, "{}");
        close_pipe();
    }
}

void discord_rpc_t::impl::tick() {
    if (!is_connected()) {
        if (logged_fail) return;
        if (!try_connect()) return;
        logs::info("discord_rpc: reconnected to Discord IPC");
        logged_fail = false;
        if (!pending_details.empty()) {
            do_send_activity(pending_details, pending_state);
        }
        return;
    }
    drain_incoming();
}

void discord_rpc_t::impl::set_activity(const xstring& details, const xstring& state) {
    pending_details = details;
    pending_state = state;
    if (!is_connected()) return;
    do_send_activity(details, state);
}

void discord_rpc_t::impl::clear_activity() {
    pending_details = xstring();
    pending_state = xstring();
    if (!is_connected()) return;

    int pid =
#ifdef GAME_PLATFORM_WIN
        (int)GetCurrentProcessId();
#else
        (int)getpid();
#endif
    char json[128];
    snprintf(json, sizeof(json),
        "{\"cmd\":\"SET_ACTIVITY\",\"args\":{\"pid\":%d,\"activity\":null},\"nonce\":\"%u\"}",
        pid, ++nonce);

    if (!send_packet(1, json)) {
        close_pipe();
    }
}

// -----------------------------------------------------------------------
// discord_rpc_t (facade)
// -----------------------------------------------------------------------

discord_rpc_t::discord_rpc_t() : d(std::make_unique<impl>()) {}

discord_rpc_t::~discord_rpc_t() = default;

void discord_rpc_t::init(const char* app_id) { d->init(app_id); }

void discord_rpc_t::shutdown() { d->shutdown(); }

void discord_rpc_t::tick() { d->tick(); }

void discord_rpc_t::set_activity(const xstring& details, const xstring& state) {
    d->set_activity(details, state);
}

void discord_rpc_t::clear_activity() { d->clear_activity(); }

discord_rpc_t g_discord_rpc;

// -----------------------------------------------------------------------
// Engine integration
// -----------------------------------------------------------------------

namespace {

static const char* k_eg_months[12] = {
    "Thoth", "Paopi", "Hathor", "Choiak",
    "Tybi", "Mekhir", "Phamenoth", "Pharmuthi",
    "Pachons", "Payni", "Epiphi", "Mesore"
};

} // anonymous namespace

void ANK_REGISTER_APPLICATION_MODULE(discord_rpc_module) {
    g_discord_rpc.init("1501648147682693140");
}

void ANK_PERMANENT_CALLBACK(event_game_mission_pre_load, ) {
    g_discord_rpc.set_activity(game.session.last_loaded_mission, xstring(""));
}

void ANK_PERMANENT_CALLBACK(event_advance_month, e) {
    g_discord_rpc.tick();

    if (!game.session.active) return;

    const char* city = (const char*)g_scenario.scenario_name;
    xstring details(city && city[0] ? city : "Akhenaten");

    const char* month = (e.month >= 0 && e.month < 12) ? k_eg_months[e.month] : "";
    char buf[48];
    snprintf(buf, sizeof(buf), "Year %d, %s", e.years_since_start + 1, month);
    g_discord_rpc.set_activity(details, xstring(buf));
}

#endif // !GAME_PLATFORM_ANDROID && !GAME_PLATFORM_BROWSER
