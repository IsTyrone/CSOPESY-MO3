#pragma once
#include <string>
#include <vector>
#include <windows.h>
namespace Layout {
    constexpr int TOP_SEP        = 0;
    constexpr int ART_START      = 1;   // ASCII art occupies rows 1-5
    constexpr int ART_LINES      = 5;
    constexpr int SUBTITLE       = 6;   // "OS Emulator" centred
    constexpr int DEV_LABEL      = 8;
    constexpr int DEV_START      = 9;
    constexpr int DEV_COUNT      = 4;
    constexpr int VERSION        = 13;
    constexpr int MARQUEE_TOP    = 14;
    constexpr int MARQUEE        = 15;
    constexpr int MARQUEE_BOT    = 16;
    constexpr int OUTPUT_START   = 17;
    constexpr int OUTPUT_LINES   = 10;
    constexpr int OUTPUT_SEP     = 27;
    constexpr int PROMPT         = 28;
    constexpr int PROMPT_PREFIX  = 11;
}

// ── ANSI colour helpers ─────────────────────────────────────────
namespace Color {
    inline const char* RESET    = "\033[0m";
    inline const char* BOLD     = "\033[1m";
    inline const char* BGREEN   = "\033[92m";
}

// ── Static console-UI helper class ──────────────────────────────
class ConsoleUI {
public:
    static void init();
    static void cleanup();
    static void clearScreen();

    // Draw the complete initial layout (header + separators + prompt)
    static void drawFullLayout(
        const std::vector<std::string>& developers,
        const std::string& versionDate);

    // Draw the rainbow ASCII-art banner
    static void drawAsciiArt();

    // Partial-redraw helpers
    static void drawSeparator(int row, char ch = '=');
    static void drawMarqueeRow(const std::string& text, int position, int frame = 0);
    static void clearMarqueeRow();
    static void drawOutputArea(const std::vector<std::string>& lines);
    static void drawPrompt(const std::string& inputBuffer);

    // Low-level utilities
    static int  getConsoleWidth();
    static void setCursorPos(short x, short y);
    static void clearRow(int row);

private:
    static HANDLE s_hOut;
    static HANDLE s_hIn;
    static DWORD  s_origOutMode;
    static DWORD  s_origInMode;
};
