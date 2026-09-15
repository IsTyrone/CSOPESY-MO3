/*
 *  CSOPESY Semi-Major Output 1  —  OS Emulator
 *  Entry point + game loop
 *
 *  Uses a non-blocking game-loop approach:
 *    • _kbhit() / _getch() for input  (no echo, no cursor fights)
 *    • Marquee::update() for animation (timer-gated, no extra thread)
 *
 *  Compile using (MSVC):
 *      cl /EHsc /std:c++17 main.cpp ConsoleUI.cpp Marquee.cpp CommandInterpreter.cpp /Fe:csopesy.exe
 *
 *  Compile using (MinGW g++):
 *      g++ -std=c++17 -o csopesy.exe main.cpp ConsoleUI.cpp Marquee.cpp CommandInterpreter.cpp
 */

#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <windows.h>

#include "ConsoleUI.h"
#include "Marquee.h"
#include "CommandInterpreter.h"

int main() {
    ConsoleUI::init();

    const std::vector<std::string> developers = {
        "Carlo Barreo",
        "Gaibril Kyle",
        "David Javier",
        "Tyrone Lee"
    };
    const std::string versionDate = "09/15/2026";

    ConsoleUI::drawFullLayout(developers, versionDate);

    // Create core components
    Marquee marquee;
    CommandInterpreter interpreter(marquee);

    std::string              inputBuffer;
    std::vector<std::string> outputHistory;
    bool running = true;

    // Game loop
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

    // Goodbye sequence
    Sleep(600);
    ConsoleUI::cleanup();
    return 0;
}
