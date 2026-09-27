#include "Config.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>

// Helper: remove leading/trailing whitespace
static std::string trim(const std::string& s) {
    auto b = s.find_first_not_of(" \t\r\n");
    if (b == std::string::npos) return "";
    auto e = s.find_last_not_of(" \t\r\n");
    return s.substr(b, e - b + 1);
}

// Helper: strip surrounding quotes from a string value
static std::string stripQuotes(const std::string& s) {
    if (s.size() >= 2 && s.front() == '"' && s.back() == '"')
        return s.substr(1, s.size() - 2);
    return s;
}

bool Config::loadFromFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) return false;

    std::string line;
    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '#') continue;   // skip blanks & comments

        std::istringstream iss(line);
        std::string key, value;
        if (!(iss >> key >> value)) continue;

        value = stripQuotes(value);

        if      (key == "num-cpu")            numCpu           = std::stoi(value);
        else if (key == "scheduler")          scheduler        = value;
        else if (key == "quantum-cycles")     quantumCycles    = std::stoi(value);
        else if (key == "batch-process-freq") batchProcessFreq = std::stoi(value);
        else if (key == "min-ins")            minIns           = std::stoi(value);
        else if (key == "max-ins")            maxIns           = std::stoi(value);
        else if (key == "delays-per-exec")    delaysPerExec    = std::stoi(value);
        else if (key == "max-overall-mem")    maxOverallMem    = std::stoi(value);
        else if (key == "mem-per-frame")      memPerFrame      = std::stoi(value);
        else if (key == "min-mem-per-proc")   minMemPerProc    = std::stoi(value);
        else if (key == "max-mem-per-proc")   maxMemPerProc    = std::stoi(value);
    }

    loaded = true;
    return true;
}

std::vector<std::string> Config::dump() const {
    std::vector<std::string> out;
    out.push_back("--- Configuration ---");
    out.push_back("  num-cpu:            " + std::to_string(numCpu));
    out.push_back("  scheduler:          " + scheduler);
    out.push_back("  quantum-cycles:     " + std::to_string(quantumCycles));
    out.push_back("  batch-process-freq: " + std::to_string(batchProcessFreq));
    out.push_back("  min-ins:            " + std::to_string(minIns));
    out.push_back("  max-ins:            " + std::to_string(maxIns));
    out.push_back("  delays-per-exec:    " + std::to_string(delaysPerExec));
    out.push_back("  max-overall-mem:    " + std::to_string(maxOverallMem));
    out.push_back("  mem-per-frame:      " + std::to_string(memPerFrame));
    out.push_back("  min-mem-per-proc:   " + std::to_string(minMemPerProc));
    out.push_back("  max-mem-per-proc:   " + std::to_string(maxMemPerProc));
    out.push_back("---------------------");
    return out;
}
