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

enum class argument_type {
    DATA_DIRECTORY,
    WINDOW_MODE,
    RENDERER,
    DISPLAY_SCALE_PERCENTAGE,
    CURSOR_SCALE_PERCENTAGE,
    WINDOW_WIDTH,
    WINDOW_HEIGHT,
    MIXED_MODE,
    EXTDATA_FOLDER,
};

const std::unordered_map<std::string, argument_type> argument_types{{"data_directory", argument_type::DATA_DIRECTORY},
                                                                    {"extdata", argument_type::DATA_DIRECTORY},
                                                                    {"window_mode", argument_type::WINDOW_MODE},
                                                                    {"renderer", argument_type::RENDERER},
                                                                    {"display_scale_percentage",argument_type::DISPLAY_SCALE_PERCENTAGE},
                                                                    {"cursor_scale_percentage",argument_type::CURSOR_SCALE_PERCENTAGE},
                                                                    {"window_width", argument_type::WINDOW_WIDTH},
                                                                    {"window_height", argument_type::WINDOW_HEIGHT},
                                                                    {"mixed", argument_type::MIXED_MODE}};

void set_value(Arguments& arguments, argument_type type, std::string&& value) {
    switch (type) {
    case argument_type::DATA_DIRECTORY:
        arguments.set_data_directory(value.c_str());
        break;
    case argument_type::WINDOW_MODE:
        if (value == "1")
            arguments.set_window_mode();
        else
            arguments.set_fullscreen();
        break;
    case argument_type::RENDERER:
        arguments.set_renderer(value.c_str());
        break;
    case argument_type::DISPLAY_SCALE_PERCENTAGE:
        arguments.set_display_scale_percentage(std::stoi(value));
        break;
    case argument_type::CURSOR_SCALE_PERCENTAGE:
        arguments.set_cursor_scale_percentage(std::stoi(value));
        break;
    case argument_type::WINDOW_WIDTH: {
        auto v = arguments.get_window_size();
        v.x = std::stoi(value);
        arguments.set_window_size(v);
        break;
    }
    case argument_type::WINDOW_HEIGHT: {
        auto v = arguments.get_window_size();
        v.y = std::stoi(value);
        arguments.set_window_size(v);
        break;
    }
    default:
        ; // nothing
    };
}

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
        cfg_dir_path = std::string(pw->pw_dir) + "/.config/" + CFG_FILE_DIR;
    }

    if (std::error_code ec; std::filesystem::create_directories(cfg_dir_path, ec)) {

        logs::info(("Created configuration directory " + cfg_dir_path).c_str());
    }
    else if (ec.value() != 0) {
        constexpr int buffer_size = 1000;
        auto const format = "Failed to create configuration directory %s; Error code: %i; Error message: %s";
        char err_msg[buffer_size];

        snprintf(err_msg, buffer_size, format, cfg_dir_path.c_str(), ec.value(), ec.message().c_str());
        logs::error(err_msg);
        return CFG_FILE_NAME;
    }

    if (std::filesystem::exists(cfg_dir_path))
        return cfg_dir_path + '/' + CFG_FILE_NAME;
#endif
    logs::warn("Home folder to keep configuration file was not found");

    return CFG_FILE_NAME;
}

} // namespace

static int parse_decimal_as_percentage(const char* str) {
    const char* start = str;
    char* end;
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
        default: {
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

void Arguments::parse(int argc, char** argv) {
    data_directory_ = std::filesystem::current_path().string().c_str();
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
            data_directory_ = pharaoh_steam_path;
        }
    }
#endif
    arguments::load(*this);
    parse_cli_(argc, argv);
}

char const* Arguments::usage() {
    return "Usage: akhenaten [ARGS] [DATA_DIR]\n"
           "\n"
           "ARGS may be:\n"
           "  --display-scale NUMBER\n"
           "          Scales the display by a factor of NUMBER. Number can be between 0.5 and 5\n"
           "  --cursor-scale NUMBER\n"
           "          Scales the mouse cursor by a factor of NUMBER. Number can be 1, 1.5 or 2\n"
           "  --render\n"
           "          use specific renderer\n"
           "  --size\n"
           "          window size. Example: 800x600\n"
           "  --window\n"
           "          enable window mode\n"
           "  --mixed\n"
           "          hot reload scripts from disk\n"
           "  --nosound\n"
           "          not use sound manager\n"
           "  --nocrashdlg\n"
           "          do not show crash dialog\n"
           "  --fulldmp\n"
           "         create full dump on crash\n"
           "  --logjsfiles\n"
           "         print logs which files open with js\n"
           "  --config\n"
           "         always show configuration window on startup\n"
           "\n"
           "The last argument, if present, is interpreted as data directory of the Pharaoh installation";
}

bool Arguments::is_fullscreen() const {
    return !window_mode_;
}

bool Arguments::use_sound() const {
    return use_sound_;
}

void Arguments::set_use_sound(bool flag) {
    use_sound_ = flag;
}

void Arguments::set_fullscreen() {
    window_mode_ = false;
}

bool Arguments::is_window_mode() const {
    return window_mode_;
}

void Arguments::set_window_mode(bool flag) {
    window_mode_ = flag;
}

int Arguments::get_display_scale_percentage() const {
    return display_scale_percentage_;
}

void Arguments::set_display_scale_percentage(int value) {
    if (value < 50 || value > 500) {
        app_terminate(DISPLAY_SCALE_ERROR_MESSAGE);
    }

    display_scale_percentage_ = value;
}

int Arguments::get_cursor_scale_percentage() const {
    return cursor_scale_percentage_;
}

