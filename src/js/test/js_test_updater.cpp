#include "js/test/js_test_common.h"

#include "core/xstring.h"
#include "platform/app_updater.h"

#include <cstdlib>
#include <string>

static int64_t parse_int64(pcstr text) {
    return text ? std::strtoll(text, nullptr, 10) : 0;
}

static xstring __test_updater_parse_time(pcstr text) {
    int64_t value = 0;
    if (!updater::parse_utc_time(text, value)) {
        return xstring("!");
    }
    return xstring(std::to_string(value).c_str());
}
ANK_FUNCTION_1(__test_updater_parse_time);

// "<run id>|<sha>|<created>", or "!" when the answer is not understood
static xstring __test_updater_parse_run(pcstr json) {
    updater_remote_build remote;
    if (!updater::parse_latest_run(json ? json : "", remote)) {
        return xstring("!");
    }
    const std::string text = std::to_string(remote.run_id) + "|" + remote.sha + "|" + std::to_string(remote.created);
    return xstring(text.c_str());
}
ANK_FUNCTION_1(__test_updater_parse_run);

static bool __test_updater_is_newer(pcstr remote_sha, pcstr remote_created, pcstr local_sha, pcstr local_time) {
    updater_remote_build remote;
    remote.run_id = 1;
    remote.sha = remote_sha ? remote_sha : "";
    remote.created = parse_int64(remote_created);
    return updater::is_newer(remote, local_sha, parse_int64(local_time));
}
ANK_FUNCTION_4(__test_updater_is_newer);

// "<workflow>|<artifact>|<program>", or "!" for a platform without builds
static xstring __test_updater_asset(int platform) {
    updater_asset asset;
    if (!updater::asset_for((e_updater_platform)platform, asset)) {
        return xstring("!");
    }
    const std::string text = std::string(asset.workflow) + "|" + asset.artifact + "|" + asset.program;
    return xstring(text.c_str());
}
ANK_FUNCTION_1(__test_updater_asset);

static xstring __test_updater_runs_url(int platform) {
    updater_asset asset;
    updater::asset_for((e_updater_platform)platform, asset);
    return asset.workflow ? xstring(updater::runs_url(asset).c_str()) : xstring("!");
}
ANK_FUNCTION_1(__test_updater_runs_url);

static xstring __test_updater_download_url(int platform, pcstr run_id) {
    updater_asset asset;
    updater::asset_for((e_updater_platform)platform, asset);
    return asset.workflow ? xstring(updater::download_url(asset, parse_int64(run_id)).c_str()) : xstring("!");
}
ANK_FUNCTION_2(__test_updater_download_url);

static int __test_updater_current_platform() {
    return updater::current_platform();
}
ANK_FUNCTION(__test_updater_current_platform);

// the normalized path, or "!" when the entry would land outside the target folder
static xstring __test_updater_safe_path(pcstr name) {
    std::string path;
    if (!updater::safe_entry_path(name, path)) {
        return xstring("!");
    }
    return xstring(path.c_str());
}
ANK_FUNCTION_1(__test_updater_safe_path);

// entries separated by "|"
static bool __test_updater_has_program(pcstr entries, pcstr program) {
    std::vector<std::string> list;
    std::string all = entries ? entries : "";
    size_t start = 0;
    while (start <= all.size()) {
        size_t end = all.find('|', start);
        if (end == std::string::npos) {
            end = all.size();
        }
        list.push_back(all.substr(start, end - start));
        start = end + 1;
    }
    return updater::has_program(list, program ? program : "");
}
ANK_FUNCTION_2(__test_updater_has_program);

static int __test_updater_next_state(int state, int event) {
    return updater::next_state((e_updater_state)state, (e_updater_event)event);
}
ANK_FUNCTION_2(__test_updater_next_state);

static int __test_updater_button(int state) {
    return updater::button_action((e_updater_state)state);
}
ANK_FUNCTION_1(__test_updater_button);
