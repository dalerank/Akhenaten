#include "qconsole.h"

#include "content/vfs.h"
#include "game/game_events_history.h"

#include <climits>
#include <cstdio>
#include <vector>

namespace {

bool read_cvar(console_args &args, int &v) { return args.next(v); }
bool read_cvar(console_args &args, float &v) { return args.next(v); }
bool read_cvar(console_args &args, bool &v) { return args.next(v); }

template<typename T>
bool read_ranged_cvar(console_args &args, T &v, int lo, int hi) {
    int tmp;
    if (!args.next(tmp) || tmp < lo || tmp > hi) {
        return false;
    }
    v = (T)tmp;
    return true;
}

bool read_cvar(console_args &args, int8_t &v) { return read_ranged_cvar(args, v, INT8_MIN, INT8_MAX); }
bool read_cvar(console_args &args, int16_t &v) { return read_ranged_cvar(args, v, INT16_MIN, INT16_MAX); }
bool read_cvar(console_args &args, uint8_t &v) { return read_ranged_cvar(args, v, 0, UINT8_MAX); }

void format_cvar(bstring256 &out, int v) { out.printf("%d", v); }
void format_cvar(bstring256 &out, int8_t v) { out.printf("%d", (int)v); }
void format_cvar(bstring256 &out, int16_t v) { out.printf("%d", (int)v); }
void format_cvar(bstring256 &out, uint8_t v) { out.printf("%d", (int)v); }
void format_cvar(bstring256 &out, float v) { out.printf("%g", v); }
void format_cvar(bstring256 &out, bool v) { out = v ? "1" : "0"; }

void strip_line_end(pstr s) {
    size_t len = ::strlen(s);
    while (len > 0 && ::isspace((unsigned char)s[len - 1])) {
        s[--len] = 0;
    }
}

} // namespace

dev::qconsole::qconsole(size_t max_history) : _max_history(max_history) {
    bind_basic_commands();
}

void dev::qconsole::bind_command(pcstr name, console_command_fn fn, pcstr help) {
    _commands[xstring(name)] = std::move(fn);
    if (help && *help) {
        set_help(name, help);
    }
}

void dev::qconsole::set_help(pcstr topic, pcstr text) {
    _help[xstring(topic)] = xstring(text);
}

template<typename T>
void dev::qconsole::bind_cvar_t(pcstr name, T &var, pcstr help) {
    cvar &cv = _cvars[xstring(name)];
    cv.set = [&var] (console_args &args) {
        T tmp;
        if (!read_cvar(args, tmp)) {
            return false;
        }
        var = tmp;
        return true;
    };
    cv.get = [&var] (bstring256 &out) { format_cvar(out, var); };

    if (help && *help) {
        set_help(name, help);
    }
}

void dev::qconsole::bind_cvar(pcstr name, int &var, pcstr help) { bind_cvar_t(name, var, help); }
void dev::qconsole::bind_cvar(pcstr name, int8_t &var, pcstr help) { bind_cvar_t(name, var, help); }
void dev::qconsole::bind_cvar(pcstr name, int16_t &var, pcstr help) { bind_cvar_t(name, var, help); }
void dev::qconsole::bind_cvar(pcstr name, uint8_t &var, pcstr help) { bind_cvar_t(name, var, help); }
void dev::qconsole::bind_cvar(pcstr name, float &var, pcstr help) { bind_cvar_t(name, var, help); }
void dev::qconsole::bind_cvar(pcstr name, bool &var, pcstr help) { bind_cvar_t(name, var, help); }

void dev::qconsole::push_history(pcstr line) {
    _history.emplace_back(line);
    while (_history.size() > _max_history) {
        _history.pop_front();
    }
}

bool dev::qconsole::load_history(const vfs::path &filename) {
    FILE *f = vfs::file_open_os(filename, "rt");
    if (!f) {
        return false;
    }

    char line[history_line::capacity];
    while (::fgets(line, sizeof(line), f)) {
        strip_line_end(line);
        if (*line) {
            push_history(line);
        }
    }

    vfs::file_close_os(f);
    return true;
}

