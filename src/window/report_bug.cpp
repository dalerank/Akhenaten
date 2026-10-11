#include "report_bug.h"

#include "city/city_warnings.h"
#include "core/log.h"
#include "core/profiler.h"
#include "game/game.h"
#include "graphics/elements/lang_text.h"
#include "graphics/screenshot.h"
#include "js/js_events.h"
#include "js/js_game.h"
#include "platform/platform.h"
#include "platform/version.hpp"

#ifdef GAME_HAVE_CURL
#include <curl/curl.h>
#include <cstdio>
#include <string>

static constexpr size_t k_log_max = 1500000;
static constexpr pcstr k_report_url = "https://playshhhit.com/akhenaten";

static size_t report_bug_write_callback(void* contents, size_t size, size_t nmemb, std::string* data) {
    size_t total = size * nmemb;
    data->append((char*)contents, total);
    return total;
}

static std::string read_log_tail(pcstr path, size_t max_bytes) {
    if (!path || !*path || max_bytes == 0) {
        return {};
    }
    FILE* f = std::fopen(path, "rb");
    if (!f) {
        return {};
    }
    if (std::fseek(f, 0, SEEK_END) != 0) {
        std::fclose(f);
        return {};
    }
    const long end = std::ftell(f);
    if (end < 0) {
        std::fclose(f);
        return {};
    }
    const size_t size = (size_t)end;
    const size_t take = size > max_bytes ? max_bytes : size;
    if (std::fseek(f, (long)(size - take), SEEK_SET) != 0) {
        std::fclose(f);
        return {};
    }
    std::string out(take, '\0');
    const size_t n = std::fread(out.data(), 1, take, f);
    std::fclose(f);
    out.resize(n);
    if (take < size) {
        const auto nl = out.find('\n');
        if (nl != std::string::npos) {
            out.erase(0, nl + 1);
        }
    }
    return out;
}

static constexpr size_t k_shot_max = 4 * 1024 * 1024;

static std::string report_shot_path() {
    const pcstr log_path = logs::output_path();
    if (!log_path || !*log_path) {
        return "akhenaten-report.png";
    }
    std::string path(log_path);
    const auto slash = path.find_last_of("\\/");
    if (slash == std::string::npos) {
        return "akhenaten-report.png";
    }
    return path.substr(0, slash + 1) + "akhenaten-report.png";
}

static std::string base64_encode(const std::string& raw) {
    static const char table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string out;
    out.reserve(((raw.size() + 2) / 3) * 4);
    size_t i = 0;
    while (i + 3 <= raw.size()) {
        const unsigned n = ((unsigned char)raw[i] << 16) | ((unsigned char)raw[i + 1] << 8) | (unsigned char)raw[i + 2];
        out.push_back(table[(n >> 18) & 63]);
        out.push_back(table[(n >> 12) & 63]);
        out.push_back(table[(n >> 6) & 63]);
        out.push_back(table[n & 63]);
        i += 3;
    }
    if (i < raw.size()) {
        unsigned n = (unsigned char)raw[i] << 16;
        if (i + 1 < raw.size()) {
            n |= (unsigned char)raw[i + 1] << 8;
        }
        out.push_back(table[(n >> 18) & 63]);
        out.push_back(table[(n >> 12) & 63]);
        out.push_back(i + 1 < raw.size() ? table[(n >> 6) & 63] : '=');
        out.push_back('=');
    }
    return out;
}

static std::string read_shot_base64(pcstr path) {
    FILE* f = std::fopen(path, "rb");
    if (!f) {
        return {};
    }
    if (std::fseek(f, 0, SEEK_END) != 0) {
        std::fclose(f);
        return {};
    }
    const long end = std::ftell(f);
    if (end <= 0 || (size_t)end > k_shot_max) {
        std::fclose(f);
        return {};
    }
    if (std::fseek(f, 0, SEEK_SET) != 0) {
        std::fclose(f);
        return {};
    }
    std::string raw((size_t)end, '\0');
    const size_t n = std::fread(raw.data(), 1, (size_t)end, f);
    std::fclose(f);
    raw.resize(n);
    return base64_encode(raw);
}

struct report_bug_pending {
    std::string title;
    std::string body;
    std::string build;
    std::string platform;
    std::string lang;
    std::string log;
    int frames_left = 0;
    bool armed = false;
};

static report_bug_pending g_report_bug;

static void report_bug_post_now();
static void report_bug_on_frame_end();

static void report_bug_finish(int ok, xstring error) {
    game.add_frame_end_event([ok, error]() {
        events::emit(event_city_warning{ ok ? xstring("#report_bug_sent") : xstring("#report_bug_error") });
        events::emit(event_report_bug_result{ ok, xstring(), error });
    });
}

