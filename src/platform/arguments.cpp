#include "arguments.h"

#include "platform/platform.h"
#include "core/app.h"
#include "core/bstring.h"
#include "core/log.h"
#include "content/vfs.h"
#include "game/game.h"

#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <SDL_system.h>

#if defined(_WIN32) || defined(_WIN64)
#include <ShlObj.h>
#else // Linux
#include <unistd.h>
#include <pwd.h>
#endif

#define CURSOR_SCALE_ERROR_MESSAGE "Option --cursor-scale must be followed by a scale value of 1, 1.5 or 2"
#define DISPLAY_SCALE_ERROR_MESSAGE "Option --display-scale must be followed by a scale value between 0.5 and 5"
#define MIXED_MODE_ERROR_MESSAGE "Option --mixed should have path to script folder"
#define UNKNOWN_OPTION_ERROR_MESSAGE "Option %s not recognized"

Arguments g_args;

namespace {

auto const CFG_FILE_NAME = "akhenaten.cfg";
auto const CFG_FILE_DIR = "akhenaten";



/// Create formatted string
/// NOTE: (use C++20 as soon as it will be available to get rid of this)
template <typename... Args>
auto string_format(char const* format, Args... args) {
    const int string_size = std::snprintf(nullptr, 0, format, args...) + 1; // With space for '\0'

    if (string_size <= 0) {
        return std::string("");
    }

    std::unique_ptr<char[]> buf(new char[string_size]);
    std::snprintf(buf.get(), string_size, format, args...);
    return std::string(buf.get(), buf.get() + string_size - 1); // Without '\0'
}

std::string get_configuration_path() {
#if defined(_WIN32) || defined(_WIN64)
    TCHAR app_data_path[MAX_PATH];

    if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, app_data_path))) {
        return std::string(app_data_path) + '/' + CFG_FILE_NAME;
    }

    logs::error("Failed to retrieve AppData path.");
#else // Unix

    std::string cfg_dir_path;
    if (const char* xdg_cfg_dir_path = std::getenv("XDG_CONFIG_HOME")) {
        cfg_dir_path = std::string(xdg_cfg_dir_path) + '/' + CFG_FILE_DIR;
    } else {
        const passwd* pw = getpwuid(getuid());
        if (!pw || !pw->pw_dir) {
            logs::warn("Home folder to keep configuration file was not found");
            return CFG_FILE_NAME;
        }
        cfg_dir_path = std::string(pw->pw_dir) + "/.config/" + CFG_FILE_DIR;
    }

    // Try to create the directory, but continue even if it fails (directory might already exist)
    std::error_code ec;
    if (std::filesystem::create_directories(cfg_dir_path, ec)) {
        logs::info(("Created configuration directory " + cfg_dir_path).c_str());
    }
    else if (ec.value() != 0) {
        constexpr int buffer_size = 1000;
        auto const format = "Failed to create configuration directory %s; Error code: %i; Error message: %s";
        char err_msg[buffer_size];

        snprintf(err_msg, buffer_size, format, cfg_dir_path.c_str(), ec.value(), ec.message().c_str());
        logs::warn(err_msg);
        // Continue anyway - the directory might already exist and be readable
    }

    // Always return the full path, even if directory creation failed
    // The file might still be readable if it was manually created
    return cfg_dir_path + '/' + CFG_FILE_NAME;
#endif
    logs::warn("Home folder to keep configuration file was not found");

    return CFG_FILE_NAME;
}

static int parse_decimal_as_percentage(const char *str) {
    const char *start = str;
    char *end;
    long whole = SDL_strtol(start, &end, 10);
    int percentage = 100 * (int)whole;
    if (*end == ',' || *end == '.') {
        end++;
        start = end;
        long fraction = SDL_strtol(start, &end, 10);
        switch (end - start) {
        case 0:
            break;
        case 1:
            percentage += fraction * 10;
            break;
        case 2:
            percentage += fraction;
            break;
        default:
        {
            int fraction_digits = (int)(end - start);
            while (fraction_digits > 2) {
                fraction = fraction / 10;
                fraction_digits--;
            }
            percentage += fraction;
            break;
        }
        }
    }

    if (*end) {
        // still some characters left, print out warning
        logs::warn("Invalid decimal: %s", str);
        return -1;
    }
    return percentage;
}

} // namespace

