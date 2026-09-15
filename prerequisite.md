# CSOPESY OS Emulator — Prerequisites & Setup Guide

## What You Need

| Requirement | Details |
|-------------|---------|
| **OS** | Windows 10 or 11 |
| **C++ Compiler** | MinGW g++ (C++17 support) **or** MSVC (Visual Studio) |
| **Terminal** | Windows Terminal (recommended) or Command Prompt |

---

## Option A: MinGW (g++) — Recommended

### Step 1 — Download MinGW

1. Go to **https://github.com/niXman/mingw-builds-binaries/releases**
2. Download the latest **x86_64-...-posix-seh** `.7z` or `.zip` file
   - Example: `x86_64-13.2.0-release-posix-seh-ucrt-rt_v11-rev1.7z`
3. Extract the archive to a folder, e.g. `C:\mingw64`

> **Alternative:** You can also install MinGW through [MSYS2](https://www.msys2.org/):
> 1. Install MSYS2
> 2. Open MSYS2 terminal and run:
>    ```bash
>    pacman -S mingw-w64-x86_64-gcc
>    ```
> 3. The compiler will be at `C:\msys64\mingw64\bin\g++.exe`

### Step 2 — Add to PATH

1. Press **Win + S**, search for **"Environment Variables"**
2. Click **"Edit the system environment variables"**
3. Click **"Environment Variables..."**
4. Under **User variables**, select **Path** → click **Edit**
5. Click **New** and add the path to your MinGW `bin` folder, e.g.:
   ```
   C:\mingw64\bin
   ```
6. Click **OK** on all dialogs

### Step 3 — Verify Installation

Open a **new** terminal (PowerShell or CMD) and run:

```bash
g++ --version
```

You should see something like:

```
g++ (x86_64-posix-seh-rev1, Built by MinGW-Builds) 13.2.0
```

---

## Option B: Visual Studio (MSVC)

1. Download **Visual Studio 2022 Community** (free) from https://visualstudio.microsoft.com/
2. During installation, select the **"Desktop development with C++"** workload
3. Open the project folder in Visual Studio or use the **Developer Command Prompt**

---

## Building the Project

### With MinGW (g++)

Open a terminal in the project folder and run:

```bash
g++ -std=c++17 -static -static-libgcc -static-libstdc++ -o csopesy.exe main.cpp ConsoleUI.cpp Marquee.cpp CommandInterpreter.cpp
```

> The `-static` flags embed the C++ runtime into the exe so it runs on
> any machine without needing MinGW DLLs (`libstdc++-6-x64.dll`, etc.).
> Otherwise Windows may complain: "The code execution cannot proceed
> because libstdc++-6-x64 was not found."
>
> **One-click alternative:** double-click `build.bat` in the project folder.

### With MSVC (cl)

Open a **Developer Command Prompt for VS** and run:

```bash
cl /EHsc /std:c++17 main.cpp ConsoleUI.cpp Marquee.cpp CommandInterpreter.cpp /Fe:csopesy.exe
```

---

## Running the Program

```bash
.\csopesy.exe
```

> **Tip:** Use **Windows Terminal** for best results (proper ANSI color support).
> The default `cmd.exe` works too, but colors may look slightly different.

---

## Quick Command Reference

Once the program is running, type these at the `Command>` prompt:

| Command | What It Does |
|---------|-------------|
| `help` | Show all available commands |
| `start_marquee` | Start the bouncing text animation |
| `stop_marquee` | Stop the animation |
| `set_text Hello!` | Change the marquee text |
| `set_speed 50` | Make it faster (lower = faster) |
| `set_speed 300` | Make it slower |
| `exit` | Quit the program |

---

## Troubleshooting

| Problem | Solution |
|---------|----------|
| `g++ is not recognized` | Make sure MinGW's `bin` folder is in your PATH and you opened a **new** terminal after editing PATH |
| Colors look broken | Use **Windows Terminal** instead of legacy `cmd.exe` |
| Characters look garbled | Your console may not support UTF-8. Run `chcp 65001` before running the program |
| Compilation errors about `windows.h` | Make sure you're on Windows and using a Windows-targeting compiler (not WSL) |

---

## Project Files Overview

```
CSOPESY/
├── main.cpp                  ← Entry point (start here)
├── ConsoleUI.h / .cpp        ← Screen drawing & colors
├── Marquee.h / .cpp          ← Bouncing text logic
├── CommandInterpreter.h / .cpp ← Command parsing
├── README.txt                ← Build instructions
├── build.bat                 ← One-click static build script
└── prerequisite.md           ← This file
```
