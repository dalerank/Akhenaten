#pragma once

#include <imgui.h>

#include "core/cstring.h"
#include "qconsole.h"

#include <set>
#include <vector>

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

/// Console text split into lines of formatted runs. Formatting comes from ANSI color codes in the written text.
class console_text_buffer {
public:
    struct formatting_params {
        ImVec4 text_color = ImVec4(1.0, 1.0, 1.0, 1.0);
        ImU32 background_color = 0;
        bool has_background_color = false;
    };

    struct text_sequence {
        formatting_params style;
        cstring text;
    };

    struct line {
        std::vector<text_sequence> sequences;

        inline text_sequence &cur_sequence() { return sequences.back(); }
        inline const text_sequence &cur_sequence() const { return sequences.back(); }
    };

    console_text_buffer();

    void clear();
    void write(pcstr text, size_t len);

    inline void apply_default_style() { current_style = default_style; }
    inline const std::vector<line> &lines() const { return _lines; }

    formatting_params default_style;

protected:
    void put(char c);
    void process_ansi_code(int code);
    void new_sequence() { current_line().sequences.push_back({ current_style, cstring() }); }
    void reset_ansi_number() { ansi_number = 0; has_ansi_number = false; }

    inline line &current_line() { return _lines.back(); }

    formatting_params current_style;

    bool bright_text = false;
    AnsiColorCode text_code = ANSI_RESET;

    std::vector<line> _lines;

    bool parsing_ansi_code = false;
    bool listening_digits = false;
    int ansi_number = 0;
    bool has_ansi_number = false;
};

/// A user input line that supports callbacks; render() returns true when a line was submitted
struct imgui_input_line {
    using text_input_callbacks = std::unordered_map<ImGuiInputTextFlags, std::function<void(ImGuiInputTextCallbackData *)>>;

    text_input_callbacks text_callbacks;

    ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;

    bool reclaim_focus = false;

    static int text_edit_callback_stub(ImGuiInputTextCallbackData *data);

    bool render(int width);
    pcstr submitted() const { return _submitted.c_str(); }

private:
    bstring512 _buffer;
    bstring512 _submitted;
};

/// Output pane with ANSI color code support and text filtering via 'filter'
class imgui_output_pane {
    bool line_pass_filter(const console_text_buffer::line &l) const;

public:
    console_text_buffer text;
    ImGuiTextFilter filter;

    bool auto_scroll_enabled = true;
    bool should_scroll_to_bottom = false;

    /// Indices (into text.lines()) of currently selected lines for multi-select copy.
    std::set<int> selected_lines;
    /// Anchor index for shift+click range selection.
    int last_clicked_idx = -1;

    inline void clear() {
        text.clear();
        selected_lines.clear();
        last_clicked_idx = -1;
    }

    void render();

    /// All lines passing the current filter as plain text, newline-separated.
    cstring all_text() const;

    /// Currently-selected lines as plain text, newline-separated. Empty if no selection.
    cstring selection_text() const;
};

/// Quake style console : IMGUI Widget
class imgui_qconsole : public console_output {
public:
    qconsole con;
    imgui_output_pane output;
    imgui_input_line input;
    size_t prev_line_count = 0; ///< used to autoscroll when output gets a new line

    ImFont *font = nullptr;

    int history_pos = -1; ///< index into the console history, for up/down arrow

    float font_scale = 1.2f;
    bool skip_event = false;

    imgui_qconsole();

    void write(pcstr text, size_t len) override { output.text.write(text, len); }

    void clear() { output.clear(); }
    void load_command_history();
    void render(const char *title, bool &p_open, int width, int height);

private:
    void history_callback(ImGuiInputTextCallbackData *data);
    void text_completion_callback(ImGuiInputTextCallbackData *data);
    void save_command_history();
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
