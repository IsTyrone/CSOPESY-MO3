#pragma once
#include <string>
#include <vector>
#include <windows.h>

namespace Layout {
    constexpr int TOP_SEP        = 0;
    constexpr int ART_START      = 1;
    constexpr int ART_LINES      = 5;
    constexpr int SUBTITLE       = 6;
    constexpr int DEV_LABEL      = 8;
    constexpr int DEV_START      = 9;
    constexpr int DEV_COUNT      = 4;
    constexpr int VERSION        = 13;

    constexpr int MARQUEE_TOP    = 14;
    constexpr int MARQUEE        = 15;                       // 15..19
    constexpr int MARQUEE_ROWS   = 5;
    constexpr int MARQUEE_BOT    = MARQUEE + MARQUEE_ROWS;   // 20

    constexpr int OUTPUT_START   = MARQUEE_BOT + 1;          // 21
    constexpr int OUTPUT_LINES   = 7;                        // 21..27
    constexpr int OUTPUT_SEP     = OUTPUT_START + OUTPUT_LINES; // 28
    constexpr int PROMPT         = OUTPUT_SEP + 1;           // 29
    constexpr int PROMPT_PREFIX  = 11;
}

namespace Color {
    inline const char* RESET    = "\033[0m";
    inline const char* BOLD     = "\033[1m";
    inline const char* BGREEN   = "\033[92m";
}

class ConsoleUI {
public:
    static void init();
    static void cleanup();
    static void clearScreen();

    static void drawFullLayout(
        const std::vector<std::string>& developers,
        const std::string& versionDate);

    static void drawAsciiArt();

    static void drawSeparator(int row, char ch = '=');
    static void drawMarqueeArt(const std::vector<std::string>& artRows,
                               int position,
                               int frame = 0);
    static void clearMarqueeArea();
    static void drawOutputArea(const std::vector<std::string>& lines);
    static void drawPrompt(const std::string& inputBuffer);

    static int  getConsoleWidth();
    static void setCursorPos(short x, short y);
    static void clearRow(int row);

private:
    static HANDLE s_hOut;
    static HANDLE s_hIn;
    static DWORD  s_origOutMode;
    static DWORD  s_origInMode;
};