ANK_REGISTER_BOOL_ARGUMENT_HANDLER("--window", "window", true, "enable window mode");
ANK_REGISTER_BOOL_ARGUMENT_HANDLER("--nosound", "sound", false, "not use sound manager");
ANK_REGISTER_BOOL_ARGUMENT_HANDLER("--logjsfiles", "logjsfiles", true, "print logs which files open with js");
ANK_REGISTER_BOOL_ARGUMENT_HANDLER("--nocrashdlg", "crashdlg", false, "do not show crash dialog");
ANK_REGISTER_BOOL_ARGUMENT_HANDLER("--fulldmp", "fulldmp", true, "create full dump on crash");
ANK_REGISTER_BOOL_ARGUMENT_HANDLER("--config", "config", true, "always show configuration window on startup");
ANK_REGISTER_BOOL_ARGUMENT_HANDLER("--save_debug_texture", "save_debug_texture", true, "save debug textures to DEV_TESTING/tex/");
ANK_REGISTER_BOOL_ARGUMENT_HANDLER("--unpack_scripts", "unpack_scripts", true, "unpack embedded scripts to user directory");

ANK_REGISTER_STRING_ARGUMENT_HANDLER("--render", "renderer", "Option --render must be opengl,direct3d", "--render RENDERER", "use specific renderer");
ANK_REGISTER_STRING_ARGUMENT_HANDLER("--extdata", "extdata_directory", "Option --extdata folder should exist", "--extdata PATH", "set external data directory path");
ANK_REGISTER_STRING_ARGUMENT_HANDLER("--mods", "mods_directory", "Option --mods folder should exist", "--mods PATH", "set mods data directory path");
ANK_REGISTER_STRING_ARGUMENT_HANDLER("--mixed", "scripts_directory", MIXED_MODE_ERROR_MESSAGE, "--mixed PATH", "hot reload scripts from disk");
ANK_REGISTER_STRING_ARGUMENT_HANDLER("--language", "language", "Option --language must be followed by a language code (e.g., ru, en, fr)", "--language CODE", "set game language (e.g., ru, en, fr, de, it, sp, po, pr, sw, tc, sc, kr)");
ANK_REGISTER_STRING_ARGUMENT_HANDLER("--font", "custom_font", "Option --font must be followed by a font file path", "--font PATH", "use custom TTF font file (overrides font from localization.js)");

// Register argument handler for --display-scale
std::optional<arguments::argument_result> handle_display_scale(int argc, char **argv, int current_index) {
    if (SDL_strcmp(argv[current_index], "--display-scale") == 0) {
        if (current_index + 1 < argc) {
            int percentage = parse_decimal_as_percentage(argv[current_index + 1]);
            if (percentage < 50 || percentage > 500) {
                app_terminate(DISPLAY_SCALE_ERROR_MESSAGE);
            }
            return arguments::argument_result("display_scale_percentage", bvariant(percentage), 2);
        } else {
            app_terminate(DISPLAY_SCALE_ERROR_MESSAGE);
        }
    }
    return std::nullopt;
}
ANK_REGISTER_ARGUMENT_HANDLER_WITH_DESC(handle_display_scale, "--display-scale NUMBER", "Scales the display by a factor of NUMBER. Number can be between 0.5 and 5");

// Register argument handler for --cursor-scale
std::optional<arguments::argument_result> handle_cursor_scale(int argc, char **argv, int current_index) {
    if (SDL_strcmp(argv[current_index], "--cursor-scale") == 0) {
        if (current_index + 1 < argc) {
            int percentage = parse_decimal_as_percentage(argv[current_index + 1]);
            if (percentage != 100 && percentage != 150 && percentage != 200) {
                app_terminate(CURSOR_SCALE_ERROR_MESSAGE);
            }
            return arguments::argument_result("cursor_scale_percentage", bvariant(percentage), 2);
        } else {
            app_terminate("Option --cursor-scale must be followed by a scale value between 0.5 and 5");
        }
    }
    return std::nullopt;
}
ANK_REGISTER_ARGUMENT_HANDLER_WITH_DESC(handle_cursor_scale, "--cursor-scale NUMBER", "Scales the mouse cursor by a factor of NUMBER. Number can be 1, 1.5 or 2");

// Register argument handler for --size
std::optional<arguments::argument_result> handle_size(int argc, char **argv, int current_index) {
    if (SDL_strcmp(argv[current_index], "--size") == 0) {
        if (current_index + 1 < argc) {
            vec2i size{800, 600};
            if (SDL_sscanf(argv[current_index + 1], "%dx%d", &size.x, &size.y) == 2) {
                return arguments::argument_result("window_size", bvariant(size), 2);
            } else {
                app_terminate("Option --size must should has fixed WxH format");
            }
        } else {
            app_terminate("Option --size must should has fixed WxH format");
        }
    }
    return std::nullopt;
}
ANK_REGISTER_ARGUMENT_HANDLER_WITH_DESC(handle_size, "--size WxH", "window size. Example: 800x600");


