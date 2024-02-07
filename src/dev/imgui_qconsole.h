#pragma once

#include <unordered_set>
#include <algorithm>

//dependencies
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include "qconsole.h"

namespace dev {

inline const ImVec4 COMMENT_COLOR = ImVec4(1.0f, 0.8f, 0.6f, 1.0f);
inline const ImVec4 ERROR_COLOR = ImVec4(2.0f, 0.2f, 0.2f, 1.0f);
inline const ImVec4 WARNING_COLOR = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);

#define RED_BKGRND_COLOR IM_COL32(255, 0, 0, 255);
#define GREEN_BKGRND_COLOR IM_COL32(0, 255, 0, 255);
#define YELLOW_BKGRND_COLOR IM_COL32(255, 255, 0, 255);
#define BLUE_BKGRND_COLOR IM_COL32(0, 0, 255, 255);
#define MAGENTA_BKGRND_COLOR IM_COL32(255, 0, 255, 255);
#define CYAN_BKGRND_COLOR IM_COL32(0, 255, 255, 255);
#define WHITE_BKGRND_COLOR IM_COL32(255, 255, 255, 255);

inline constexpr std::string_view TEXT_COLOR_RESET = "\u001b[0m";
inline constexpr std::string_view TEXT_COLOR_BLACK = "\u001b[30m";
inline constexpr std::string_view TEXT_COLOR_RED = "\u001b[31m";
inline constexpr std::string_view TEXT_COLOR_GREEN = "\u001b[32m";
inline constexpr std::string_view TEXT_COLOR_YELLOW = "\u001b[33m";
inline constexpr std::string_view TEXT_COLOR_BLUE = "\u001b[34m";
inline constexpr std::string_view TEXT_COLOR_MAGENTA = "\u001b[35m";
inline constexpr std::string_view TEXT_COLOR_CYAN = "\u001b[36m";
inline constexpr std::string_view TEXT_COLOR_WHITE = "\u001b[37m";
inline constexpr std::string_view TEXT_COLOR_BLACK_BRIGHT = "\u001b[30;1m";
inline constexpr std::string_view TEXT_COLOR_RED_BRIGHT = "\u001b[31;1m";
inline constexpr std::string_view TEXT_COLOR_GREEN_BRIGHT = "\u001b[32;1m";
inline constexpr std::string_view TEXT_COLOR_YELLOW_BRIGHT = "\u001b[33;1m";
inline constexpr std::string_view TEXT_COLOR_BLUE_BRIGHT = "\u001b[34;1m";
inline constexpr std::string_view TEXT_COLOR_MAGENTA_BRIGHT = "\u001b[35;1m";
inline constexpr std::string_view TEXT_COLOR_CYAN_BRIGHT = "\u001b[36;1m";
inline constexpr std::string_view TEXT_COLOR_WHITE_BRIGHT = "\u001b[37;1m";
inline constexpr std::string_view TEXT_COLOR_BLACK_BKGRND = "\u001b[40m";
inline constexpr std::string_view TEXT_COLOR_RED_BKGRND = "\u001b[41m";
inline constexpr std::string_view TEXT_COLOR_GREEN_BKGRND = "\u001b[42m";
inline constexpr std::string_view TEXT_COLOR_YELLOW_BKGRND = "\u001b[43m";
inline constexpr std::string_view TEXT_COLOR_BLUE_BKGRND = "\u001b[44m";
inline constexpr std::string_view TEXT_COLOR_MAGENTA_BKGRND = "\u001b[45m";
inline constexpr std::string_view TEXT_COLOR_CYAN_BKGRND = "\u001b[46m";
inline constexpr std::string_view TEXT_COLOR_WHITE_BKGRND = "\u001b[47m";

enum AnsiColorCode
{
    ANSI_RESET = 0,
    ANSI_BRIGHT_TEXT = 1,

    ANSI_BLACK = 30,
    ANSI_RED = 31,
    ANSI_GREEN = 32,
    ANSI_YELLOW = 33,
    ANSI_BLUE = 34,
    ANSI_MAGENTA = 35,
    ANSI_CYAN = 36,
    ANSI_WHITE = 37,

