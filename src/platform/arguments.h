#pragma once

#include <stdexcept>
#include <string>

#include "game/settings.h"

class Arguments {
public:
    Arguments(int argc, char** argv);

    static char const* usage();

    [[nodiscard]] int get_fullscreen() const;
    [[nodiscard]] int get_window_mode() const;

    [[nodiscard]] int get_display_scale_percentage() const;

    [[nodiscard]] int get_cursor_scale_percentage() const;

    [[nodiscard]] std::string get_renderer() const;

    [[nodiscard]] std::string get_data_directory() const;
    void set_data_directory(std::string value);

    [[nodiscard]] display_size get_window_size() const;
    void set_window_size(display_size value);

private:
    std::string version_;
    std::string data_directory_;
    std::string renderer_;
    int display_scale_percentage_ = 100;
    int cursor_scale_percentage_ = 100;
    display_size window_size_ = {800, 600};
    int window_mode_ = -1;

    void parse_cli_(int argc, char** argv);
};
