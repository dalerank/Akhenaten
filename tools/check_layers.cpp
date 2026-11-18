// Layer check for src/: a file may include headers of its own layer or lower.
//
// Layers, low to high: core < grid < sim < presentation < app (directories per layer in LAYERS below).
// Existing violations are recorded in tools/layers_baseline.txt; only new ones fail.
//
//   check_layers            check against the baseline (exit 1 on new violations)
//   check_layers --update   rewrite the baseline from the current tree
//   check_layers --summary  print violation counts per (layer -> layer)
//   --root DIR              repository root (default: the working directory)
//
// Build: g++ -std=c++17 -O2 tools/check_layers.cpp -o check_layers (or the CMake target check_layers).

#include <algorithm>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <map>
#include <regex>
#include <set>
#include <string>
#include <tuple>
#include <vector>

namespace fs = std::filesystem;

struct layer_def {
    const char* name;
    std::vector<std::string> dirs;
};

static const std::vector<layer_def> LAYERS = {
  {"core", {"core", "events"}},
  {"grid", {"grid"}},
  {"sim", {"building", "figure", "figuretype", "city", "scenario", "empire", "game", "io", "resource", "config"}},
  {"presentation", {"graphics", "overlays", "widget", "window", "sound", "input", "content"}},
  {"app", {"platform", "js", "dev", "debug", "editor", "net"}},
};

// Enum-only "vocabulary" headers: usable from any layer as long as they include nothing above themselves.
static const std::set<std::string> VOCABULARY = {
  "building/building_type.h",
  "city/constants.h",
  "figure/figure_type.h",
  "game/resource.h",
};

// Low-level infrastructure that sits in a higher directory: treated as core when included.
// Moving these files where they belong is part of the plan; until then they are not violations.
static const std::set<std::string> INFRASTRUCTURE = {
  "js/js.h",
  "js/js_defines.h",
  "js/js_events.h",
  "js/js_game.h",
  "js/js_register.h",
  "js/js_struct.h",
  "io/io_buffer.h",
  "platform/platform.h",
  "content/vfs.h",
};

static const std::set<std::string> IGNORED_DIRS = {"mujs", "lame", "bzip", "lzma", "scripts"};

static std::map<std::string, int> g_rank;
static std::map<std::string, std::string> g_layer_name;
static fs::path g_src;

static std::string top_dir(const std::string& rel) {
    const size_t slash = rel.find('/');
    return slash == std::string::npos ? rel : rel.substr(0, slash);
}

static bool ends_with(const std::string& s, const std::string& suffix) {
    return s.size() >= suffix.size() && s.compare(s.size() - suffix.size(), suffix.size(), suffix) == 0;
}

// JS binding glue lives next to the code it binds; it is checked by its own rule later.
static bool is_exempt_source(const std::string& rel) {
    return ends_with(rel, "_js.cpp") || ends_with(rel, "_js.h");
}

static std::string resolve(const std::string& src_rel, const std::string& inc) {
    const std::string top = top_dir(inc);
    if ((inc.find('/') != std::string::npos && g_rank.count(top)) || IGNORED_DIRS.count(top)) {
        return inc;
    }
    const std::string local = (fs::path(src_rel).parent_path() / inc).lexically_normal().generic_string();
    std::error_code ec;
    if (fs::exists(g_src / local, ec)) {
        return local;
    }
    return inc;
}