void dev::qconsole::save_history(const vfs::path &filename) const {
    if (_history.empty()) {
        return;
    }

    FILE *f = vfs::file_open_os(filename, "wt");
    if (!f) {
        return;
    }

    for (const history_line &line : _history) {
        ::fprintf(f, "%s\n", line.c_str());
    }

    vfs::file_close_os(f);
}

void dev::qconsole::expand_variables(pcstr line, bstring1024 &result, console_output &out) {
    result.clear();
    for (pcstr p = line; *p;) {
        if (*p != '$') {
            result.append(*p++);
            continue;
        }

        pcstr name_begin = ++p;
        while (*p && !::isspace((unsigned char)*p)) {
            ++p;
        }

        bstring128 name;
        name.ncat(name_begin, std::min<size_t>(p - name_begin, bstring128::capacity - 1));
        if (name.empty()) {
            error(out, "EXPECTED IDENTIFIER AT $");
            result.append('$');
            continue;
        }

        auto it = _cvars.find(xstring(name.c_str()));
        if (it == _cvars.end()) {
            error(out, "Variable %s not found", name);
            result.append('$').append(name.c_str());
            continue;
        }

        bstring256 value;
        it->second.get(value);
        result.append(value.c_str());
    }
}

void dev::qconsole::execute(pcstr line, console_output &out) {
    if (!line) {
        return;
    }

    while (*line && ::isspace((unsigned char)*line)) {
        ++line;
    }

    if (!*line || *line == '#') {
        return;
    }

    history_line raw(line);
    strip_line_end(raw.data());
    push_history(raw.c_str());

    out.print(style.echo_begin);
    out.print(raw.c_str());
    out.print(style.echo_end);
    out.print("\n");

    bstring1024 expanded;
    expand_variables(raw.c_str(), expanded, out);

    console_args args(expanded.c_str());
    bstring128 token;
    bool command_found = false;
    while (args.next(token)) {
        auto it = _commands.find(xstring(token.c_str()));
        if (it != _commands.end()) {
            command_found = true;
            it->second(args, out);
            out.print("\n");
        }
    }

    if (command_found) {
        return;
    }

    auto cv = _cvars.find(xstring(token.c_str()));
    if (cv != _cvars.end()) {
        bstring256 value;
        cv->second.get(value);
        out.printf("%s %s\n", token, value);
        return;
    }

    error(out, "Variable/Command %s unknown.", token);
}

void dev::qconsole::execute_file(pcstr filename, console_output &out) {
    FILE *f = vfs::file_open_os(vfs::path(filename), "rt");
    if (!f) {
        error(out, "Unable to open file : %s", filename);
        return;
    }

    char line[history_line::capacity];
    while (::fgets(line, sizeof(line), f)) {
        execute(line, out);
    }

    vfs::file_close_os(f);
}

void dev::qconsole::cmd_list_cmds(console_output &out) const {
    std::vector<pcstr> names;
    names.reserve(_commands.size());
    for (const auto &it : _commands) {
        names.push_back(it.first.c_str());
    }
    std::sort(names.begin(), names.end(), [] (pcstr a, pcstr b) { return ::strcmp(a, b) < 0; });

    out.print("\nAvailable commands:");
    for (pcstr name : names) {
        out.printf("\n%s", name);
    }
    out.print("\n");
}

void dev::qconsole::cmd_list_cvars(console_output &out) const {
    out.print("\nBound console variables:");
    for (const auto &it : _cvars) {
        out.printf("\n%s", it.first);
    }
    out.print("\n");
}