static void report_bug_on_frame_end() {
    if (g_report_bug.frames_left > 0) {
        --g_report_bug.frames_left;
        game.add_frame_end_event(report_bug_on_frame_end);
        return;
    }
    g_report_bug.armed = false;
    report_bug_post_now();
}
#endif

void report_bug_http_post(const char* title, const char* body) {
#ifdef GAME_HAVE_CURL
    g_report_bug.title = title ? title : "";
    g_report_bug.body = body ? body : "";
    g_report_bug.build = get_version().c_str();
    g_report_bug.platform = platform.name() ? platform.name() : "";
    g_report_bug.lang = lang_get_current_language().lang.c_str();
    logs::flush();
    g_report_bug.log = read_log_tail(logs::output_path(), k_log_max);
    // This frame was already drawn with the dialog. The next frame redraws after it closes.
    g_report_bug.frames_left = 1;
    if (!g_report_bug.armed) {
        g_report_bug.armed = true;
        game.add_frame_end_event(report_bug_on_frame_end);
    }
#else
    game.add_frame_end_event([]() {
        events::emit(event_city_warning{ xstring("#report_bug_error") });
        events::emit(event_report_bug_result{ 0, xstring(), xstring("Not supported: libcurl is not available.") });
    });
#endif
}

#ifdef GAME_HAVE_CURL
static void report_bug_post_now() {
    const std::string shot_path = report_shot_path();
    std::string shot;
    if (graphics_write_display_png(shot_path.c_str())) {
        shot = read_shot_base64(shot_path.c_str());
        std::remove(shot_path.c_str());
    }
    std::string title_str = std::move(g_report_bug.title);
    std::string body_str = std::move(g_report_bug.body);
    std::string build = std::move(g_report_bug.build);
    std::string platform_name = std::move(g_report_bug.platform);
    std::string lang = std::move(g_report_bug.lang);
    std::string log_text = std::move(g_report_bug.log);

    game.mt.detach_task([title_str, body_str, build, platform_name, lang, log_text, shot]() {
        CURL* curl = curl_easy_init();
        if (!curl) {
            logs::error("report_bug: curl_easy_init failed");
            report_bug_finish(0, xstring("Failed to initialize HTTP client."));
            return;
        }

        auto json_escape = [](const std::string& s) -> std::string {
            std::string out;
            out.reserve(s.size() + 8);
            for (unsigned char c : s) {
                switch (c) {
                case '"':  out += "\\\""; break;
                case '\\': out += "\\\\"; break;
                case '\n': out += "\\n";  break;
                case '\r': out += "\\r";  break;
                case '\t': out += "\\t";  break;
                default:
                    if (c < 0x20) {
                        char buf[8];
                        snprintf(buf, sizeof(buf), "\\u%04x", (unsigned)c);
                        out += buf;
                    } else {
                        out += (char)c;
                    }
                    break;
                }
            }
            return out;
        };

        std::string payload = "{\"kind\":\"bug\",\"title\":\"" + json_escape(title_str)
            + "\",\"text\":\"" + json_escape(body_str)
            + "\",\"build\":\"" + json_escape(build)
            + "\",\"platform\":\"" + json_escape(platform_name)
            + "\",\"lang\":\"" + json_escape(lang)
            + "\",\"log\":\"" + json_escape(log_text) + "\"";
        if (!shot.empty()) {
            payload += ",\"shot\":\"" + json_escape(shot) + "\"";
        }
        payload += "}";
        std::string response_buf;

        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "User-Agent: Akhenaten/1.0");

        curl_easy_setopt(curl, CURLOPT_URL, k_report_url);
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)payload.size());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, report_bug_write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_buf);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 60L);

        CURLcode res = curl_easy_perform(curl);

        long http_code = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            logs::error("report_bug: curl error: %s", curl_easy_strerror(res));
            report_bug_finish(0, xstring(curl_easy_strerror(res)));
            return;
        }

        if (http_code < 200 || http_code >= 300) {
            logs::error("report_bug: HTTP %ld", http_code);
            char buf[64];
            snprintf(buf, sizeof(buf), "HTTP error %ld", http_code);
            report_bug_finish(0, xstring(buf));
            return;
        }

        logs::info("report_bug: submitted successfully (HTTP %ld)", http_code);
        report_bug_finish(1, xstring());
    });
}
#endif

void __game_report_bug(pcstr title, pcstr body) {
    report_bug_http_post(title, body);
}
ANK_FUNCTION_2(__game_report_bug)
