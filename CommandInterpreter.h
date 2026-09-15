#pragma once
#include <string>
#include <vector>

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
    Result cmdUnknown(const std::string& cmd);

    Marquee& m_marquee;
};
