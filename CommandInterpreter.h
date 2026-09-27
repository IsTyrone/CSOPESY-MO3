#pragma once
#include <string>
#include <vector>
#include "Config.h"

class Marquee;

class CommandInterpreter {
public:
    struct Result {
        std::vector<std::string> output;
        bool shouldExit = false;
    };

    explicit CommandInterpreter(Marquee& marquee);

    Result execute(const std::string& input);

private:
    Result cmdHelp();
    Result cmdStartMarquee();
    Result cmdStopMarquee();
    Result cmdSetText(const std::string& args);
    Result cmdSetSpeed(const std::string& args);
    Result cmdExit();
    Result cmdInitialize();
    Result cmdUnknown(const std::string& cmd);

    Marquee& m_marquee;
    Config   m_config;
};
