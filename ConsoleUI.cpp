#include "ConsoleUI.h"
#include <iostream>

HANDLE ConsoleUI::s_hOut       = INVALID_HANDLE_VALUE;
HANDLE ConsoleUI::s_hIn        = INVALID_HANDLE_VALUE;
DWORD  ConsoleUI::s_origOutMode = 0;
DWORD  ConsoleUI::s_origInMode  = 0;

void ConsoleUI::init() {
    s_hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    s_hIn  = GetStdHandle(STD_INPUT_HANDLE);

    GetConsoleMode(s_hOut, &s_origOutMode);
    GetConsoleMode(s_hIn,  &s_origInMode);

    DWORD outMode = s_origOutMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(s_hOut, outMode);

    SetConsoleOutputCP(CP_UTF8);

    SetConsoleTitleA("CSOPESY OS Emulator");

    CONSOLE_CURSOR_INFO ci = { 25, FALSE };
    SetConsoleCursorInfo(s_hOut, &ci);
}

void ConsoleUI::cleanup() {
    SetConsoleMode(s_hOut, s_origOutMode);
    SetConsoleMode(s_hIn,  s_origInMode);

    CONSOLE_CURSOR_INFO ci = { 25, TRUE };
    SetConsoleCursorInfo(s_hOut, &ci);

    std::cout << Color::RESET;
    clearScreen();
}

void ConsoleUI::clearScreen() {
    COORD topLeft = { 0, 0 };
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD written;

    GetConsoleScreenBufferInfo(s_hOut, &csbi);
    DWORD cells = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacterA(s_hOut, ' ', cells, topLeft, &written);
    FillConsoleOutputAttribute(s_hOut, csbi.wAttributes, cells, topLeft, &written);
    setCursorPos(0, 0);
}

void ConsoleUI::drawFullLayout(
    const std::vector<std::string>& developers,
    const std::string& versionDate)
{
    clearScreen();

    drawSeparator(Layout::TOP_SEP);

    setCursorPos(2, Layout::WELCOME);
    std::cout << Color::BOLD << "Welcome to CSOPESY!" << Color::RESET << std::flush;

    setCursorPos(2, Layout::DEV_LABEL);
    std::cout << "Group developers:" << Color::RESET << std::flush;

    for (int i = 0; i < static_cast<int>(developers.size()) && i < Layout::DEV_COUNT; ++i) {
        setCursorPos(4, Layout::DEV_START + i);
        std::cout << developers[i] << Color::RESET << std::flush;
    }

    setCursorPos(2, Layout::VERSION);
    std::cout << "Version date: " << versionDate << Color::RESET << std::flush;
              
    drawSeparator(Layout::MARQUEE_TOP);
    drawSeparator(Layout::MARQUEE_BOT);
    drawSeparator(Layout::OUTPUT_SEP, '-');
    
    drawPrompt("");
}

void ConsoleUI::drawSeparator(int row, char ch) {
    int width = getConsoleWidth();
    setCursorPos(0, static_cast<short>(row));

    for (int i = 0; i < width; ++i) std::cout << ch;
    std::cout << Color::RESET << std::flush;
}

void ConsoleUI::drawMarqueeRow(const std::string& text, int position) {
    clearRow(Layout::MARQUEE);
    if (text.empty() || position < 0) return;

    setCursorPos(static_cast<short>(position), Layout::MARQUEE);

    int maxLen = getConsoleWidth() - position;
    std::string display = (static_cast<int>(text.size()) > maxLen)
                              ? text.substr(0, maxLen)
                              : text;

    std::cout << Color::BOLD << Color::BGREEN << display << Color::RESET << std::flush;
}

void ConsoleUI::clearMarqueeRow() {
    clearRow(Layout::MARQUEE);
}

void ConsoleUI::drawOutputArea(const std::vector<std::string>& lines) {
    int max   = Layout::OUTPUT_LINES;
    int total = static_cast<int>(lines.size());
    int start = (total > max) ? total - max : 0;
    int width = getConsoleWidth();

    for (int i = 0; i < max; ++i) {
        int row = Layout::OUTPUT_START + i;
        clearRow(row);
        int idx = start + i;
        if (idx < total) {
            setCursorPos(2, static_cast<short>(row));

            std::string line = lines[idx];
            int maxLen = width - 4;
            if (static_cast<int>(line.size()) > maxLen)
                line = line.substr(0, maxLen);

            if (line.size() >= 2 && line[0] == '>' && line[1] == ' ')
                std::cout <<  line << Color::RESET;
            else
                std::cout <<  line << Color::RESET;

            std::cout << std::flush;
        }
    }
}

void ConsoleUI::drawPrompt(const std::string& inputBuffer) {
    clearRow(Layout::PROMPT);
    setCursorPos(0, Layout::PROMPT);

    std::cout << Color::BOLD <<"  Command> "
              << Color::RESET << inputBuffer
              << Color::RESET << std::flush;

    CONSOLE_CURSOR_INFO ci = { 25, TRUE };
    SetConsoleCursorInfo(s_hOut, &ci);
}
int ConsoleUI::getConsoleWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(s_hOut, &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

void ConsoleUI::setCursorPos(short x, short y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(s_hOut, pos);
}

void ConsoleUI::clearRow(int row) {
    int   width = getConsoleWidth();
    COORD pos   = { 0, static_cast<SHORT>(row) };
    DWORD written;
    FillConsoleOutputCharacterA(s_hOut, ' ', width, pos, &written);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(s_hOut, &csbi);
    FillConsoleOutputAttribute(s_hOut, csbi.wAttributes, width, pos, &written);
}