void Arguments::parse(int argc, char** argv) {
    xstring data_dir = std::filesystem::current_path().string().c_str();
#if defined(GAME_PLATFORM_WIN)
    auto get_steam_path = [] () {
        DWORD dwType = REG_SZ;
        HKEY hKey = 0;
        char value[1024] = {0};
        DWORD value_length = 1024;
        RegOpenKeyA(HKEY_CURRENT_USER, "SOFTWARE\\Valve\\Steam", &hKey);
        RegQueryValueExA(hKey, "SteamPath", NULL, &dwType, (LPBYTE)&value, &value_length);
        return bstring256(value);
    };

    bstring256 steam_path = get_steam_path();
    if (!steam_path.empty()) {
        vfs::path pharaoh_steam_path(steam_path, "/steamapps/common/Pharaoh + Cleopatra/");
        vfs::path pharaoh_exe_path(pharaoh_steam_path, "Pharaoh.exe");
        bool binary_exist = std::filesystem::exists(pharaoh_exe_path.c_str());
        if (binary_exist) {
            logs::info("Steam pharaoh path: %s", pharaoh_steam_path);
            data_dir = pharaoh_steam_path.c_str();
        }
    }
#endif
    args_["data_directory"] = bvariant(data_dir);    
    const bool file_exists = arguments::load(*this);
    args_["config_file_exists"] = bvariant(file_exists);
    parse_cli_(argc, argv);
    
    // Apply save_debug_texture from args to game
    if (is("save_debug_texture", false)) {
        game.save_debug_texture = true;
    }
}

char const* Arguments::usage() {
    static std::string usage_text;
    if (usage_text.empty()) {
        usage_text = "Usage: akhenaten [ARGS] [DATA_DIR]\n"
                     "\n"
                     "ARGS may be:\n";
        
        auto descriptions = arguments::get_argument_descriptions();
        // Sort by argument name for consistent output
        std::sort(descriptions.begin(), descriptions.end(), 
                  [](const auto& a, const auto& b) { return a.first < b.first; });
        
        for (const auto& desc : descriptions) {
            bstring1024 help;
            help.append_fmt("  %s\n", desc.first.c_str());
            help.append_fmt("          %s\n", desc.second.c_str());
            usage_text.append(help.c_str());
        }
        
        usage_text += "\n"
                      "The last argument, if present, is interpreted as data directory of the Pharaoh installation";
    }
    return usage_text.c_str();
}

bool Arguments::is(const xstring & name, bool def) const {
    const auto& fullscreen = get_arg(name);
    if (fullscreen.is_bool()) {
        return fullscreen.as_bool();
    }

    return def;
}

int Arguments::get_display_scale_percentage() const {
    const auto& scale = get_arg("display_scale_percentage");
    if (scale.is_int32()) {
        return scale.as_int32();
    }
    return 100; // default value
}

void Arguments::set_display_scale_percentage(int value) {
    args_["display_scale_percentage"] = bvariant(std::clamp(value, 50, 500));
}

int Arguments::get_cursor_scale_percentage() const {
    const auto& scale = get_arg("cursor_scale_percentage");
    if (scale.is_int32()) {
        return scale.as_int32();
    }
    return 100; // default value
}

void Arguments::set_cursor_scale_percentage(int value) {
    args_["cursor_scale_percentage"] = bvariant(std::clamp(value, 100, 200));
}

void Arguments::set_renderer(pcstr value) {
    args_["renderer"] = xstring(value);
}

void Arguments::set_data_directory(pcstr value) {
    args_["data_directory"] = bvariant(xstring(value));
}

const xstring& Arguments::get_str(const xstring& name) const {
    const bvariant& font = get_arg(name);
    if (font.is_str() && !font.as_str().empty()) {
        return font.as_str();
    }

    static const xstring dummy;
    return dummy;
}

void Arguments::set_custom_font(pcstr value) {
    args_["custom_font"] = bvariant(xstring(value));
}

vec2i Arguments::get_window_size() const {
    const bvariant& size = get_arg("window_size");
    if (size.is_vec2i()) {
        return size.as_vec2i();
    }
    return vec2i{800, 600}; // default value
}

