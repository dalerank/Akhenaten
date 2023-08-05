#pragma once

#include <stdexcept>
#include <string>


class Arguments {
public:
    /// Exception thrown when CLI arguments cannot be parsed.
    class CliParseError : public std::runtime_error {
    public:
        explicit CliParseError(char const* description)
          : std::runtime_error(description) {
        }

        explicit CliParseError(std::string const& description)
          : std::runtime_error(description) {
        }
    };

    /// Exception thrown when --help was requested.
    class CliHelpRequested : public std::runtime_error {
    public:
        CliHelpRequested()
          : std::runtime_error("Help was requested.") {
        }
    };

    Arguments(int argc, char** argv);

    static char const* usage();

    [[nodiscard]] bool is_fullscreen() const;
    [[nodiscard]] bool is_window_mode() const;

    [[nodiscard]] int get_display_scale_percentage() const;

    [[nodiscard]] int get_cursor_scale_percentage() const;

    [[nodiscard]] std::string get_renderer() const;

    [[nodiscard]] std::string get_data_directory() const;
    void set_data_directory(std::string value);

    [[nodiscard]] int get_window_width() const;
    void set_window_width(int value);

    [[nodiscard]] int get_window_height() const;
    void set_window_height(int value);

private:
    std::string version_;
    std::string data_directory_;
    std::string renderer_;
    int display_scale_percentage_ = 100;
    int cursor_scale_percentage_ = 100;
    int window_width_ = 800;
    int window_height_ = 600;
    bool window_mode_ = false;

    void parse_cli_(int argc, char** argv);
};
