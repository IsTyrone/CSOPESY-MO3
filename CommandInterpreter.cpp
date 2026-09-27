#include "CommandInterpreter.h"
#include "Marquee.h"
#include <algorithm>
#include <cctype>

CommandInterpreter::CommandInterpreter(Marquee& marquee): m_marquee(marquee) {
}

CommandInterpreter::Result CommandInterpreter::execute(const std::string& input) {
    std::string trimmed = input;
    auto notSpace = [](unsigned char c) { return !std::isspace(c); };
    trimmed.erase(trimmed.begin(), std::find_if(trimmed.begin(), trimmed.end(), notSpace));
    trimmed.erase(std::find_if(trimmed.rbegin(), trimmed.rend(), notSpace).base(), trimmed.end());
    if (trimmed.empty()) return { {}, false };

    std::string cmd, args;
    auto sp = trimmed.find(' ');
    if (sp != std::string::npos) {
        cmd  = trimmed.substr(0, sp);
        args = trimmed.substr(sp + 1);
        args.erase(args.begin(), std::find_if(args.begin(), args.end(), notSpace));
    } else {
        cmd = trimmed;
    }

    std::string lc = cmd;
    std::transform(lc.begin(), lc.end(), lc.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

    if (lc == "help")           
        return cmdHelp();
    if (lc == "start_marquee")  
        return cmdStartMarquee();
    if (lc == "stop_marquee")   
        return cmdStopMarquee();
    if (lc == "set_text")       
        return cmdSetText(args);
    if (lc == "set_speed")      
        return cmdSetSpeed(args);
    if (lc == "exit")           
        return cmdExit();

    return cmdUnknown(cmd);
}

CommandInterpreter::Result CommandInterpreter::cmdHelp() {
    return {
        {
            "Available commands:",
            "  help            Display this help message",
            "  start_marquee   Start the marquee animation",
            "  stop_marquee    Stop the marquee animation",
            "  set_text <t>    Set the marquee display text",
            "  set_speed <ms>  Set refresh rate in milliseconds",
            "  exit            Exit the program"
        },
        false
    };
}

CommandInterpreter::Result CommandInterpreter::cmdStartMarquee() {
    if (m_marquee.isRunning())
        return { { "Marquee is already running." }, false };
    m_marquee.start();
    return { { "Marquee started." }, false };
}

CommandInterpreter::Result CommandInterpreter::cmdStopMarquee() {
    if (!m_marquee.isRunning())
        return { { "Marquee is not running." }, false };
    m_marquee.stop();
    return { { "Marquee stopped." }, false };
}

CommandInterpreter::Result CommandInterpreter::cmdSetText(const std::string& args) {
    if (args.empty())
        return { { "Usage: set_text <text>" }, false };
    m_marquee.setText(args);
    return { { "Marquee text set to: " + args }, false };
}

CommandInterpreter::Result CommandInterpreter::cmdSetSpeed(const std::string& args) {
    if (args.empty())
        return { { "Usage: set_speed <milliseconds>" }, false };
    try {
        size_t pos;
        int speed = std::stoi(args, &pos);
        if (pos != args.size())
            return { { "must be a whole number in milliseconds (e.g. 100)" }, false };
        if (speed <= 0)
            return { { "Speed must be a positive integer." }, false };
        m_marquee.setSpeed(speed);
        return { { "Marquee speed set to " + std::to_string(speed) + " ms." }, false };
    } catch (...) {
        return { { "Invalid number: " + args }, false };
    }
}

CommandInterpreter::Result CommandInterpreter::cmdExit() {
    if (m_marquee.isRunning()) m_marquee.stop();
    return { { "Goodbye!" }, true };
}

CommandInterpreter::Result CommandInterpreter::cmdUnknown(const std::string& cmd) {
    return { { "Unknown command: " + cmd + "  (type 'help' for available commands)" }, false };
}
