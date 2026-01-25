#include "qconsole.h"

#include "game/game_events_history.h"

void dev::qconsole::eventsHistory(std::ostream &os) const {
    os << "\nEvents history:";

    const auto &lines = events_history::get_event_history();
    for (int i = 0; i < lines.events.size(); ++i) {
        os << events_history::_event_to_string(lines.events[i]).c_str() << std::endl;
    }

    os << std::endl;
}

bool dev::qconsole::loadHistoryBuffer(const vfs::path &inFile) {
    std::ifstream hfi(inFile);

    if (hfi.is_open()) {
        loadHistoryBuffer(hfi);
        hfi.close();
        return true;
    }

    return false;
}

void dev::qconsole::saveHistoryBuffer(const vfs::path &outFile) {
    if (history_buffer.size()) {
        std::ofstream hfo(outFile);
        saveHistoryBuffer(hfo);
        hfo.close();
    }
}

void dev::qconsole::loadHistoryBuffer(std::istream &inFile) {
    while (!inFile.eof()) {

        std::string tmp;
        std::getline(inFile, tmp);

        if (tmp.length()) {
            history_buffer.push(tmp);
        }
    }
}

void dev::qconsole::saveHistoryBuffer(std::ofstream &outfile) {
    for (unsigned int i = 0; i < history_buffer.size(); i++) {
        outfile << history_buffer[i] << std::endl;
    }
}

const std::deque<std::string> &dev::qconsole::historyBuffer() const {
    return history_buffer;
}

void dev::qconsole::dereferenceVariables(std::istream &is, std::ostream &os, std::string &str) {
    size_t varBase = 0;
    int n = 0;

    while ((varBase = str.find('$', varBase)) != str.npos) {
        size_t substrEnd = varBase;
        size_t dollar = varBase;
        varBase++;

        n++;

        for (; ((substrEnd < str.size()) && (!isspace(str[substrEnd]))); substrEnd++) {
            ;
        }

        if (substrEnd == varBase) {
            os << error() << "EXPECTED IDENTIFIER AT $" << std::endl;
        } else {
            std::string substr(str.substr(varBase, substrEnd - varBase));
            std::stringstream sstr;
            cvar_print_table::iterator it = cvar_printf.find(substr);

            // check that variable exists
            if (it != cvar_printf.end()) {
                it->second(is, sstr);
                str.replace(dollar, substrEnd, sstr.str());
            } else {
                os << error() << "Variable " << substr << " not found" << std::endl;
            }
        }
    }
}

dev::qconsole::qconsole(size_t maxCapacity) : history_buffer(maxCapacity) {
    bindBasicCommands();
}

void dev::qconsole::bindBasicCommands() {
    std::function<void(const std::string &, const DynamicVariable &)> f1 = std::bind(
        static_cast<void (qconsole:: *)(const std::string &, const DynamicVariable &)>(&qconsole::bindDynamicCVar<DynamicVariable>),
        this, std::placeholders::_1, std::placeholders::_2);

    bind_command("var", f1,
        "Type var <varname> <value> to declare a dynamic variable with name <varname> and value <value>."
        "\nVariable names are any space delimited string and variable value is set to the remainder of the line.");

    bind_command("cmds", [this] (std::istream &is, std::ostream &os) { this->list_cmds(os); }, "lists the available console commands");
    bind_command("set", [this] (std::istream &is, std::ostream &os) { this->commandSet(is, os); }, "type set <identifier> <val> to change the value of a cvar");
    bind_command("echo", [this] (std::istream &is, std::ostream &os) { this->command_echo(is, os); }, "type echo <identifier> to print the value of a cvar");
    bind_command("cvars", [this] (std::istream &is, std::ostream &os) { listCVars(os); }, "lists the bound cvars");
    bind_command("events_history", [this] (std::istream &is, std::ostream &os) { this->eventsHistory(os); }, "lists the events history");
    bind_command("help", [this] (std::istream &is, std::ostream &os) { this->commandHelp(is, os); }, "you're a smarty");

    bind_command("run", [this] (std::istream &is, std::ostream &os) {
        std::string f;
        is >> f;
        this->executeFile(f, os);
    }, "runs the commands in a text file named by the argument");
}

void dev::qconsole::commandExecute(std::istream &is, std::ostream &os) {
    char ch;
    while (!is.eof()) {
        ch = is.peek();

        if (ch == std::char_traits<char>::eof()) {
            is.get(ch);
            return;
        } else if (ch == '#') {
            std::string tmp;
            getline(is, tmp);
            return;
        } //if newline we will not parse anything else
        else if (std::isspace(ch)) {
            is.get(ch);
            continue;
        } else {
            break;
        }
    }

    std::stringstream lineStream;
    {
        std::string lineTemp;

        getline(is, lineTemp);

        history_buffer.push(lineTemp);

        os << echo() << lineTemp << std::endl;

        dereferenceVariables(is, os, lineTemp);

        lineStream.str(lineTemp); ///\todo this constrains us to a single line.  way to go later might be to require user or
        ///generated command parser to return string that was parsed
    }

    std::string x;
    bool command_found = false;
    while (lineStream >> x) {
        CommandTable::const_iterator it = commandTable.find(x);

        if (it != commandTable.end()) {
            command_found = true;
            (it->second)(lineStream, os); //execute the command
            os << '\n';
        }
    }

    if (command_found) {
        return;
    }

    cvar_print_table::iterator it = cvar_printf.find(x);
    if (it != cvar_printf.end()) {
        (it->second)(is, os);
        return;
    }

    os << error() << "Variable/Command " << x << " unknown." << std::endl;
}

void dev::qconsole::commandExecute(const std::string &str, std::ostream &output) {
    std::stringstream lineStream;
    lineStream.str(str);
    commandExecute(lineStream, output);
}

void dev::qconsole::command_echo(std::istream &is, std::ostream &os) {
    std::string x;

    if (!(is >> x)) {
        os << error() << "Syntax error parsing argument." << std::endl;
        return;
    }

    cvar_print_table::iterator it = cvar_printf.find(x);
    if (it != cvar_printf.end()) {
        (it->second)(is, os);
    } else {
        os << error() << "Variable " << x << " unknown." << std::endl;
    }
}

void dev::qconsole::commandSet(std::istream &is, std::ostream &os) {
    std::string x;

    if (!(is >> x)) {
        os << error() << "Syntax error parsing argument" << std::endl;
        return;
    }

    CVarReadTable::iterator it = cvarReadFTable.find(x);

    if (it != cvarReadFTable.end()) {
        it->second(is, os);
    } else {
        os << error() << "Variable " << x << " unknown." << std::endl;
    }
}
