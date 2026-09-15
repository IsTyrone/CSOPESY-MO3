#include "ConsoleUI.h"
#include <iostream>
#include <cmath>

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

static void hsvToRgb(float h, float s, float v, int& r, int& g, int& b);

static std::string blockify(const char* pattern) {
    std::string result;
    for (const char* p = pattern; *p; ++p) {
        if (*p == '#')
            result += "\xe2\x96\x88";   // U+2588 FULL BLOCK
        else
            result += *p;
    }
    return result;
}

void ConsoleUI::drawAsciiArt() {
    static const char* patterns[] = {
        "  ###### #######  ######  ######  ####### ####### ##    ##",
        " ##      ##      ##    ## ##   ## ##      ##       ##  ## ",
        " ##      ####### ##    ## ######  #####   #######   ####  ",
        " ##           ## ##    ## ##      ##           ##    ##   ",
        "  ###### #######  ######  ##      ####### #######    ##   ",
    };

    int width = getConsoleWidth();

    for (int line = 0; line < Layout::ART_LINES; ++line) {
        std::string row = blockify(patterns[line]);

        int cpCount = 0;
        for (size_t i = 0; i < row.size(); ) {
            unsigned char c = static_cast<unsigned char>(row[i]);
            if      ((c & 0x80) == 0)    i += 1;
            else if ((c & 0xE0) == 0xC0) i += 2;
            else if ((c & 0xF0) == 0xE0) i += 3;
            else                         i += 4;
            ++cpCount;
        }
        int pad = (width > cpCount) ? (width - cpCount) / 2 : 0;

        setCursorPos(static_cast<short>(pad),
                     static_cast<short>(Layout::ART_START + line));

        int charIdx = 0;
        for (size_t i = 0; i < row.size(); ) {
            unsigned char c = static_cast<unsigned char>(row[i]);
            int bytes = 1;
            if      ((c & 0xE0) == 0xC0) bytes = 2;
            else if ((c & 0xF0) == 0xE0) bytes = 3;
            else if ((c & 0xF8) == 0xF0) bytes = 4;

            std::string ch = row.substr(i, bytes);

            if (ch != " ") {
                float hue = fmodf(charIdx * 6.2f + line * 30.0f, 360.0f);
                int r, g, b;
                hsvToRgb(hue, 1.0f, 1.0f, r, g, b);
                std::cout << "\033[1m\033[38;2;"
                          << r << ";" << g << ";" << b << "m" << ch;
            } else {
                std::cout << ' ';
            }
            i += bytes;
            ++charIdx;
        }
        std::cout << Color::RESET << std::flush;
    }
}

void ConsoleUI::drawFullLayout(
    const std::vector<std::string>& developers,
    const std::string& versionDate)
{
    clearScreen();

    drawSeparator(Layout::TOP_SEP);

    drawAsciiArt();

    {
        std::string sub = "OS Emulator";
        int pad = (getConsoleWidth() > static_cast<int>(sub.size()))
                      ? (getConsoleWidth() - static_cast<int>(sub.size())) / 2
                      : 0;
        setCursorPos(static_cast<short>(pad), Layout::SUBTITLE);
        std::cout << Color::BOLD << sub << Color::RESET << std::flush;
    }

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

static void hsvToRgb(float h, float s, float v, int& r, int& g, int& b) {
    h = fmodf(h, 360.0f);
    if (h < 0) h += 360.0f;
    float c = v * s;
    float x = c * (1.0f - fabsf(fmodf(h / 60.0f, 2.0f) - 1.0f));
    float m = v - c;
    float rf = 0, gf = 0, bf = 0;
    if      (h < 60)  { rf = c; gf = x; }
    else if (h < 120) { rf = x; gf = c; }
    else if (h < 180) { gf = c; bf = x; }
    else if (h < 240) { gf = x; bf = c; }
    else if (h < 300) { rf = x; bf = c; }
    else              { rf = c; bf = x; }
    r = static_cast<int>((rf + m) * 255);
    g = static_cast<int>((gf + m) * 255);
    b = static_cast<int>((bf + m) * 255);
}

void ConsoleUI::drawMarqueeArt(const std::vector<std::string>& artRows,
                               int position,
                               int frame)
{
    clearMarqueeArea();
    if (artRows.empty() || position < 0) return;

    int width = getConsoleWidth();

    for (int r = 0; r < static_cast<int>(artRows.size()) &&
                    r < Layout::MARQUEE_ROWS; ++r)
    {
        const std::string& row = artRows[r];
        if (row.empty()) continue;

        int startCol = position;
        int visible  = width - startCol;
        if (visible <= 0) continue;

        std::string display = (static_cast<int>(row.size()) > visible)
                                  ? row.substr(0, visible)
                                  : row;

        setCursorPos(static_cast<short>(startCol),
                     static_cast<short>(Layout::MARQUEE + r));

        for (int i = 0; i < static_cast<int>(display.size()); ++i) {
            float hue = fmodf((i * 15.0f) + (frame * 6.0f) + (r * 20.0f), 360.0f);
            int rr, gg, bb;
            hsvToRgb(hue, 1.0f, 1.0f, rr, gg, bb);

            char c = display[i];
            if (c == ' ') {
                std::cout << ' ';
            } else {
                std::cout << "\033[1m\033[38;2;"
                          << rr << ";" << gg << ";" << bb << "m" << c;
            }
        }
        std::cout << Color::RESET << std::flush;
    }
}

void ConsoleUI::clearMarqueeArea() {
    for (int r = 0; r < Layout::MARQUEE_ROWS; ++r)
        clearRow(Layout::MARQUEE + r);
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

            std::cout << line << Color::RESET;
            std::cout << std::flush;
        }
    }
}

void ConsoleUI::drawPrompt(const std::string& inputBuffer) {
    clearRow(Layout::PROMPT);
    setCursorPos(0, Layout::PROMPT);

    std::cout << Color::BOLD << "  Command> "
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