void Arguments::set_cursor_scale_percentage(int value) {
    if (value != 100 && value != 150 && value != 200) {
        app_terminate(CURSOR_SCALE_ERROR_MESSAGE);
    }

    cursor_scale_percentage_ = value;
}

pcstr Arguments::get_renderer() const {
    return renderer_.c_str();
}

void Arguments::set_renderer(pcstr value) {
    renderer_ = value;
}

const char *Arguments::get_data_directory() const {
    return data_directory_;
}

void Arguments::set_data_directory(const char * value) {
    data_directory_ = value;
}

const char *Arguments::get_extdata_directory() const {
    return extdata_directory_;
}

const char *Arguments::get_scripts_directory() const {
    return scripts_directory_;
}

vec2i Arguments::get_window_size() const {
    return window_size_;
}

void Arguments::set_window_size(vec2i value) {
    window_size_ = value;
}

void Arguments::parse_cli_(int argc, char** argv) {
    for (int i = 1; i < argc; i++) {
        // ignore "-psn" arguments, this is needed to launch the app
        // from the Finder on macOS.
        // https://hg.libsdl.org/SDL/file/c005c49beaa9/test/testdropfile.c#l47
        if (SDL_strcmp(argv[i], "-psn") == 0) {
            continue;

        } else if (SDL_strcmp(argv[i], "--window") == 0) {
            window_mode_ = true;
        } else if (SDL_strcmp(argv[i], "--logjsfiles") == 0) {
            logjsfiles_ = true;
        } else if (SDL_strcmp(argv[i], "--config") == 0) {
            show_config_window_ = true;
        } else if (SDL_strcmp(argv[i], "--nosound") == 0) {
            use_sound_ = false;
        } else if (SDL_strcmp(argv[i], "--nocrashdlg") == 0) {
            use_crashdlg_ = false;        
        } else if (SDL_strcmp(argv[i], "--fulldmp") == 0) {
            create_fulldmp_ = true;
        } else if (SDL_strcmp(argv[i], "--render") == 0) {
            if (i + 1 < argc) {
                renderer_ = argv[i + 1];
                ++i;
            } else {
                app_terminate("Option --render must be opengl,direct3d");
            }
        } else if (SDL_strcmp(argv[i], "--display-scale") == 0) {
            if (i + 1 < argc) {
                int percentage = parse_decimal_as_percentage(argv[i + 1]);
                ++i;

                set_display_scale_percentage(percentage);
            } else
                app_terminate(DISPLAY_SCALE_ERROR_MESSAGE);
        } else if (SDL_strcmp(argv[i], "--size") == 0) {
            if (i + 1 < argc) {
                SDL_sscanf(argv[i + 1], "%dx%d", &window_size_.x, &window_size_.y);
                ++i;
            } else {
                app_terminate("Option --size must should has fixed WxH format");
            }
        } else if (SDL_strcmp(argv[i], "--extdata") == 0) {
            if (i + 1 < argc) {
                extdata_directory_ = argv[i + 1];
                ++i;
            } else {
                app_terminate("Option --extdata folder should exist");
            }
        } else if (SDL_strcmp(argv[i], "--mixed") == 0) {
            if (i + 1 < argc) {
                scripts_directory_ = argv[i + 1];
                ++i;
            } else {
                app_terminate("Option --mixed folder should exist");
            }

        } else if (SDL_strcmp(argv[i], "--cursor-scale") == 0) {
            if (i + 1 < argc) {
                int percentage = parse_decimal_as_percentage(argv[i + 1]);
                ++i;

                set_cursor_scale_percentage(percentage);
            } else {
                app_terminate("Option --cursor-scale must be followed by a scale value between 0.5 and 5");
            }
        } else if (SDL_strcmp(argv[i], "--help") == 0) {
            app_terminate(usage());

        } else if (SDL_strcmp(argv[i], "--save_debug_texture") == 0) {
            game.save_debug_texture = true;

        } else if (SDL_strncmp(argv[i], "--", 2) == 0) {
            logs::info(bstring256(UNKNOWN_OPTION_ERROR_MESSAGE, argv[i]));

        } else {
            // TODO: ???? check that there are no other arguments after
            data_directory_ = argv[i];
        }
    }
}

namespace arguments {

void load(Arguments& arguments) {
    std::ifstream input(get_configuration_path(), std::ios::in);

    if (!input.is_open()) {
        logs::info("Configuration file was not found.");
    } else {
        std::string line;
        while (std::getline(input, line)) {
            auto pos = line.find('=');
            if (pos == std::string::npos)
                continue;

            auto const key = line.substr(0, pos);
            auto const it = argument_types.find(key);
            if (it == argument_types.end()) {
                logs::warn("Unknown argument key: %s", key.c_str());
                continue;
            }

            set_value(arguments, it->second, line.substr(pos + 1));
        }
    }
}

void store(Arguments const& arguments) {
    std::ofstream output(get_configuration_path(), std::ios::trunc | std::ios::out);

    output << "data_directory" << '=' << arguments.get_data_directory() << '\n';
    output << "window_mode" << '=' << arguments.is_window_mode() << '\n';
    output << "renderer" << '=' << arguments.get_renderer() << '\n';
    output << "display_scale_percentage" << '=' << arguments.get_display_scale_percentage() << '\n';
    output << "cursor_scale_percentage" << '=' << arguments.get_cursor_scale_percentage() << '\n';
    output << "window_width" << '=' << arguments.get_window_size().x << '\n';
    output << "window_height" << '=' << arguments.get_window_size().y << '\n';
}

} // namespace arguments