void dev::qconsole::cmd_events_history(console_args &args, console_output &out) const {
    bstring128 filter;
    args.next(filter);

    out.print("\nEvents history:");
    if (!filter.empty()) {
        out.printf(" (filter: %s)", filter);
    }
    out.print("\n");

    const auto &lines = events_history::get_event_history();
    for (uint32_t i = 0; i < lines.events.size(); ++i) {
        const bstring1024 &line = events_history::_event_to_string(lines.events[i]);
        if (!filter.empty() && !::strstr(line.c_str(), filter.c_str())) {
            continue;
        }
        out.println(line.c_str());
    }

    out.print("\n");
}

void dev::qconsole::cmd_set(console_args &args, console_output &out) {
    bstring128 name;
    if (!args.next(name)) {
        error(out, "Syntax error parsing argument");
        return;
    }

    auto it = _cvars.find(xstring(name.c_str()));
    if (it == _cvars.end()) {
        error(out, "Variable %s unknown.", name);
        return;
    }

    if (!it->second.set(args)) {
        error(out, "SYNTAX ERROR IN VARIABLE PARSER");
    }
}

void dev::qconsole::cmd_echo(console_args &args, console_output &out) {
    bstring128 name;
    if (!args.next(name)) {
        error(out, "Syntax error parsing argument.");
        return;
    }

    auto it = _cvars.find(xstring(name.c_str()));
    if (it == _cvars.end()) {
        error(out, "Variable %s unknown.", name);
        return;
    }

    bstring256 value;
    it->second.get(value);
    out.printf("%s %s\n", name, value);
}

void dev::qconsole::cmd_help(console_args &args, console_output &out) {
    bstring128 topic;
    if (!args.next(topic)) {
        out.println("Type 'help' followed by the name of a command or variable to get help on that topic if available."
                    "\nType cmds, cvars to print lists of the available commands, variables, and help topics."
                    "\nUse $<varname> to dereference a variable in a command argument list and use # to comment the rest of a line");
        return;
    }

    auto it = _help.find(xstring(topic.c_str()));
    if (it == _help.end()) {
        error(out, "No help available for topic: %s", topic);
        return;
    }

    out.println(it->second.c_str());
}

void dev::qconsole::cmd_var(console_args &args, console_output &out) {
    bstring128 name;
    if (!args.next(name)) {
        error(out, "Syntax error in function arguments.");
        return;
    }

    const xstring key(name.c_str());
    bstring256 &value = _dynamic_vars[key];
    value = args.rest();
    args.skip_rest();

    cvar &cv = _cvars[key];
    cv.set = [&value] (console_args &a) {
        value = a.rest();
        a.skip_rest();
        return true;
    };
    cv.get = [&value] (bstring256 &result) { result = value; };
}

void dev::qconsole::bind_basic_commands() {
    bind_command("var", [this] (console_args &args, console_output &out) { cmd_var(args, out); },
        "Type var <varname> <value> to declare a dynamic variable with name <varname> and value <value>."
        "\nVariable names are any space delimited string and variable value is set to the remainder of the line.");

    bind_command("cmds", [this] (console_args &, console_output &out) { cmd_list_cmds(out); }, "lists the available console commands");
    bind_command("set", [this] (console_args &args, console_output &out) { cmd_set(args, out); }, "type set <identifier> <val> to change the value of a cvar");
    bind_command("echo", [this] (console_args &args, console_output &out) { cmd_echo(args, out); }, "type echo <identifier> to print the value of a cvar");
    bind_command("cvars", [this] (console_args &, console_output &out) { cmd_list_cvars(out); }, "lists the bound cvars");
    bind_command("events_history", [this] (console_args &args, console_output &out) { cmd_events_history(args, out); },
        "lists the events history; optional substr filter: events_history [substr]");
    bind_command("help", [this] (console_args &args, console_output &out) { cmd_help(args, out); }, "you're a smarty");

    bind_command("run", [this] (console_args &args, console_output &out) {
        bstring256 filename;
        if (!args.next(filename)) {
            error(out, "Usage: run <file>");
            return;
        }
        execute_file(filename.c_str(), out);
    }, "runs the commands in a text file named by the argument");
}