    ANSI_BLACK_BKGRND = 40,
    ANSI_RED_BKGRND = 41,
    ANSI_GREEN_BKGRND = 42,
    ANSI_YELLOW_BKGRND = 43,
    ANSI_BLUE_BKGRND = 44,
    ANSI_MAGENTA_BKGRND = 45,
    ANSI_CYAN_BKGRND = 46,
    ANSI_WHITE_BKGRND = 47,
};

/// Stream Buffer for the IMGUI Console Terminal.  Breaks text stream into Lines, which are an array of formatted text sequences
/// Formatting is presently handled via ANSI Color Codes.  Some other input transformation can be applied to the input before it hits this stream
/// eg. to do syntax highlighting, etc.
class ConsoleBuf : public std::streambuf
{
  public:
    
    struct FormattingParams
    {
        ImVec4 textColor = ImVec4(1.0, 1.0, 1.0, 1.0);
        ImU32 backgroundColor = 0;
        bool hasBackgroundColor = false;
    };
    
    struct TextSequence
    {
        FormattingParams style;
        std::string text = "";
    };

    struct Line
    {
        std::vector<TextSequence> sequences;

        inline TextSequence &curSequence() { return sequences[sequences.size() - 1]; }
        inline const TextSequence &curSequence() const { return sequences[sequences.size() - 1]; }
    };

    void clear();

    inline void applyDefaultStyle(){currentStyle = defaultStyle;}
    inline const Line &currentLine() const { return lines[lines.size() - 1]; }
    inline const std::string &curStr() const { return currentLine().curSequence().text; }

    ConsoleBuf();

    inline const std::vector<Line>& getLines() const { return lines; }
    
    FormattingParams defaultStyle; ///< can change default text color and background

  protected:
    /// change formatting state based on an integer code in the ansi-code input stream.  called by the streambuf methods
    void processANSICode(int code);

    // -- streambuf overloads --
    int overflow(int c);

    FormattingParams currentStyle; ///< // current formatting
    
    bool brightText = false;                       ///< saw ansi code for bright-mode text
    AnsiColorCode textCode = ANSI_RESET;           ///< ANSI color code we last saw for text

    std::vector<Line> lines; ///< All output lines

    bool parsingANSICode = false; ///< ANSI color code parser state variable
    bool listeningDigits = false; ///< ANSI color code parser state variable - listening for next digit

    std::stringstream numParse; ///< ANSI color code parser state variable - digit accumulator

    inline Line &currentLine() { return lines[lines.size() - 1]; }
    inline std::string &curStr() { return currentLine().curSequence().text; }
};

/// streambuffer implementation for MultiStream
class MultiStreamBuf : public std::streambuf
{
  public:
    std::unordered_set<std::ostream *> streams;

    MultiStreamBuf() {}

    int overflow(int in);

    std::streamsize xsputn(const char *s, std::streamsize n);
};

/// An ostream that is actually a container of ostream pointers, that pipes output to every ostream in the container
class MultiStream : public std::ostream
{
    MultiStreamBuf buf;

  public:
    MultiStream() : std::ostream(&buf) {}

    void addStream(std::ostream &str) { buf.streams.insert(&str); }
};

/// A user input line that supports callbacks and pushes user input to a stream on enter
struct IMGUIInputLine
{
  private:
    std::string InputBuf;       ///< buffer user is typing into currently
    std::stringstream stream; ///< stream that input lines accumulate into on enter presses

  public:
    typedef std::unordered_map<ImGuiInputTextFlags, std::function<void(ImGuiInputTextCallbackData *)>> TextInputCallbacks;

    TextInputCallbacks textCallbacks; ///< IMGUI Text Input Callbacks.  Map flags to function objects

    /// See definition of ImGui::InputText
    ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;

    IMGUIInputLine();

    std::istream &getStream(); ///< returns the istream that user input accumulates into

    std::string getInput(); ///< Pulls a single line from the input stream and returns it

    /// Calls appropriate user defined callbacks
    static int TextEditCallbackStub(ImGuiInputTextCallbackData *data);

    /// Renders the control in a new IMGUI popup window.  Returns true if new user input is available.
    bool renderInWindow(bool &p_open, const char *title);

    /// Renders the contorl in whatever the surrounding IMGUI context is.  Returns true if new user input is available.
    bool render(int width);
    bool reclaim_focus = false;
};