void Arguments::set_window_size(vec2i value) {
    args_["window_size"] = bvariant(value);
}

void Arguments::parse_cli_(int argc, char** argv) {
    for (int i = 1; i < argc; i++) {
        // ignore "-psn" arguments, this is needed to launch the app
        // from the Finder on macOS.
        // https://hg.libsdl.org/SDL/file/c005c49beaa9/test/testdropfile.c#l47
        if (SDL_strcmp(argv[i], "-psn") == 0) {
            continue;
        }

        // Try registered argument handlers first
        bool handled = false;
        for (arguments::ArgumentHandler *s = arguments::ArgumentHandler::tail; s; s = s->next) {
            auto result = s->func(argc, argv, i);
            if (result.has_value()) {
                args_[result->name] = result->value;
                i += result->consumed_args - 1; // -1 because the loop will increment i
                handled = true;
                break;
            }
        }
        if (handled) {
            continue;
        }

        if (SDL_strcmp(argv[i], "--help") == 0) {
            app_terminate(usage());

        } else if (SDL_strncmp(argv[i], "--", 2) == 0) {
            logs::info(bstring256(UNKNOWN_OPTION_ERROR_MESSAGE, argv[i]));

        } else {
            // TODO: ???? check that there are no other arguments after
            args_["data_directory"] = bvariant(xstring(argv[i]));
        }
    }
}

const bvariant& Arguments::get_arg(const xstring& name) const {
    auto it = args_.find(name);
    if (it != args_.end()) {
        return it->second;
    }

    static bvariant dummy;
    return dummy;
}

bool Arguments::has_arg(const xstring& name) const {
    return args_.find(name) != args_.end();
}

namespace arguments {

bool load(Arguments& arguments) {
    std::ifstream input(get_configuration_path(), std::ios::in);

    if (!input.is_open()) {
        logs::info("Configuration file was not found.");
        return false;
    } 
    
    std::string line;
    while (std::getline(input, line)) {
        auto pos = line.find('=');
        if (pos == std::string::npos)
            continue;

        auto const key = line.substr(0, pos);
        auto const value = line.substr(pos + 1);

        if (key == "data_directory") {
            arguments.set_data_directory(value.c_str());
        } else if (key == "window_mode") {
            if (value == "1")
                arguments.set_window_mode();
            else
                arguments.set_fullscreen();
        } else if (key == "renderer") {
            arguments.set_renderer(value.c_str());
        } else if (key == "display_scale_percentage") {
            arguments.set_display_scale_percentage(std::stoi(value));
        } else if (key == "cursor_scale_percentage") {
            arguments.set_cursor_scale_percentage(std::stoi(value));
        } else if (key == "window_width") {
            auto v = arguments.get_window_size();
            v.x = std::stoi(value);
            arguments.set_window_size(v);
        } else if (key == "window_height") {
            auto v = arguments.get_window_size();
            v.y = std::stoi(value);
            arguments.set_window_size(v);
        } else if (key == "custom_font") {
            arguments.set_custom_font(value.c_str());
        } else {
            logs::warn("Unknown argument key: %s", key.c_str());
        }
    }
    return true;
}

void store(Arguments const& arguments) {
    std::ofstream output(get_configuration_path(), std::ios::trunc | std::ios::out);

    output << "data_directory" << '=' << arguments.get_data_directory().c_str() << '\n';
    output << "window_mode" << '=' << arguments.is_window_mode() << '\n';
    output << "renderer" << '=' << arguments.get_renderer().c_str() << '\n';
    output << "display_scale_percentage" << '=' << arguments.get_display_scale_percentage() << '\n';
    output << "cursor_scale_percentage" << '=' << arguments.get_cursor_scale_percentage() << '\n';
    output << "window_width" << '=' << arguments.get_window_size().x << '\n';
    output << "window_height" << '=' << arguments.get_window_size().y << '\n';
    if (!arguments.get_custom_font().empty()) {
        output << "custom_font" << '=' << arguments.get_custom_font().c_str() << '\n';
    }
}

std::vector<std::pair<xstring, xstring>> get_argument_descriptions() {
    std::vector<std::pair<xstring, xstring>> descriptions;
    for (ArgumentInfo *s = ArgumentInfo::tail; s; s = s->next) {
        if (s->func) {
            argument_info* info = s->func;
            descriptions.emplace_back(info->arg_name, info->description);
        }
    }
    return descriptions;
}

} // namespace arguments
