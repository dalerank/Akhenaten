#include "arguments.h"

#include "core/application.h"
#include "io/log.h"

#include <filesystem>

#define CURSOR_SCALE_ERROR_MESSAGE "Option --cursor-scale must be followed by a scale value of 1, 1.5 or 2"
#define DISPLAY_SCALE_ERROR_MESSAGE "Option --display-scale must be followed by a scale value between 0.5 and 5"
#define UNKNOWN_OPTION_ERROR_MESSAGE "Option %s not recognized"

namespace {
/// Create formatted string
/// NOTE: (use C++20 as soon as it will be available to get rid of this)
template <typename... Args>
auto string_format(char const* format, Args... args) {
    const int string_size = std::snprintf(nullptr, 0, format, args...) + 1; // With space for '\0'

    if (string_size <= 0)
        app::terminate("Error during string formatting.");

    std::unique_ptr<char[]> buf(new char[string_size]);
    std::snprintf(buf.get(), string_size, format, args...);
    return std::string(buf.get(), buf.get() + string_size - 1); // Without '\0'
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

Arguments::Arguments(int argc, char** argv)
  : data_directory_(std::filesystem::current_path().string()) {
    // TODO: load from settings file
    parse_cli_(argc, argv);
}

char const* Arguments::usage() {
    return "Usage: ozymandias [ARGS] [DATA_DIR]\n"
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
           "\n"
           "The last argument, if present, is interpreted as data directory of the Pharaoh installation";
}

bool Arguments::is_fullscreen() const {
    return !window_mode_;
}

bool Arguments::is_window_mode() const {
    return window_mode_;
}

int Arguments::get_display_scale_percentage() const {
    return display_scale_percentage_;
}

int Arguments::get_cursor_scale_percentage() const {
    return cursor_scale_percentage_;
}

std::string Arguments::get_renderer() const {
    return renderer_;
}

std::string Arguments::get_data_directory() const {
    return data_directory_;
}

void Arguments::set_data_directory(std::string value) {
    data_directory_ = std::move(value);
}

int Arguments::get_window_width() const {
    return window_width_;
}

void Arguments::set_window_width(int value) {
    window_width_ = value;
}

int Arguments::get_window_height() const {
    return window_height_;
}

void Arguments::set_window_height(int value) {
    window_height_ = value;
}

void Arguments::parse_cli_(int argc, char** argv) {
    for (int i = 1; i < argc; i++) {
        // ignore "-psn" arguments, this is needed to launch the app
        // from the Finder on macOS.
        // https://hg.libsdl.org/SDL/file/c005c49beaa9/test/testdropfile.c#l47
        if (SDL_strcmp(argv[i], "-psn") == 0)
            continue;
        else if (SDL_strcmp(argv[i], "--window") == 0)
            window_mode_ = true;
        else if (SDL_strcmp(argv[i], "--render") == 0) {
            if (i + 1 < argc) {
                renderer_ = argv[i + 1];
                ++i;
            } else
                app::terminate(DISPLAY_SCALE_ERROR_MESSAGE);
        } else if (SDL_strcmp(argv[i], "--display-scale") == 0) {
            if (i + 1 < argc) {
                int percentage = parse_decimal_as_percentage(argv[i + 1]);
                ++i;

                if (percentage < 50 || percentage > 500)
                    app::terminate(DISPLAY_SCALE_ERROR_MESSAGE);
                else
                    display_scale_percentage_ = percentage;
            } else
                app::terminate(DISPLAY_SCALE_ERROR_MESSAGE);
        } else if (SDL_strcmp(argv[i], "--size") == 0) {
            if (i + 1 < argc) {
                SDL_sscanf(argv[i + 1], "%dx%d", &window_width_, &window_height_);
                ++i;
            } else
                app::terminate(DISPLAY_SCALE_ERROR_MESSAGE);
        } else if (SDL_strcmp(argv[i], "--cursor-scale") == 0) {
            if (i + 1 < argc) {
                int percentage = parse_decimal_as_percentage(argv[i + 1]);
                ++i;

                if (percentage == 100 || percentage == 150 || percentage == 200)
                    cursor_scale_percentage_ = percentage;
                else
                    app::terminate(CURSOR_SCALE_ERROR_MESSAGE);
            } else
                app::terminate(CURSOR_SCALE_ERROR_MESSAGE);
        } else if (SDL_strcmp(argv[i], "--help") == 0)
            app::terminate(usage());
        else if (SDL_strncmp(argv[i], "--", 2) == 0) {
            app::terminate(string_format(UNKNOWN_OPTION_ERROR_MESSAGE, argv[i]));
        } else {
            // TODO: ???? check that there are no other arguments after
            data_directory_ = argv[i];
        }
    }
}
