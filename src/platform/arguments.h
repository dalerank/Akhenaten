#pragma once

#include "content/vfs.h"
#include "game/settings.h"

class Arguments {
public:
    static char const* usage();

    [[nodiscard]] bool is_fullscreen() const;
    void set_fullscreen();

    [[nodiscard]] bool use_sound() const;
    void set_use_sound(bool flag = true);

    [[nodiscard]] bool is_window_mode() const;
    void set_window_mode(bool flag = true);

    [[nodiscard]] bool is_logjsfiles() const { return logjsfiles_; }

    [[nodiscard]] int get_display_scale_percentage() const;
    void set_display_scale_percentage(int value);

    [[nodiscard]] int get_cursor_scale_percentage() const;
    void set_cursor_scale_percentage(int value);

    [[nodiscard]] pcstr get_renderer() const;
    void set_renderer(pcstr value);

    [[nodiscard]] const char* get_data_directory() const;
    void set_data_directory(const char *value);

    [[nodiscard]] const char* get_extdata_directory() const;

    [[nodiscard]] vec2i get_window_size() const;
    void set_window_size(vec2i value);

    [[nodiscard]] bool use_crashdlg() const { return use_crashdlg_; }
    [[nodiscard]] bool create_fulldmp() const { return create_fulldmp_; }
    [[nodiscard]] bool should_show_config_window() const { return show_config_window_; }
    [[nodiscard]] bool config_file_exists() const { return config_file_exists_; }
    [[nodiscard]] bool should_unpack_scripts() const { return unpack_scripts_; }

    [[nodiscard]] const char* get_scripts_directory() const;
    void parse(int argc, char **argv);

private:
    vfs::path data_directory_;
    vfs::path extdata_directory_;
    vfs::path scripts_directory_;

    bstring64 renderer_;
    int display_scale_percentage_ = 100;
    int cursor_scale_percentage_ = 100;
    vec2i window_size_ = {800, 600};
    bool window_mode_ = false;
    bool use_sound_ = true;
    bool use_crashdlg_ = true;
    bool create_fulldmp_ = false;
    bool logjsfiles_ = false;
    bool show_config_window_ = false;
    bool config_file_exists_ = false;
    bool unpack_scripts_ = false;

    /// apply parameters from command line
    void parse_cli_(int argc, char** argv);
};

extern Arguments g_args;

namespace arguments {

/// Load configuration from the file (if exists)
/// @return true if configuration file was found and loaded, false otherwise
bool load(Arguments& arguments);

/// Store configuration to the file system
void store(Arguments const& arguments);

} // namespace arguments
