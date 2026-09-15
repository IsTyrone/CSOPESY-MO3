# CSOPESY-MO3 Project File Guide

This guide explains what each main file in the project does.

## 1. `main.cpp`

This is the **main file** where the program starts.

**Functions:**

* Sets up the console UI.
* Creates the `Marquee` and `CommandInterpreter` objects.
* Checks for keyboard input.
* Sends commands to the command interpreter when Enter is pressed.
* Updates the marquee animation.

## 2. `ConsoleUI.h` and `ConsoleUI.cpp`

These files handle the **console display**.

**Functions:**

* Sets up and cleans up the console.
* Draws the main screen layout.
* Displays and clears the moving marquee.
* Shows the `Command>` prompt.
* Displays command output and handles scrolling.
* Controls text position and colors.

## 3. `Marquee.h` and `Marquee.cpp`

These files handle the **moving text marquee**.

**Functions:**

* Sets and gets the marquee text.
* Starts and stops the marquee.
* Controls the marquee speed.
* Updates the text position.
* Makes the text move back and forth across the screen.

## 4. `CommandInterpreter.h` and `CommandInterpreter.cpp`

These files handle **user commands**.

**Functions:**

* Reads and processes user input.
* Identifies the command and its arguments.
* Runs commands such as:

  * `help`
  * `start`
  * `stop`
  * `settext`
  * `setspeed`
  * `exit`
* Controls the `Marquee` based on the user's commands.

## 5. Build and Documentation Files

- `build.bat` – Compiles the C++ files and creates `csopesy.exe`.
- `README.txt` / `prerequisite.md` – Contains project information, requirements, and setup instructions.
