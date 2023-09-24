#pragma once

#include "content/vfs.h"
#include "game/settings.h"

class Arguments {
public:
    Arguments(int argc, char** argv);

    static char const* usage();

    [[nodiscard]] bool is_fullscreen() const;
    void set_fullscreen();

    [[nodiscard]] bool is_window_mode() const;
    void set_window_mode(bool flag = true);

    [[nodiscard]] int get_display_scale_percentage() const;
    void set_display_scale_percentage(int value);

    [[nodiscard]] int get_cursor_scale_percentage() const;
    void set_cursor_scale_percentage(int value);

    [[nodiscard]] const char* get_renderer() const;
    void set_renderer(const char* value);

    [[nodiscard]] const char* get_data_directory() const;
    void set_data_directory(const char *value);

    [[nodiscard]] display_size get_window_size() const;
    void set_window_size(display_size value);

    [[nodiscard]] const char* get_scripts_directory() const;

private:
    vfs::path data_directory_;
    vfs::path scripts_directory_;

    bstring64 renderer_;
    int display_scale_percentage_ = 100;
    int cursor_scale_percentage_ = 100;
    display_size window_size_ = {800, 600};
    bool window_mode_ = false;

    /// apply parameters from command line
    void parse_cli_(int argc, char** argv);
};

namespace arguments {

/// Load configuration from the file (if exists)
void load(Arguments& arguments);

/// Store configuration to the file system
void store(Arguments const& arguments);

} // namespace arguments