static std::set<std::string> collect() {
    static const std::regex include_re(R"re(^\s*#\s*include\s+"([^"]+)")re");
    std::set<std::string> violations;
    std::error_code ec;
    for (auto it = fs::recursive_directory_iterator(g_src, ec); it != fs::recursive_directory_iterator();
      it.increment(ec)) {
        const std::string rel = fs::relative(it->path(), g_src, ec).generic_string();
        if (it->is_directory(ec)) {
            if (IGNORED_DIRS.count(top_dir(rel))) {
                it.disable_recursion_pending();
            }
            continue;
        }
        if (!ends_with(rel, ".cpp") && !ends_with(rel, ".h") && !ends_with(rel, ".hpp")) {
            continue;
        }
        const std::string src_layer = top_dir(rel);
        if (!g_rank.count(src_layer) || is_exempt_source(rel)) {
            continue;
        }
        std::ifstream in(it->path(), std::ios::binary);
        std::string line;
        while (std::getline(in, line)) {
            std::smatch m;
            if (!std::regex_search(line, m, include_re)) {
                continue;
            }
            const std::string target = resolve(rel, m[1].str());
            const std::string tgt_layer = top_dir(target);
            if (!g_rank.count(tgt_layer) || VOCABULARY.count(target) || INFRASTRUCTURE.count(target)
                || ends_with(target, "_fwd.h")) {
                continue;
            }
            if (g_rank[tgt_layer] > g_rank[src_layer]) {
                violations.insert(rel + " -> " + target);
            }
        }
    }
    return violations;
}

static std::set<std::string> read_baseline(const fs::path& path) {
    std::set<std::string> lines;
    std::ifstream in(path, std::ios::binary);
    std::string line;
    while (std::getline(in, line)) {
        while (!line.empty() && (line.back() == '\r' || line.back() == ' ' || line.back() == '\t')) {
            line.pop_back();
        }
        const size_t first = line.find_first_not_of(" \t");
        if (first == std::string::npos || line[0] == '#') {
            continue;
        }
        lines.insert(line.substr(first));
    }
    return lines;
}

static void write_baseline(const fs::path& path, const std::set<std::string>& violations) {
    std::ofstream out(path, std::ios::binary | std::ios::trunc);
    out << "# Known layer violations (file -> included header). Generated by tools/check_layers.cpp --update.\n";
    out << "# Remove lines as violations get fixed; never add lines by hand to silence a new one.\n";
    for (const std::string& v : violations) {
        out << v << "\n";
    }
}

static void print_summary(const std::set<std::string>& violations) {
    std::map<std::tuple<std::string, std::string, std::string>, int> pairs;
    for (const std::string& v : violations) {
        const size_t arrow = v.find(" -> ");
        const std::string src = top_dir(v.substr(0, arrow));
        const std::string tgt = top_dir(v.substr(arrow + 4));
        ++pairs[{g_layer_name[src], src, tgt}];
    }
    std::vector<std::pair<std::tuple<std::string, std::string, std::string>, int>> sorted(pairs.begin(), pairs.end());
    std::stable_sort(sorted.begin(), sorted.end(), [](const auto& a, const auto& b) { return a.second > b.second; });
    for (const auto& [key, n] : sorted) {
        std::printf("%5d  %-10s %-12s -> %s\n", n, std::get<0>(key).c_str(), std::get<1>(key).c_str(),
          std::get<2>(key).c_str());
    }
    std::printf("%5d  total\n", (int)violations.size());
}

int main(int argc, char** argv) {
    bool update = false;
    bool summary = false;
    fs::path root = fs::current_path();
    for (int i = 1; i < argc; ++i) {
        const std::string arg = argv[i];
        if (arg == "--update") {
            update = true;
        } else if (arg == "--summary") {
            summary = true;
        } else if (arg == "--root" && i + 1 < argc) {
            root = argv[++i];
        } else {
            std::fprintf(stderr, "usage: check_layers [--update] [--summary] [--root DIR]\n");
            return 2;
        }
    }

    for (size_t i = 0; i < LAYERS.size(); ++i) {
        for (const std::string& d : LAYERS[i].dirs) {
            g_rank[d] = (int)i;
            g_layer_name[d] = LAYERS[i].name;
        }
    }
    g_src = root / "src";
    const fs::path baseline_path = root / "tools" / "layers_baseline.txt";
    std::error_code ec;
    if (!fs::is_directory(g_src, ec)) {
        std::fprintf(stderr, "check_layers: no src/ under %s (use --root)\n", root.generic_string().c_str());
        return 2;
    }

    const std::set<std::string> current = collect();
    if (summary) {
        print_summary(current);
        return 0;
    }
    if (update) {
        write_baseline(baseline_path, current);
        std::printf("baseline updated: %d violations\n", (int)current.size());
        return 0;
    }

    const std::set<std::string> baseline = read_baseline(baseline_path);
    std::vector<std::string> added;
    std::vector<std::string> fixed;
    std::set_difference(current.begin(), current.end(), baseline.begin(), baseline.end(), std::back_inserter(added));
    std::set_difference(baseline.begin(), baseline.end(), current.begin(), current.end(), std::back_inserter(fixed));
    if (!fixed.empty()) {
        std::printf("%d baseline entries are fixed; remove them (or run --update):\n", (int)fixed.size());
        for (const std::string& v : fixed) {
            std::printf("  %s\n", v.c_str());
        }
    }
    if (!added.empty()) {
        std::printf("%d new layer violations (a file includes a header from a higher layer):\n", (int)added.size());
        for (const std::string& v : added) {
            std::printf("  %s\n", v.c_str());
        }
        std::printf("Layers, low to high: core < grid < sim < presentation < app\n");
        return 1;
    }
    std::printf("layer check passed: %d known violations, 0 new\n", (int)current.size());
    return 0;
}