/// GUI Ostream pane with ANSI Color Code Support
/// Supports text filtering as well via 'filter' member.
class IMGUIOstream : public std::ostream
{
    /// checks if an output line passes the filter
    bool linePassFilter(const ConsoleBuf::Line &l) const;

  public:
    ConsoleBuf strb;        ///< custom streambuf
    ImGuiTextFilter filter; ///< Text filter.

    bool autoScrollEnabled = true;
    bool shouldScrollToBottom = false;

    inline void Clear() { strb.clear(); } ///< clear the output pane

    inline IMGUIOstream() : std::ostream(&strb) {}

    /// renders the control in a new popup window.
    void renderInWindow(bool &p_open, const char *title = "");

    /// Renders the control in whatever the surrounding IMGUI context is.
    void render();
    
    inline void applyDefaultStyle(){strb.applyDefaultStyle();}
    inline ConsoleBuf::FormattingParams& defaultStyle(){return strb.defaultStyle;}
};

/// Quake style console : IMGUI Widget
/// The widget IS-A MultiStream, so you can call .addStream() to add additional streams to mirror the output - like a file or cout
/// A MultiStream IS-A ostream, so you can write to it with << and pass it to ostream functions
/// You can also get its streambuf and pass it to another ostream, such as cout so that those ostreams write to the console.  eg.  cout.rdbuf(console.rdbuf())
class imgui_qconsole : public MultiStream
{
  public:
    qconsole con; ///< implementation of the quake style console
    IMGUIOstream os;                 ///< IMGUI ostream pane
    IMGUIInputLine is;               ///< IMGUI input line
    std::size_t prevLineCount = 0;   ///< previous line count for os; used to autoscroll when os gets a new line.

    ImFont* font = nullptr;

    int HistoryPos = -1; ///< index into the console history buffer, for when we press up/down arrow to scroll previous commands

    float fontScale = 1.2f; ///< text scale for the console widget window
    bool skip_event = false;

    void clear(); ///< Clear the ostream

    void render(const char *title, bool& p_open, int width, int height); ///< Renders an IMGUI window implementation of the console

    imgui_qconsole();

  private:
    void optionsMenu();

    void historyCallback(ImGuiInputTextCallbackData *data);

    void textCompletionCallback(ImGuiInputTextCallbackData *data);
};

// -------------------------------------------
// ------------ANSI COLOR HELPERS-------------
// -------------------------------------------

ImU32 getANSIBackgroundColor(AnsiColorCode code);
ImVec4 getAnsiTextColor(AnsiColorCode code);
ImVec4 getAnsiTextColorBright(AnsiColorCode code);

// -------------------------------------------
// --------------Portable String Helpers------
// -------------------------------------------

inline static int Strnicmp(const char *s1, const char *s2, int n)
{
    int d = 0;
    while (n > 0 && (d = toupper(*s2) - toupper(*s1)) == 0 && *s1)
    {
        s1++;
        s2++;
        n--;
    }
    return d;
}

inline static void Strtrim(char *s)
{
    char *str_end = s + strlen(s);
    while (str_end > s && str_end[-1] == ' ')
        str_end--;
    *str_end = 0;
}

// -------------------------------------------
// ----- IMGUIOstream Implementation ------ //
// -------------------------------------------

inline bool IMGUIOstream::linePassFilter(const ConsoleBuf::Line &l) const
{
    for (const ConsoleBuf::TextSequence &s : l.sequences)
    {
        const char *item = s.text.c_str();
        if (filter.PassFilter(item))
            return true;
    }

    return false;
}

inline void IMGUIOstream::renderInWindow(bool &p_open, const char *title)
{
    ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);

    if (!ImGui::Begin(title, &p_open))
    {
        ImGui::End();
        return;
    }

    render();

    ImGui::End();
}

