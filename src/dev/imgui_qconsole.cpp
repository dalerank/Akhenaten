#include "imgui_qconsole.h"

#include "content/vfs.h"
#include "platform/platform.h"

#include <algorithm>

namespace dev {

    bool imgui_output_pane::line_pass_filter(const console_text_buffer::line &l) const {
        for (const console_text_buffer::text_sequence &s : l.sequences) {
            if (filter.PassFilter(s.text.c_str()))
                return true;
        }

        return false;
    }

    void imgui_output_pane::render() {
        const ImGuiIO &io = ImGui::GetIO();
        int line_idx = -1;
        for (const console_text_buffer::line &line : text.lines()) {
            ++line_idx;
            if (!line_pass_filter(line))
                continue;

            // Wrap each line in a Selectable for click-to-copy + multi-select.
            // The Selectable provides hover highlight + click capture; the colored text is
            // overlaid on top using TextColored after resetting the cursor.
            const bool is_selected = selected_lines.count(line_idx) > 0;

            ImVec2 line_start = ImGui::GetCursorPos();
            ImGui::PushID(line_idx);
            const bool clicked = ImGui::Selectable("##cl", is_selected, 0, ImVec2(0, ImGui::GetTextLineHeight()));
            ImGui::PopID();

            if (clicked) {
                if (io.KeyShift && last_clicked_idx >= 0) {
                    // Shift+Click: replace selection with a contiguous range from anchor to here.
                    selected_lines.clear();
                    const int lo = std::min(last_clicked_idx, line_idx);
                    const int hi = std::max(last_clicked_idx, line_idx);
                    for (int i = lo; i <= hi; ++i) {
                        selected_lines.insert(i);
                    }
                } else if (io.KeyCtrl) {
                    // Ctrl+Click: toggle this line in/out of the selection.
                    if (is_selected) {
                        selected_lines.erase(line_idx);
                    } else {
                        selected_lines.insert(line_idx);
                    }
                    last_clicked_idx = line_idx;
                } else {
                    // Plain click: replace selection with just this line.
                    selected_lines.clear();
                    selected_lines.insert(line_idx);
                    last_clicked_idx = line_idx;
                }

                const cstring sel = selection_text();
                if (!sel.empty()) {
                    ImGui::SetClipboardText(sel.c_str());
                }
            }

            ImGui::SetCursorPos(line_start);

            for (const console_text_buffer::text_sequence &seq : line.sequences) {
                if (seq.style.has_background_color) {
                    ImVec2 textSize = ImGui::CalcTextSize(seq.text.c_str());
                    ImVec2 cursorScreenPos = ImGui::GetCursorScreenPos();
                    ImVec2 sum = ImVec2(textSize[0] + cursorScreenPos[0], textSize[1] + cursorScreenPos[1]);
                    ImGui::GetWindowDrawList()->AddRectFilled(cursorScreenPos, sum, seq.style.background_color);
                }

                ImGui::TextColored(seq.style.text_color, "%s", seq.text.c_str());
                ImGui::SameLine();
            }

            ImGui::NewLine();
        }

        if ((auto_scroll_enabled && should_scroll_to_bottom) || (auto_scroll_enabled && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
            ImGui::SetScrollHereY(1.0f);
        should_scroll_to_bottom = false;
    }

    cstring imgui_output_pane::all_text() const {
        cstring result;
        for (const console_text_buffer::line &line : text.lines()) {
            if (!line_pass_filter(line))
                continue;
            for (const console_text_buffer::text_sequence &seq : line.sequences) {
                result += seq.text;
            }
            result += '\n';
        }
        return result;
    }

    cstring imgui_output_pane::selection_text() const {
        cstring result;
        const auto &lines = text.lines();
        for (int idx : selected_lines) {
            if (idx < 0 || idx >= (int)lines.size()) {
                continue;
            }
            for (const console_text_buffer::text_sequence &seq : lines[idx].sequences) {
                result += seq.text;
            }
            result += '\n';
        }
        return result;
    }

    imgui_qconsole::imgui_qconsole() {
        input.text_callbacks[ImGuiInputTextFlags_CallbackCompletion] = [this] (ImGuiInputTextCallbackData *data) { text_completion_callback(data); };
        input.text_callbacks[ImGuiInputTextFlags_CallbackHistory] = [this] (ImGuiInputTextCallbackData *data) { history_callback(data); };

        con.bind_command("clear", [this] (console_args &, console_output &) { clear(); }, "Clear the console");
        con.bind_cvar("fontScale", font_scale);
        con.style = qconsole::styling_color();
    }

    void imgui_qconsole::render(const char *title, bool &p_open, int width, int height) {
        if (!p_open) return;

        if (font) {
            ImGui::PushFont(font);
        }

        ImGui::SetNextWindowPos({ 0, 0 });
        ImGui::SetNextWindowSize(ImVec2(width, height));

        ImGui::Begin(title, &p_open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
        ImGui::SetWindowFontScale(font_scale);

        if (ImGui::SmallButton("Copy All")) {
            const cstring all = output.all_text();
            if (!all.empty()) {
                ImGui::SetClipboardText(all.c_str());
            }
        }
        ImGui::SameLine();
        if (ImGui::SmallButton("Clear")) {
            output.clear();
        }
        ImGui::SameLine();
        ImGui::Checkbox("Auto-scroll", &output.auto_scroll_enabled);

        // Reserve enough left-over height for 1 separator + 1 input text
        const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
        ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar);

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing

        output.render();

        if (prev_line_count < output.text.lines().size()) {
            output.should_scroll_to_bottom = true;
        }
        prev_line_count = output.text.lines().size();

        ImGui::PopStyleVar();
        ImGui::EndChild();
        ImGui::Separator();

        if (input.render(width)) {
            history_pos = -1;

            con.execute(input.submitted(), *this);
            save_command_history();
            // On command input, we scroll to bottom even if AutoScroll==false
            output.should_scroll_to_bottom = true;
        }

        if (font) {
            ImGui::PopFont();
        }

        ImGui::End();
    }

    void imgui_qconsole::history_callback(ImGuiInputTextCallbackData *data) {
        const int history_size = (int)con.history().size();
        const int prev_history_pos = history_pos;
        if (data->EventKey == ImGuiKey_UpArrow) {
            if (history_pos == -1) {
                history_pos = history_size - 1;
            } else if (history_pos > 0) {
                history_pos--;
            }
        } else if (data->EventKey == ImGuiKey_DownArrow) {
            if (history_pos != -1) {
                if (++history_pos >= history_size) {
                    history_pos = -1;
                }
            }
        }

        // A better implementation would preserve the data on the current input line along with cursor position.
        if (prev_history_pos != history_pos) {
            const char *history_str = (history_pos >= 0) ? con.history()[history_pos].c_str() : "";
            data->DeleteChars(0, data->BufTextLen);
            data->InsertChars(0, history_str);
        }
    }

    void imgui_qconsole::text_completion_callback(ImGuiInputTextCallbackData *data) {
        // Locate beginning of current word
        const char *word_end = data->Buf + data->CursorPos;
        const char *word_start = word_end;
        while (word_start > data->Buf) {
            const char c = word_start[-1];
            if (c == ' ' || c == '\t' || c == ',' || c == ';')
                break;
            word_start--;
        }

        const int word_len = (int)(word_end - word_start);

        // Command and cvar names are interned, so the pointers stay valid.
        std::vector<pcstr> candidates;
        for (const auto &it : con.commands()) {
            if (Strnicmp(it.first.c_str(), word_start, word_len) == 0) {
                candidates.push_back(it.first.c_str());
            }
        }

        for (const auto &it : con.cvars()) {
            if (Strnicmp(it.first.c_str(), word_start, word_len) == 0) {
                candidates.push_back(it.first.c_str());
            }
        }

        if (candidates.empty()) {
            printf("No match for \"%.*s\"!\n", word_len, word_start);
        } else if (candidates.size() == 1) {
            // Single match. Delete the beginning of the word and replace it entirely so we've got nice casing.
            data->DeleteChars((int)(word_start - data->Buf), word_len);
            data->InsertChars(data->CursorPos, candidates[0]);
            data->InsertChars(data->CursorPos, " ");
        } else {
            // Multiple matches. Complete as much as we can..
            // So inputing "C"+Tab will complete to "CL" then display "CLEAR" and "CLASSIFY" as matches.
            int match_len = word_len;
            for (;;) {
                int c = 0;
                bool all_candidates_matches = true;
                for (int i = 0; i < (int)candidates.size() && all_candidates_matches; i++) {
                    if (i == 0) {
                        c = toupper(candidates[i][match_len]);
                    } else if (c == 0 || c != toupper(candidates[i][match_len])) {
                        all_candidates_matches = false;
                    }
                }

                if (!all_candidates_matches) {
                    break;
                }
                match_len++;
            }

            if (match_len > 0) {
                data->DeleteChars((int)(word_start - data->Buf), word_len);
                data->InsertChars(data->CursorPos, candidates[0], candidates[0] + match_len);
            }

            print("Possible matches:\n");
            std::sort(candidates.begin(), candidates.end(), [] (pcstr a, pcstr b) { return ::strcmp(a, b) < 0; });
            for (pcstr candidate : candidates) {
                printf("- %s\n", candidate);
            }
        }
    }

    console_text_buffer::console_text_buffer() {
        clear();
    }

    void console_text_buffer::clear() {
        // swap forces reallocation, unlike clear
        std::vector<line> x;
        _lines.swap(x);

        _lines.push_back(line());
        new_sequence();
    }

    void console_text_buffer::write(pcstr text, size_t len) {
        for (size_t i = 0; i < len; ++i) {
            put(text[i]);
        }
    }

    void console_text_buffer::process_ansi_code(int code) {
        switch (code) {
        case ANSI_RESET:
            current_style = default_style;
            break;

        case ANSI_BRIGHT_TEXT:
            bright_text = true;
            if (text_code) {
                current_style.text_color = getAnsiTextColorBright(text_code);
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
            text_code = (AnsiColorCode)code;
            current_style.text_color = bright_text ? getAnsiTextColorBright(text_code) : getAnsiTextColor(text_code);
            break;

        case ANSI_BLACK_BKGRND:
        case ANSI_RED_BKGRND:
        case ANSI_GREEN_BKGRND:
        case ANSI_YELLOW_BKGRND:
        case ANSI_BLUE_BKGRND:
        case ANSI_MAGENTA_BKGRND:
        case ANSI_CYAN_BKGRND:
        case ANSI_WHITE_BKGRND:
            current_style.has_background_color = true;
            current_style.background_color = getANSIBackgroundColor((AnsiColorCode)code);
            break;

        default:
            break;
        }
    }

    void console_text_buffer::put(char c) {
        if (parsing_ansi_code) {
            if (::isdigit((unsigned char)c) && listening_digits) {
                ansi_number = ansi_number * 10 + (c - '0');
                has_ansi_number = true;
                return;
            }

            switch (c) {
            case 'm': // end of ansi code; apply color formatting to new sequence
                parsing_ansi_code = false;
                if (has_ansi_number) {
                    process_ansi_code(ansi_number);
                }
                reset_ansi_number();
                bright_text = false;
                new_sequence();
                break;

            case '[':
                listening_digits = true;
                reset_ansi_number();
                break;

            case ';':
                if (has_ansi_number) {
                    process_ansi_code(ansi_number);
                }
                reset_ansi_number();
                break;

            default: // malformed sequence: drop it
                reset_ansi_number();
                listening_digits = false;
                parsing_ansi_code = false;
                break;
            }
            return;
        }

        switch (c) {
        case '\u001b':
            parsing_ansi_code = true;
            reset_ansi_number();
            break;

        case '\n':
            _lines.push_back(line());
            new_sequence();
            break;

        default:
            current_line().cur_sequence().text += c;
            break;
        }
    }

    int imgui_input_line::text_edit_callback_stub(ImGuiInputTextCallbackData *data) {
        text_input_callbacks *ic = (text_input_callbacks *)data->UserData;
        if (!ic)
            return 0;

        auto it = ic->find(data->EventFlag);
        if (it != ic->end()) {
            it->second(data);
        }

        return 0;
    }

    bool imgui_input_line::render(int width) {
        bool rval = false;

        ImGui::SetNextWindowSize(ImVec2(width, 0));
        if (reclaim_focus) {
            ImGui::SetKeyboardFocusHere(0); // Auto focus previous widget
            reclaim_focus = false;
        }

        if (ImGui::InputText("##Input", _buffer.data(), bstring512::capacity, input_text_flags, &text_edit_callback_stub, (void *)&text_callbacks)) {
            reclaim_focus = true;

            Strtrim(_buffer.data());
            if (!_buffer.empty()) {
                _submitted = _buffer;
                _buffer.clear();
                rval = true;
            }
        }

        // Auto-focus on window apparition
        ImGui::SetItemDefaultFocus();

        return rval;
    }

    void imgui_qconsole::load_command_history() {
        pcstr base_path = vfs::platform_file_manager_get_base_path();
        if (!base_path) {
            return;
        }

        vfs::path filepath(base_path, "/qconsole_history.txt");
        con.load_history(filepath);
    }

    void imgui_qconsole::save_command_history() {
        pcstr base_path = vfs::platform_file_manager_get_base_path();
        if (!base_path) {
            return;
        }

        vfs::path filepath(base_path, "/qconsole_history.txt");
        con.save_history(filepath);
    }

}
