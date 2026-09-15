#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <windows.h>

#include "ConsoleUI.h"
#include "Marquee.h"
#include "CommandInterpreter.h"
#include "AsciiFont.h"

int main() {
    ConsoleUI::init();

    // Load the external font file (must sit next to csopesy.exe)
    if (!AsciiFont::loadFont("font.txt")) {
        std::cerr << "Fatal: could not load font.txt. "
                     "Place it next to csopesy.exe.\n";
        ConsoleUI::cleanup();
        return 1;
    }

    const std::vector<std::string> developers = {
        "Carlo Barreo",
        "Gaibril Kyle",
        "David Javier",
        "Tyrone Lee"
    };
    const std::string versionDate = "09/15/2026";

    ConsoleUI::drawFullLayout(developers, versionDate);

    Marquee marquee;
    CommandInterpreter interpreter(marquee);

    std::string              inputBuffer;
    std::vector<std::string> outputHistory;
    bool running = true;

    while (running) {
        bool marqueeRendered = marquee.update();

        if (marqueeRendered) {
            ConsoleUI::setCursorPos(
                static_cast<short>(Layout::PROMPT_PREFIX + inputBuffer.size()),
                Layout::PROMPT);
        }

        if (_kbhit()) {
            int ch = _getch();

            if (ch == '\r' || ch == '\n') {
                if (!inputBuffer.empty()) {
                    outputHistory.push_back("> " + inputBuffer);

                    auto result = interpreter.execute(inputBuffer);
                    for (const auto& line : result.output)
                        outputHistory.push_back(line);

                    outputHistory.push_back("");

                    ConsoleUI::drawOutputArea(outputHistory);

                    if (result.shouldExit) {
                        running = false;
                        break;
                    }
                    inputBuffer.clear();
                }
                ConsoleUI::drawPrompt(inputBuffer);

            } else if (ch == 8 || ch == 127) {
                if (!inputBuffer.empty()) {
                    inputBuffer.pop_back();
                    ConsoleUI::drawPrompt(inputBuffer);
                }

            } else if (ch == 0 || ch == 224) {
                _getch();

            } else if (ch >= 32 && ch < 127) {
                inputBuffer += static_cast<char>(ch);
                ConsoleUI::drawPrompt(inputBuffer);
            }
        }

        Sleep(1);
    }

    Sleep(600);
    ConsoleUI::cleanup();
    return 0;
}