inline void IMGUIOstream::render()
{
    for (const ConsoleBuf::Line& line : strb.getLines())
    {
        if (!linePassFilter(line))
            continue;

        for (const ConsoleBuf::TextSequence &seq : line.sequences)
        {
            if (seq.style.hasBackgroundColor)
            {
                ImVec2 textSize = ImGui::CalcTextSize(seq.text.c_str());
                ImVec2 cursorScreenPos = ImGui::GetCursorScreenPos();
                ImVec2 sum = ImVec2(textSize[0] + cursorScreenPos[0], textSize[1] + cursorScreenPos[1]);
                ImGui::GetWindowDrawList()->AddRectFilled(cursorScreenPos, sum, seq.style.backgroundColor);
            }

            ImGui::TextColored(seq.style.textColor, "%s", seq.text.c_str());
            ImGui::SameLine();
        }

        ImGui::NewLine();
    }

    if ((autoScrollEnabled && shouldScrollToBottom) || (autoScrollEnabled && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
        ImGui::SetScrollHereY(1.0f);
    shouldScrollToBottom = false;
}

// -------------------------------------------
// --- imgui_qconsole Implementation --- //
// -------------------------------------------

inline imgui_qconsole::imgui_qconsole()
{
    addStream(os);

    is.textCallbacks[ImGuiInputTextFlags_CallbackCompletion] = [this](ImGuiInputTextCallbackData *data) { this->textCompletionCallback(data); };

    is.textCallbacks[ImGuiInputTextFlags_CallbackHistory] = [this](ImGuiInputTextCallbackData *data) { this->historyCallback(data); };

    con.bind_member_command("clear", *this, &imgui_qconsole::clear, "Clear the console");
    con.bind_cvar("fontScale", fontScale);

    con.style = qconsole::ConsoleStylingColor();
}

inline void imgui_qconsole::clear() { os.Clear(); }

inline void imgui_qconsole::optionsMenu() { ImGui::Checkbox("Auto-scroll", &os.autoScrollEnabled); }

inline void imgui_qconsole::render(const char *title, bool& p_open, int width, int height)
{
    if (!p_open) return;

    if (font) {
        ImGui::PushFont(font);
    }

    ImGui::SetNextWindowPos({0, 0});
    ImGui::SetNextWindowSize(ImVec2(width, height));

    ImGui::Begin(title, &p_open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    ImGui::SetWindowFontScale(fontScale);

    // As a specific feature guaranteed by the library, after calling Begin() the last Item represent the title bar.
    // So e.g. IsItemHovered() will return true when hovering the title bar.
    // Here we create a context menu only available from the title bar.
    //if (ImGui::BeginPopupContextItem())
    //{
    //    if (ImGui::MenuItem("Close Console"))
    //        p_open = false;
    //    ImGui::EndPopup();
    //}

    //ImGui::TextWrapped("Enter 'help' for help, press TAB to use text completion.");

    // TODO: display items starting from the bottom

    //if (ImGui::SmallButton("Clear"))
    //{
    //    ClearLog();
    //}
    //ImGui::SameLine();
    //
    //bool copy_to_clipboard = ImGui::SmallButton("Copy");

    //ImGui::Separator();

    // Options menu
    //if (ImGui::BeginPopup("Options"))
    //{
    //    optionsMenu();
    //    ImGui::EndPopup();
    //}

    // Options, Filter
    //if (ImGui::Button("Options"))
    //    ImGui::OpenPopup("Options");
    //ImGui::SameLine();
    //os.filter.Draw("Filter (\"incl,-excl\") (\"error\")", 180);
    //ImGui::Separator();

    // Reserve enough left-over height for 1 separator + 1 input text
    const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
    ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar);
    //if (ImGui::BeginPopupContextWindow())
    //{
    //    if (ImGui::Selectable("Clear"))
    //        ClearLog();
    //    ImGui::EndPopup();
    //}

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
    //if (copy_to_clipboard)
    //    ImGui::LogToClipboard();

    os.render();

    if (prevLineCount < os.strb.getLines().size())
    {
        os.shouldScrollToBottom = true;
    }
    prevLineCount = os.strb.getLines().size();

    //if (copy_to_clipboard)
    //    ImGui::LogFinish();

    ImGui::PopStyleVar();
    ImGui::EndChild();
    ImGui::Separator();

    if (is.render(width))
    {
        HistoryPos = -1;

        con.commandExecute(is.getStream(), (*this));

        // On command input, we scroll to bottom even if AutoScroll==false
        os.shouldScrollToBottom = true;
    }

    if (font)
    {
        ImGui::PopFont();
    }

    ImGui::End();
}

inline void imgui_qconsole::historyCallback(ImGuiInputTextCallbackData *data)
{
    // Example of HISTORY
    const int prev_history_pos = HistoryPos;
    if (data->EventKey == ImGuiKey_UpArrow)
    {
        if (HistoryPos == -1)
            HistoryPos = con.historyBuffer().size() - 1;
        else if (HistoryPos > 0)
            HistoryPos--;
    }
    else if (data->EventKey == ImGuiKey_DownArrow)
    {
        if (HistoryPos != -1)
            if (++HistoryPos >= con.historyBuffer().size())
                HistoryPos = -1;
    }

    // A better implementation would preserve the data on the current input line along with cursor position.
    if (prev_history_pos != HistoryPos)
    {
        const char *history_str = (HistoryPos >= 0) ? con.historyBuffer()[HistoryPos].c_str() : "";
        data->DeleteChars(0, data->BufTextLen);
        data->InsertChars(0, history_str);
    }
}

inline void imgui_qconsole::textCompletionCallback(ImGuiInputTextCallbackData *data)
{
    // Locate beginning of current word
    const char *word_end = data->Buf + data->CursorPos;
    const char *word_start = word_end;
    while (word_start > data->Buf)
    {
        const char c = word_start[-1];
        if (c == ' ' || c == '\t' || c == ',' || c == ';')
            break;
        word_start--;
    }

    // Build a list of candidates
    ImVector<std::string> candidates;

    // autocomplete commands...
    for (auto it = con.getCommandTable().begin(); it != con.getCommandTable().end(); it++)
    {
        if (Strnicmp(it->first.c_str(), word_start, (int)(word_end - word_start)) == 0)
        {
            candidates.push_back(it->first);
        }
    }

    // ... and autcomplete variables
    for (auto it = con.getCVarReadTable().begin(); it != con.getCVarReadTable().end(); it++)
    {
        if (Strnicmp(it->first.c_str(), word_start, (int)(word_end - word_start)) == 0)
        {
            candidates.push_back(it->first);
        }
    }

    if (candidates.Size == 0)
    {
        // No match
        //AddLog("No match for %.*s, , word_start);
        (*this) << "No match for ";
        (*this) << (int)(word_end - word_start);
        (*this) << ' ' << word_start;
        (*this) << "!\n";
    }
    else if (candidates.Size == 1)
    {
        // Single match. Delete the beginning of the word and replace it entirely so we've got nice casing.
        data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
        data->InsertChars(data->CursorPos, candidates[0].c_str());
        data->InsertChars(data->CursorPos, " ");
    }
    else
    {
        // Multiple matches. Complete as much as we can..
        // So inputing "C"+Tab will complete to "CL" then display "CLEAR" and "CLASSIFY" as matches.
        int match_len = (int)(word_end - word_start);
        for (;;)
        {
            int c = 0;
            bool all_candidates_matches = true;
            for (int i = 0; i < candidates.Size && all_candidates_matches; i++)
                if (i == 0)
                    c = toupper(candidates[i][match_len]);
                else if (c == 0 || c != toupper(candidates[i][match_len]))
                    all_candidates_matches = false;
            if (!all_candidates_matches)
                break;
            match_len++;
        }

        if (match_len > 0)
        {
            data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
            data->InsertChars(data->CursorPos, candidates[0].c_str(), candidates[0].c_str() + match_len);
        }

        // List matches
        (*this) << "Possible matches:\n";
        for (int i = 0; i < candidates.Size; i++)
            (*this) << "- " << candidates[i] << '\n';
    }
}

inline ImU32 getANSIBackgroundColor(AnsiColorCode code)
{
    switch (code)
    {
    case ANSI_RESET:
        return 0;
    case ANSI_BLACK_BKGRND:
        return 0;
    case ANSI_RED_BKGRND:
        return RED_BKGRND_COLOR;
    case ANSI_GREEN_BKGRND:
        return GREEN_BKGRND_COLOR;
    case ANSI_YELLOW_BKGRND:
        return YELLOW_BKGRND_COLOR;
    case ANSI_BLUE_BKGRND:
        return BLUE_BKGRND_COLOR;
    case ANSI_MAGENTA_BKGRND:
        return MAGENTA_BKGRND_COLOR;
    case ANSI_CYAN_BKGRND:
        return CYAN_BKGRND_COLOR;
    case ANSI_WHITE_BKGRND:
        return WHITE_BKGRND_COLOR;
    default:
        return 0;
    }
}

inline ImVec4 getAnsiTextColor(AnsiColorCode code)
{
    switch (code)
    {
    case ANSI_RESET:
        return ImVec4(1.0, 1.0, 1.0, 1.0);
    case ANSI_BLACK:
        return ImVec4(0.0, 0.0, 0.0, 1.0);
    case ANSI_RED:
        return ImVec4(0.75, 0.0, 0.0, 1.0);
    case ANSI_GREEN:
        return ImVec4(0.0, 0.750, 0.0, 1.0);
    case ANSI_YELLOW:
        return ImVec4(0.750, 0.750, 0.0, 1.0);
    case ANSI_BLUE:
        return ImVec4(0.0, 0.0, 0.750, 1.0);
        ;
    case ANSI_MAGENTA:
        return ImVec4(0.750, 0.0, 0.750, 1.0);
        ;
    case ANSI_CYAN:
        return ImVec4(0.0, 0.750, 0.750, 1.0);
        ;
    case ANSI_WHITE:
        return ImVec4(0.750, 0.750, 0.750, 1.0);
        ;
    default:
        return ImVec4(0.0, 0.0, 0.0, 1.0);
    }
}

inline ImVec4 getAnsiTextColorBright(AnsiColorCode code)
{
    switch (code)
    {
    case ANSI_RESET:
        return ImVec4(1.0, 1.0, 1.0, 1.0);
    case ANSI_BLACK:
        return ImVec4(0.0, 0.0, 0.0, 1.0);
    case ANSI_RED:
        return ImVec4(1.0, 0.0, 0.0, 1.0);
    case ANSI_GREEN:
        return ImVec4(0.0, 1.0, 0.0, 1.0);
    case ANSI_YELLOW:
        return ImVec4(1.0, 1.0, 0.0, 1.0);
    case ANSI_BLUE:
        return ImVec4(0.0, 0.0, 1.0, 1.0);
        ;
    case ANSI_MAGENTA:
        return ImVec4(1.0, 0.0, 1.0, 1.0);
        ;
    case ANSI_CYAN:
        return ImVec4(0.0, 1.0, 1.0, 1.0);
        ;
    case ANSI_WHITE:
        return ImVec4(1.0, 1.0, 1.0, 1.0);
        ;
    default:
        return ImVec4(0.0, 0.0, 0.0, 1.0);
    }
}

// --------------------------------------
// --- MultiStreamBuf implementation ---
// --------------------------------------

inline int MultiStreamBuf::overflow(int in)
{
    char c = in; ///\todo check for eof, etc?
    for (std::ostream *str : streams)
    {
        (*str) << c;
    }
    return 1;
}

inline std::streamsize MultiStreamBuf::xsputn(const char *s, std::streamsize n)
{
    std::streamsize ssz = 0;

    for (std::ostream *str : streams)
    {
        ssz = str->rdbuf()->sputn(s, n);
    }

    return ssz;
}

// --------------------------------------
// ---- ConsoleBuf implementation -------
// --------------------------------------

inline void ConsoleBuf::clear()
{
    // swap forces reallocation, unlike clear
    std::vector<Line> x;
    lines.swap(x);
    //lines.clear();

    lines.push_back(Line());
    currentLine().sequences.push_back(TextSequence()); // start a new run of chars with default formatting
}

inline void ConsoleBuf::processANSICode(int code)
{
    switch (code)
    {
    case ANSI_RESET:
        
        currentStyle = defaultStyle;
            
        break;
    case ANSI_BRIGHT_TEXT:
        brightText = true;
        if (textCode)
        {
            currentStyle.textColor = getAnsiTextColorBright(textCode);
        }
        break;
    case ANSI_BLACK:
    case ANSI_RED:
    case ANSI_GREEN:
    case ANSI_YELLOW:
    case ANSI_BLUE:
    case ANSI_MAGENTA:
    case ANSI_CYAN:
    case ANSI_WHITE:
        textCode = (AnsiColorCode)code;

        if (brightText)
        {
            currentStyle.textColor = getAnsiTextColorBright((AnsiColorCode)code);
        }
        else
        {
            currentStyle.textColor = getAnsiTextColor((AnsiColorCode)code);
        }
        break;
    case ANSI_BLACK_BKGRND:
    case ANSI_RED_BKGRND:
    case ANSI_GREEN_BKGRND:
    case ANSI_YELLOW_BKGRND:
    case ANSI_BLUE_BKGRND:
    case ANSI_MAGENTA_BKGRND:
    case ANSI_CYAN_BKGRND:
    case ANSI_WHITE_BKGRND:
        currentStyle.hasBackgroundColor = true;
        currentStyle.backgroundColor = getANSIBackgroundColor((AnsiColorCode)code);
        break;
    default:
        std::cerr << "unknown ansi code " << code << " in output\n";
        return;
    }
}

inline int ConsoleBuf::overflow(int c)
{
    if (c != EOF)
    {
        if (parsingANSICode)
        {
            bool error = false;

            if (std::isdigit((char)c) && listeningDigits)
            {
                numParse << (char)c;
            }
            else
            {
                switch (c)
                {
                case 'm': // end of ansi code; apply color formatting to new sequence
                {
                    parsingANSICode = false;

                    int x;
                    if (numParse >> x)
                    {
                        processANSICode(x);
                    }

                    numParse.clear();

                    brightText = false;

                    currentLine().sequences.push_back({currentStyle, "" });

                    break;
                }
                case '[':
                {
                    listeningDigits = true;
                    numParse.clear();
                    break;
                }
                case ';':
                {
                    int x;
                    numParse >> x;

                    numParse.clear();

                    processANSICode(x);

                    break;
                }
                default:
                {
                    error = true;
                    break;
                }
                }

                if (error)
                {
                    numParse.clear();
                    listeningDigits = false;
                    parsingANSICode = false;

                    std::cerr << c;
                    //curStr() += (char)c;
                }
            }
        }
        else
        {
            switch (c)
            {
            case '\u001b':
            {
                parsingANSICode = true;
                numParse.clear();
                break;
            }
            case '\n':
            {
                //currentline add \n
                lines.push_back(Line());
                currentLine().sequences.push_back(TextSequence({currentStyle, "",}));
                break;
            }
            default:
            {
                //std::cerr <<c;
                curStr() += (char)c;
            }
            }
        }
    }
    return c;
}

inline ConsoleBuf::ConsoleBuf()
{
    lines.push_back(Line());
    currentLine().sequences.push_back(TextSequence()); // start a new run of chars with default formatting
}

// --------------------------------------
// ---  IMGUIInputLine Implementation ---
// --------------------------------------

inline IMGUIInputLine::IMGUIInputLine()
{
}

inline std::istream &IMGUIInputLine::getStream()
{
    return stream;
}

inline std::string IMGUIInputLine::getInput()
{
    std::string rval;
    std::getline(stream, rval);
    return rval;
}

// In C++11 you'd be better off using lambdas for this sort of forwarding callbacks
inline int IMGUIInputLine::TextEditCallbackStub(ImGuiInputTextCallbackData *data)
{
    TextInputCallbacks *ic = (TextInputCallbacks *)data->UserData;

    if (!ic)
        return 0;

    if (ic->find(data->EventFlag) != ic->end())
    {
        (*ic)[data->EventFlag](data);
    }

    return 0;
}

inline bool IMGUIInputLine::renderInWindow(bool &p_open, const char *title)
{
    ImGui::SetNextWindowSize(ImVec2(320, 0), ImGuiCond_FirstUseEver);

    if (!ImGui::Begin(title, &p_open))
    {
        ImGui::End();
        return false;
    }

    bool rval = render(ImGui::GetWindowWidth());

    ImGui::End();

    return rval;
}

inline bool IMGUIInputLine::render(int width)
{
    bool rval = false;

    ImGui::SetNextWindowSize(ImVec2(width, 0));
    if (reclaim_focus) {
        ImGui::SetKeyboardFocusHere(0); // Auto focus previous widget
        reclaim_focus = false;
    }
    if (ImGui::InputText("##Input", &InputBuf, input_text_flags, &TextEditCallbackStub, (void*)(&textCallbacks))) {
        reclaim_focus = true;

        char* s = InputBuf.data();
        Strtrim(s);

        if (InputBuf.length() && strlen(s))
        {
            rval = true;

            auto pos1 = stream.tellp(); // save pos1
            stream << s;                // write
            stream << std::endl;
            stream.seekg(pos1);

            strcpy(s, "");
        }
    }

    // Auto-focus on window apparition
    ImGui::SetItemDefaultFocus();     

    return rval;
}

} // dev
