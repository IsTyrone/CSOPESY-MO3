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
| `initialize`     | Load settings from `config.txt`              |
| `start_marquee`  | Start the marquee animation                  |
| `stop_marquee`   | Stop the marquee animation                   |
| `set_text <t>`   | Set the marquee display text                 |
| `set_speed <ms>` | Set the marquee refresh rate in milliseconds |
| `exit`           | Exit the program                             |

### Command Examples

```text
help
initialize
start_marquee
stop_marquee
set_text Hello World
set_speed 100
exit
```

## Configuration (`config.txt`)

The program reads its OS emulator settings from `config.txt` at runtime via the `initialize` command. Edit this file before running to change behavior.

### CPU & Scheduling

| Parameter | Example | Description |
|-----------|---------|-------------|
| `num-cpu` | `4` | Number of CPU cores. Determines how many processes can run simultaneously. |
| `scheduler` | `"rr"` | Scheduling algorithm. `"rr"` = Round-Robin (processes take turns), `"fcfs"` = First-Come-First-Served (each process runs to completion). |
| `quantum-cycles` | `5` | Time quantum for Round-Robin only. Number of CPU cycles a process gets before being preempted. |

### Process Generation

| Parameter | Example | Description |
|-----------|---------|-------------|
| `batch-process-freq` | `1` | How often (in CPU cycles) a new process is generated. `1` = every cycle. |
| `min-ins` | `1000` | Minimum number of instructions assigned to a new process. |
| `max-ins` | `2000` | Maximum number of instructions assigned to a new process. |
| `delays-per-exec` | `0` | Number of idle cycles between each instruction execution. `0` = no delay. |

### Memory

| Parameter | Example | Description |
|-----------|---------|-------------|
| `max-overall-mem` | `1024` | Total system memory available (in KB). |
| `mem-per-frame` | `64` | Size of each memory frame for paging. Total frames = `max-overall-mem / mem-per-frame`. |
| `min-mem-per-proc` | `64` | Minimum memory a process requires. |
| `max-mem-per-proc` | `256` | Maximum memory a process requires. |

### Example `config.txt`

```text
num-cpu 4
scheduler "rr"
quantum-cycles 5
batch-process-freq 1
min-ins 1000
max-ins 2000
delays-per-exec 0
max-overall-mem 1024
mem-per-frame 64
min-mem-per-proc 64
max-mem-per-proc 256
```

## Project Structure

```text
.
├── main.cpp
├── ConsoleUI.cpp / .h
├── Marquee.cpp / .h
├── CommandInterpreter.cpp / .h
├── Config.cpp / .h
├── config.txt
├── build.bat
└── README.md
```

## Requirements

* C++17 or later
* MinGW (g++) or Microsoft Visual C++ (MSVC)
* Windows operating system
