#include "imgui_qconsole.h"

#include "content/vfs.h"
#include "platform/platform.h"

namespace dev {

    bool IMGUIOstream::linePassFilter(const ConsoleBuf::Line &l) const {
        for (const ConsoleBuf::TextSequence &s : l.sequences) {
            const char *item = s.text.c_str();
            if (filter.PassFilter(item))
                return true;
        }

        return false;
    }

    void IMGUIOstream::renderInWindow(bool &p_open, const char *title) {
        ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);

        if (!ImGui::Begin(title, &p_open)) {
            ImGui::End();
            return;
        }

        render();

        ImGui::End();
    }


    void IMGUIOstream::render() {
        for (const ConsoleBuf::Line &line : strb.getLines()) {
            if (!linePassFilter(line))
                continue;

            for (const ConsoleBuf::TextSequence &seq : line.sequences) {
                if (seq.style.hasBackgroundColor) {
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

    imgui_qconsole::imgui_qconsole() {
        addStream(os);

        is.textCallbacks[ImGuiInputTextFlags_CallbackCompletion] = [this] (ImGuiInputTextCallbackData *data) { this->textCompletionCallback(data); };

        is.textCallbacks[ImGuiInputTextFlags_CallbackHistory] = [this] (ImGuiInputTextCallbackData *data) { this->historyCallback(data); };

        con.bind_member_command("clear", *this, &imgui_qconsole::clear, "Clear the console");
        con.bind_cvar("fontScale", fontScale);
        con.style = qconsole::ConsoleStylingColor();        
    }

    void imgui_qconsole::clear() { os.Clear(); }
    void imgui_qconsole::optionsMenu() { ImGui::Checkbox("Auto-scroll", &os.autoScrollEnabled); }

    void imgui_qconsole::render(const char *title, bool &p_open, int width, int height) {
        if (!p_open) return;

        if (font) {
            ImGui::PushFont(font);
        }

        ImGui::SetNextWindowPos({ 0, 0 });
        ImGui::SetNextWindowSize(ImVec2(width, height));

        ImGui::Begin(title, &p_open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
        ImGui::SetWindowFontScale(fontScale);

        // Reserve enough left-over height for 1 separator + 1 input text
        const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
        ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar);

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing

        os.render();

        if (prevLineCount < os.strb.getLines().size()) {
            os.shouldScrollToBottom = true;
        }
        prevLineCount = os.strb.getLines().size();

        ImGui::PopStyleVar();
        ImGui::EndChild();
        ImGui::Separator();

        if (is.render(width)) {
            HistoryPos = -1;

            con.commandExecute(is.getStream(), (*this)); 
            saveCommandHistory();
            // On command input, we scroll to bottom even if AutoScroll==false
            os.shouldScrollToBottom = true;
        }

        if (font) {
            ImGui::PopFont();
        }

        ImGui::End();
    }

    void imgui_qconsole::historyCallback(ImGuiInputTextCallbackData *data) {
        const int prev_history_pos = HistoryPos;
        if (data->EventKey == ImGuiKey_UpArrow) {
            if (HistoryPos == -1) {
                HistoryPos = con.historyBuffer().size() - 1;
            } else if (HistoryPos > 0) {
                HistoryPos--;
            }
        } else if (data->EventKey == ImGuiKey_DownArrow) {
            if (HistoryPos != -1) {
                if (++HistoryPos >= con.historyBuffer().size()) {
                    HistoryPos = -1;
                }
            }
        }

        // A better implementation would preserve the data on the current input line along with cursor position.
        if (prev_history_pos != HistoryPos) {
            const char *history_str = (HistoryPos >= 0) ? con.historyBuffer()[HistoryPos].c_str() : "";
            data->DeleteChars(0, data->BufTextLen);
            data->InsertChars(0, history_str);
        }
    }

    void imgui_qconsole::textCompletionCallback(ImGuiInputTextCallbackData *data) {
        // Locate beginning of current word
        const char *word_end = data->Buf + data->CursorPos;
        const char *word_start = word_end;
        while (word_start > data->Buf) {
            const char c = word_start[-1];
            if (c == ' ' || c == '\t' || c == ',' || c == ';')
                break;
            word_start--;
        }

        // Build a list of candidates
        ImVector<std::string> candidates;

        // autocomplete commands...
        for (auto it = con.getCommandTable().begin(); it != con.getCommandTable().end(); it++) {
            if (Strnicmp(it->first.c_str(), word_start, (int)(word_end - word_start)) == 0) {
                candidates.push_back(it->first);
            }
        }

        // ... and autcomplete variables
        for (auto it = con.getCVarReadTable().begin(); it != con.getCVarReadTable().end(); it++) {
            if (Strnicmp(it->first.c_str(), word_start, (int)(word_end - word_start)) == 0) {
                candidates.push_back(it->first);
            }
        }

        if (candidates.Size == 0) {
            // No match
            //AddLog("No match for %.*s, , word_start);
            (*this) << "No match for ";
            (*this) << (int)(word_end - word_start);
            (*this) << ' ' << word_start;
            (*this) << "!\n";
        } else if (candidates.Size == 1) {
            // Single match. Delete the beginning of the word and replace it entirely so we've got nice casing.
            data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
            data->InsertChars(data->CursorPos, candidates[0].c_str());
            data->InsertChars(data->CursorPos, " ");
        } else {
            // Multiple matches. Complete as much as we can..
            // So inputing "C"+Tab will complete to "CL" then display "CLEAR" and "CLASSIFY" as matches.
            int match_len = (int)(word_end - word_start);
            for (;;) {
                int c = 0;
                bool all_candidates_matches = true;
                for (int i = 0; i < candidates.Size && all_candidates_matches; i++) {
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
                data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
                data->InsertChars(data->CursorPos, candidates[0].c_str(), candidates[0].c_str() + match_len);
            }

            // List matches
            (*this) << "Possible matches:\n";
            std::sort(candidates.begin(), candidates.end());
            for (int i = 0; i < candidates.Size; i++) {
                (*this) << "- " << candidates[i] << '\n';
            }
        }
    }

    int MultiStreamBuf::overflow(int in) {
        char c = in; ///\todo check for eof, etc?
        for (std::ostream *str : streams) {
            (*str) << c;
        }
        return 1;
    }

    std::streamsize MultiStreamBuf::xsputn(const char *s, std::streamsize n) {
        std::streamsize ssz = 0;

        for (std::ostream *str : streams) {
            ssz = str->rdbuf()->sputn(s, n);
        }

        return ssz;
    }

    void ConsoleBuf::clear() {
        // swap forces reallocation, unlike clear
        std::vector<Line> x;
        lines.swap(x);
        //lines.clear();

        lines.push_back(Line());
        currentLine().sequences.push_back(TextSequence()); // start a new run of chars with default formatting
    }

    void ConsoleBuf::processANSICode(int code) {
        switch (code) {
        case ANSI_RESET:

            currentStyle = defaultStyle;

            break;
        case ANSI_BRIGHT_TEXT:
            brightText = true;
            if (textCode) {
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

            if (brightText) {
                currentStyle.textColor = getAnsiTextColorBright((AnsiColorCode)code);
            } else {
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

    int ConsoleBuf::overflow(int c) {
        if (c != EOF) {
            if (parsingANSICode) {
                bool error = false;

                if (std::isdigit((char)c) && listeningDigits) {
                    numParse << (char)c;
                } else {
                    switch (c) {
                    case 'm': // end of ansi code; apply color formatting to new sequence
                    {
                        parsingANSICode = false;

                        int x;
                        if (numParse >> x) {
                            processANSICode(x);
                        }

                        numParse.clear();

                        brightText = false;

                        currentLine().sequences.push_back({ currentStyle, "" });

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

                    if (error) {
                        numParse.clear();
                        listeningDigits = false;
                        parsingANSICode = false;

                        std::cerr << c;
                        //curStr() += (char)c;
                    }
                }
            } else {
                switch (c) {
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
                    currentLine().sequences.push_back(TextSequence({ currentStyle, "", }));
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

    ConsoleBuf::ConsoleBuf() {
        lines.push_back(Line());
        currentLine().sequences.push_back(TextSequence()); // start a new run of chars with default formatting
    }

    IMGUIInputLine::IMGUIInputLine() {
    }

    std::istream &IMGUIInputLine::getStream() {
        return stream;
    }

    std::string IMGUIInputLine::getInput() {
        std::string rval;
        std::getline(stream, rval);
        return rval;
    }

    int IMGUIInputLine::TextEditCallbackStub(ImGuiInputTextCallbackData *data) {
        TextInputCallbacks *ic = (TextInputCallbacks *)data->UserData;

        if (!ic)
            return 0;

        if (ic->find(data->EventFlag) != ic->end()) {
            (*ic)[data->EventFlag](data);
        }

        return 0;
    }

    bool IMGUIInputLine::renderInWindow(bool &p_open, const char *title) {
        ImGui::SetNextWindowSize(ImVec2(320, 0), ImGuiCond_FirstUseEver);

        if (!ImGui::Begin(title, &p_open)) {
            ImGui::End();
            return false;
        }

        bool rval = render(ImGui::GetWindowWidth());

        ImGui::End();

        return rval;
    }

    bool IMGUIInputLine::render(int width) {
        bool rval = false;

        ImGui::SetNextWindowSize(ImVec2(width, 0));
        if (reclaim_focus) {
            ImGui::SetKeyboardFocusHere(0); // Auto focus previous widget
            reclaim_focus = false;
        }
        if (ImGui::InputText("##Input", &InputBuf, input_text_flags, &TextEditCallbackStub, (void *)(&textCallbacks))) {
            reclaim_focus = true;

            char *s = InputBuf.data();
            Strtrim(s);

            if (InputBuf.length() && strlen(s)) {
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

    void imgui_qconsole::loadCommandHistory() {
        pcstr base_path = vfs::platform_file_manager_get_base_path();
        if (!base_path) {
            return;
        }
        
        vfs::path filepath(base_path, "/qconsole_history.txt");
        con.loadHistoryBuffer(filepath);
    }

    void imgui_qconsole::saveCommandHistory() {
        pcstr base_path = vfs::platform_file_manager_get_base_path();
        if (!base_path) {
            return;
        }
        
        vfs::path filepath(base_path, "/qconsole_history.txt");
        con.saveHistoryBuffer(filepath);
    }

}