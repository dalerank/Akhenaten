#pragma once

#include "content/vfs.h"
#include "game/settings.h"
#include "core/core.h"
#include "core/variant.h"
#include <optional>

class Arguments;

namespace arguments {
    struct argument_result {
        xstring name;
        bvariant value;
        int consumed_args;
        
        argument_result() : consumed_args(1) {}
        argument_result(const xstring& n, const bvariant& v, int consumed = 1) 
            : name(n), value(v), consumed_args(consumed) {}
    };
    
    struct argument_info {
        xstring arg_name;      // имя аргумента (например, "--window")
        xstring description;   // описание аргумента
        
        argument_info(const xstring& name, const xstring& desc) 
            : arg_name(name), description(desc) {}
    };
    
    using argument_handler_cb = std::optional<argument_result>(int argc, char** argv, int current_index);
    using ArgumentHandler = FuncLinkedList<argument_handler_cb*>;
    using ArgumentInfo = FuncLinkedList<argument_info*>;

    /// Load configuration from the file (if exists)
    /// @return true if configuration fil was found and loaded, false otherwise
    bool load(Arguments &arguments);

    /// Store configuration to the file system
    void store(Arguments const &arguments);
    
    /// Get all registered argument descriptions
    /// @return vector of pairs (argument_name, description)
    std::vector<std::pair<xstring, xstring>> get_argument_descriptions();
}

class Arguments {
public:
    static char const* usage();

    [[nodiscard]] bool is_fullscreen() const { return !is("window", false); }
    void set_fullscreen() { args_["window"] = bvariant(false); }

    [[nodiscard]] bool use_sound() const { return is("sound", true); }
    void set_use_sound(bool flag = true) { args_["sound"] = bvariant(flag); }

    [[nodiscard]] bool is_window_mode() const { return is("window", false); }
    void set_window_mode(bool flag = true) { args_["window"] = flag; }

    [[nodiscard]] bool is_logjsfiles() const { return is("logjsfiles", false); }

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

    [[nodiscard]] bool use_crashdlg() const { return is("crashdlg", true); }
    [[nodiscard]] bool create_fulldmp() const { return is("fulldmp", false); }
    [[nodiscard]] bool should_show_config_window() const { return is("config", false); }
    [[nodiscard]] bool config_file_exists() const { return is("config_file_exists", false); }
    [[nodiscard]] bool should_unpack_scripts() const { return is("unpack_scripts", false); }
    [[nodiscard]] const char* get_language() const {
        auto lang = get_arg("language");
        if (lang && lang->is_str() && !lang->as_str().empty()) {
            return lang->as_str().c_str();
        }
        return nullptr;
    }

    [[nodiscard]] const char* get_scripts_directory() const;
    void parse(int argc, char **argv);

    bool is(const xstring &name, bool def) const;

    /// Get a custom argument value by name
    /// @return optional bvariant if the argument was set, empty optional otherwise
    [[nodiscard]] std::optional<bvariant> get_arg(const xstring& name) const;
    
    /// Check if a custom argument exists
    [[nodiscard]] bool has_arg(const xstring& name) const;

private:
    bvariant_map args_;

    /// apply parameters from command line
    void parse_cli_(int argc, char** argv);
};

extern Arguments g_args;

#define ANK_REGISTER_ARGUMENT_HANDLER(func) \
    namespace arguments {int ANK_CONFIG_PULL_VAR_NAME(func) = 1;} \
    static arguments::ArgumentHandler ANK_CONFIG_CC1(arg_handler, __LINE__)(func); \
    std::optional<arguments::argument_result> func(int argc, char** argv, int current_index)

#define ANK_REGISTER_ARGUMENT_HANDLER_WITH_DESC(func, arg_name, description) \
    namespace arguments {int ANK_CONFIG_PULL_VAR_NAME(func) = 1;} \
    static arguments::ArgumentHandler ANK_CONFIG_CC1(arg_handler, __LINE__)(func); \
    static arguments::argument_info ANK_CONFIG_CC1(arg_info_obj, __LINE__)(arg_name, description); \
    static arguments::ArgumentInfo ANK_CONFIG_CC1(arg_info_list, __LINE__)(&ANK_CONFIG_CC1(arg_info_obj, __LINE__)); \
    std::optional<arguments::argument_result> func(int argc, char** argv, int current_index)

#define ANK_REGISTER_BOOL_ARGUMENT_HANDLER(arg_name, storage_name, value, description) \
    std::optional<arguments::argument_result> ANK_CONFIG_CC1(handle_, __LINE__)(int argc, char **argv, int current_index) { \
        if (strcmp(argv[current_index], arg_name) == 0) { \
            return arguments::argument_result(storage_name, bvariant(value), 1); \
        } \
        return std::nullopt; \
    } \
    ANK_REGISTER_ARGUMENT_HANDLER_WITH_DESC(ANK_CONFIG_CC1(handle_, __LINE__), arg_name, description)
