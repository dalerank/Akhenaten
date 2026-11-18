#include "core/app.h"
#include "core/profiler.h"
#include "core/xvalue.h"
#include "game/game_events.h"
#include "js/js_events.h"
#include "js/js_game.h"
#include "net/http_client.h"
#include "core/log.h"
#include "game/game.h"

#include <regex>
#include <string>

struct event_github_recent_commits_loaded { xstring commits; };
struct event_github_totals_commits_loaded { int current_commit; };

// Main menu init can re-fire; only hit GitHub once per process.
struct github_cache_t {
    bool recent_attempted = false;
    xstring recent_commits;
    bool commits_attempted = false;
    int commits = -1;
};

bool github_is_active() {
#ifdef GAME_HAVE_CURL
    return true;
#else
    return false;
#endif
}

namespace {

bool parse_json_string_at(const std::string &body, size_t open_quote, std::string &out, size_t &end_pos) {
    out.clear();
    if (open_quote >= body.size() || body[open_quote] != '"') {
        return false;
    }

    size_t i = open_quote + 1;
    while (i < body.size()) {
        const char c = body[i++];
        if (c == '\\') {
            if (i >= body.size()) {
                return false;
            }
            const char e = body[i++];
            switch (e) {
            case 'n':
            case 'r':
                out.push_back('\n');
                break;
            case 't':
                out.push_back('\t');
                break;
            case '"':
            case '\\':
            case '/':
                out.push_back(e);
                break;
            case 'u':
                if (i + 4 > body.size()) {
                    return false;
                }
                i += 4; // skip \uXXXX; ASCII subjects do not need it
                break;
            default:
                out.push_back(e);
                break;
            }
        } else if (c == '"') {
            end_pos = i;
            return true;
        } else {
            out.push_back(c);
        }
    }
    return false;
}

std::string commit_subject_line(const std::string &message) {
    std::string line = message;
    const size_t nl = line.find('\n');
    if (nl != std::string::npos) {
        line.resize(nl);
    }
    while (!line.empty() && (line.back() == '\r' || line.back() == ' ' || line.back() == '\t')) {
        line.pop_back();
    }

    // Rich text treats '@' as markup (@L line break, @P paragraph, @N link).
    for (char &c : line) {
        if (c == '@') {
            c = ' ';
        }
    }

    constexpr size_t kMaxLen = 72;
    if (line.size() > kMaxLen) {
        line.resize(kMaxLen - 3);
        line += "...";
    }
    return line;
}

} // namespace

xstring github_get_recent_commits(pcstr owner, pcstr repo, int limit) {
    if (!owner || !*owner || !repo || !*repo) {
        return {};
    }
    if (limit < 1) {
        limit = 1;
    }
    if (limit > 30) {
        limit = 30;
    }

    auto &cache = xvalue<github_cache_t>::ref();
    if (cache.recent_attempted) {
        return cache.recent_commits;
    }
    cache.recent_attempted = true;

    std::string url = "https://api.github.com/repos/";
    url += owner;
    url += "/";
    url += repo;
    url += "/commits?per_page=";
    url += std::to_string(limit);

    const http_get_result response = http_get(url.c_str(), 10, false);

#ifndef GAME_HAVE_CURL
    (void)response;
    cache.recent_commits = xstring("Recent commits not supported on this platform (libcurl is not available).");
    return cache.recent_commits;
#else
    if (!response.ok || response.body.empty()) {
        if (response.http_code != 0) {
            logs::error("Unable to fetch recent commits (HTTP code: %ld)", response.http_code);
        }
        cache.recent_commits = xstring("Failed to download recent commits from GitHub.");
        return cache.recent_commits;
    }

    std::string formatted;
    size_t pos = 0;
    int found = 0;
    while (found < limit) {
        const size_t key = response.body.find("\"message\"", pos);
        if (key == std::string::npos) {
            break;
        }

        const size_t colon = response.body.find(':', key + 9);
        if (colon == std::string::npos) {
            break;
        }

        size_t q = colon + 1;
        while (q < response.body.size() && (response.body[q] == ' ' || response.body[q] == '\t' || response.body[q] == '\n'
                                           || response.body[q] == '\r')) {
            ++q;
        }

        std::string message;
        size_t end_pos = q;
        if (!parse_json_string_at(response.body, q, message, end_pos)) {
            pos = q + 1;
            continue;
        }
        pos = end_pos;

        const std::string subject = commit_subject_line(message);
        if (subject.empty()) {
            continue;
        }

        if (!formatted.empty()) {
            formatted += "@L";
        }
        formatted += "* ";
        formatted += subject;
        ++found;
    }

    if (formatted.empty()) {
        cache.recent_commits = xstring("No recent commits found.");
    } else {
        logs::info("Recent commits downloaded successfully (%d items)", found);
        cache.recent_commits = xstring(formatted.c_str());
    }
    return cache.recent_commits;
#endif
}

int github_get_total_commits(pcstr owner, pcstr repo) {
    if (!owner || !*owner || !repo || !*repo) {
        return -1;
    }

    auto &cache = xvalue<github_cache_t>::ref();
    if (cache.commits_attempted) {
        return cache.commits;
    }
    cache.commits_attempted = true;

    std::string url = "https://api.github.com/repos/";
    url += owner;
    url += "/";
    url += repo;
    url += "/commits?per_page=1";

    const http_get_result response = http_get(url.c_str(), 10, true);

#ifndef GAME_HAVE_CURL
    (void)response;
    cache.commits = -1;
    return -1;
#else
    if (!response.ok) {
        logs::error("Unable to fetch commits (HTTP code: %ld)", response.http_code);
        cache.commits = -1;
        return -1;
    }

    const std::regex link_regex(R"(<([^>]+)>; rel="last")");
    std::smatch match;

    int total = 1;
    if (std::regex_search(response.headers, match, link_regex)) {
        const std::string last_page_url = match[1].str();
        const std::regex page_regex(R"(&page=(\d+))");
        if (std::regex_search(last_page_url, match, page_regex)) {
            total = std::stoi(match[1].str());
        }
    }

    cache.commits = total;
    return total;
#endif
}

void github_get_recent_commits_async(pcstr owner, pcstr repo) {
    const xstring owner_str(owner ? owner : "");
    const xstring repo_str(repo ? repo : "");

    game.mtrpc.detach_task([owner_str, repo_str]() {
        const xstring commits = github_get_recent_commits(owner_str.c_str(), repo_str.c_str(), 10);
        game.add_frame_end_event([commits]() {
            events::emit(event_github_recent_commits_loaded{ commits });
        });
    });
}

void github_get_total_commits_async(pcstr owner, pcstr repo) {
    const xstring owner_str(owner ? owner : "");
    const xstring repo_str(repo ? repo : "");

    game.mtrpc.detach_task([owner_str, repo_str]() {
        const int current_commit = github_get_total_commits(owner_str.c_str(), repo_str.c_str());
        game.add_frame_end_event([current_commit]() {
            events::emit(event_github_totals_commits_loaded{ current_commit });
        });
    });
}

void ANK_REGISTER_APPLICATION_MODULE(register_github_module) {
}

ANK_FUNCTION(github_is_active)
ANK_FUNCTION_2(github_get_recent_commits_async)
ANK_FUNCTION_2(github_get_total_commits_async)

ANK_SCRIPT_EVENT(event_github_recent_commits_loaded, commits)
ANK_SCRIPT_EVENT(event_github_totals_commits_loaded, current_commit)
