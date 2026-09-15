CSOPESY Semi-Major Output 1 — OS Emulator
==========================================

Group Members:
  - Carlo Barreo
  - Gaibril Kyle
  - David Javier
  - Tyrone Lee

Entry Point:
  main.cpp

Build Instructions:
-------------------

  Option A — MinGW (g++):
    g++ -std=c++17 -static -static-libgcc -static-libstdc++ -o csopesy.exe main.cpp ConsoleUI.cpp Marquee.cpp CommandInterpreter.cpp

    (The -static flags embed the C++ runtime so the exe runs on any
     machine without needing libstdc++-6-x64.dll / libgcc DLLs.)

  Option B — One-click script:
    build.bat

  Option C — MSVC (cl):
    cl /EHsc /std:c++17 main.cpp ConsoleUI.cpp Marquee.cpp CommandInterpreter.cpp /Fe:csopesy.exe

Run:
----
    .\csopesy.exe

Available Commands:
-------------------
    help            Display available commands
    start_marquee   Start the marquee animation
    stop_marquee    Stop the marquee animation
    set_text <t>    Set the marquee display text
    set_speed <ms>  Set the marquee refresh rate in milliseconds
    exit            Exit the program
