#pragma once

#include <unordered_set>
#include <algorithm>
#include <vector>

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
class ConsoleBuf : public std::streambuf {
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
    void loadCommandHistory();
    void render(const char *title, bool& p_open, int width, int height); ///< Renders an IMGUI window implementation of the console

    imgui_qconsole();

  private:
    void optionsMenu();

    void historyCallback(ImGuiInputTextCallbackData *data);

    void textCompletionCallback(ImGuiInputTextCallbackData *data);
    
    void saveCommandHistory();
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

} // dev
