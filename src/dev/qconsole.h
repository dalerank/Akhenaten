#pragma once

#include "dev/console_io.h"
#include "content/path.h"
#include "core/xstring.h"

#include <deque>
#include <unordered_map>

namespace dev {

class qconsole {
public:
    static const unsigned int default_history_size = 10u;

    using history_line = bstring512;

    struct cvar {
        std::function<bool(console_args &)> set; // false on a parse error; the variable stays untouched
        std::function<void(bstring256 &)> get;
    };

    using command_table = std::unordered_map<xstring, console_command_fn>;
    using cvar_table = std::unordered_map<xstring, cvar>;
    using help_table = std::unordered_map<xstring, xstring>;

    struct styling {
        pcstr error_begin, error_end;
        pcstr warning_begin, warning_end;
        pcstr echo_begin, echo_end;
    };

    static styling styling_color() { return { "\u001b[37;41;1m[error]: ", "\u001b[0m", "\u001b[33;1m[warning]: ", "\u001b[0m", "\u001b[32;1m> ", "\u001b[0m" }; }
    static styling styling_plain() { return { "[error]: ", "", "[warning]: ", "", "> ", "" }; }

    styling style = styling_plain();

    qconsole(size_t max_history = default_history_size);

    void execute(pcstr line, console_output &out);
    void execute_file(pcstr filename, console_output &out);

    void bind_command(pcstr name, console_command_fn fn, pcstr help = nullptr);
    void set_help(pcstr topic, pcstr text);

    void bind_cvar(pcstr name, int &var, pcstr help = nullptr);
    void bind_cvar(pcstr name, int8_t &var, pcstr help = nullptr);
    void bind_cvar(pcstr name, int16_t &var, pcstr help = nullptr);
    void bind_cvar(pcstr name, uint8_t &var, pcstr help = nullptr);
    void bind_cvar(pcstr name, float &var, pcstr help = nullptr);
    void bind_cvar(pcstr name, bool &var, pcstr help = nullptr);

    bool load_history(const vfs::path &filename);
    void save_history(const vfs::path &filename) const;

    const std::deque<history_line> &history() const { return _history; }
    const command_table &commands() const { return _commands; }
    const cvar_table &cvars() const { return _cvars; }
    const help_table &help() const { return _help; }

    template<typename... Args>
    void error(console_output &out, pcstr fmt, const Args &...args) {
        out.print(style.error_begin);
        out.printf(fmt, args...);
        out.print(style.error_end);
        out.print("\n");
    }

private:
    template<typename T>
    void bind_cvar_t(pcstr name, T &var, pcstr help);

    void push_history(pcstr line);
    void expand_variables(pcstr line, bstring1024 &result, console_output &out);
    void bind_basic_commands();

    void cmd_list_cmds(console_output &out) const;
    void cmd_list_cvars(console_output &out) const;
    void cmd_events_history(console_args &args, console_output &out) const;
    void cmd_set(console_args &args, console_output &out);
    void cmd_echo(console_args &args, console_output &out);
    void cmd_help(console_args &args, console_output &out);
    void cmd_var(console_args &args, console_output &out);

    size_t _max_history;
    std::deque<history_line> _history;
    command_table _commands;
    cvar_table _cvars;
    help_table _help;
    std::unordered_map<xstring, bstring256> _dynamic_vars; // node-based: cvar closures keep references into it
};

} // namespace dev
