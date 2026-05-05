#include "report_bug.h"

#include "core/log.h"
#include "core/profiler.h"
#include "game/game.h"
#include "js/js_events.h"
#include "js/js_game.h"

#ifdef GAME_HAVE_CURL
#include <curl/curl.h>
#include <string>

static size_t report_bug_write_callback(void* contents, size_t size, size_t nmemb, std::string* data) {
    size_t total = size * nmemb;
    data->append((char*)contents, total);
    return total;
}
#endif

void report_bug_http_post(const char* title, const char* body) {
#ifdef GAME_HAVE_CURL
    std::string title_str = title ? title : "";
    std::string body_str  = body  ? body  : "";

    game.mt.detach_task([title_str, body_str]() {
        CURL* curl = curl_easy_init();
        if (!curl) {
            logs::error("report_bug: curl_easy_init failed");
            xstring err("Failed to initialize HTTP client.");
            game.add_frame_end_event([err]() {
                events::emit(event_report_bug_result{ 0, xstring(), err });
            });
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

        std::string payload = "{\"title\":\"" + json_escape(title_str) + "\",\"body\":\"" + json_escape(body_str) + "\"}";
        std::string response_buf;

        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "User-Agent: Akhenaten/1.0");

        curl_easy_setopt(curl, CURLOPT_URL, "https://c8b67431cd9028f6198998cf5c57aa01.m.pipedream.net");
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)payload.size());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, report_bug_write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_buf);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 15L);

        CURLcode res = curl_easy_perform(curl);

        long http_code = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            logs::error("report_bug: curl error: %s", curl_easy_strerror(res));
            xstring err(curl_easy_strerror(res));
            game.add_frame_end_event([err]() {
                events::emit(event_report_bug_result{ 0, xstring(), err });
            });
            return;
        }

        if (http_code < 200 || http_code >= 300) {
            logs::error("report_bug: HTTP %ld", http_code);
            char buf[64];
            snprintf(buf, sizeof(buf), "HTTP error %ld", http_code);
            xstring err(buf);
            game.add_frame_end_event([err]() {
                events::emit(event_report_bug_result{ 0, xstring(), err });
            });
            return;
        }

        logs::info("report_bug: submitted successfully (HTTP %ld)", http_code);
        game.add_frame_end_event([]() {
            events::emit(event_report_bug_result{ 1, xstring(), xstring() });
        });
    });
#else
    game.add_frame_end_event([]() {
        events::emit(event_report_bug_result{ 0, xstring(), xstring("Not supported: libcurl is not available.") });
    });
#endif
}

void __game_report_bug(pcstr title, pcstr body) {
    report_bug_http_post(title, body);
}
ANK_FUNCTION_2(__game_report_bug)
