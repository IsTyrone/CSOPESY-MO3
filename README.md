# CSOPESY Semi-Major Output 1 — OS Emulator

## Group Members

* Carlo Barreo
* Gaibril Kyle
* David Javier
* Tyrone Lee

## Entry Point

```text
main.cpp
```

## Build Instructions

### Option A — MinGW (g++)

Compile the project using:

```bash
g++ -std=c++17 -static -static-libgcc -static-libstdc++ -o csopesy.exe main.cpp ConsoleUI.cpp Marquee.cpp CommandInterpreter.cpp
```

The `-static` flags embed the C++ runtime libraries into the executable, allowing the `.exe` to run on machines without requiring:

```text
libstdc++-6-x64.dll
libgcc DLLs
```

### Option B — One-Click Build Script

Run the included:

```text
build.bat
```

### Option C — MSVC (cl)

Using Microsoft Visual C++:

```bash
cl /EHsc /std:c++17 main.cpp ConsoleUI.cpp Marquee.cpp CommandInterpreter.cpp /Fe:csopesy.exe
```

## Running the Program

After successfully building the project, run:

```powershell
.\csopesy.exe
```

## Available Commands

| Command          | Description                                  |
| ---------------- | -------------------------------------------- |
| `help`           | Display available commands                   |
| `start_marquee`  | Start the marquee animation                  |
| `stop_marquee`   | Stop the marquee animation                   |
| `set_text <t>`   | Set the marquee display text                 |
| `set_speed <ms>` | Set the marquee refresh rate in milliseconds |
| `exit`           | Exit the program                             |

### Command Examples

```text
help
start_marquee
stop_marquee
set_text Hello World
set_speed 100
exit
```

## Project Structure

```text
.
├── main.cpp
├── ConsoleUI.cpp
├── Marquee.cpp
├── CommandInterpreter.cpp
├── build.bat
└── README.md
```

## Requirements

* C++17 or later
* MinGW (g++) or Microsoft Visual C++ (MSVC)
* Windows operating system
