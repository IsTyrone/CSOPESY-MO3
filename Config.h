#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <vector>
#include <unordered_map>

struct Config {
    int         numCpu          = 4;
    std::string scheduler       = "rr";
    int         quantumCycles   = 5;
    int         batchProcessFreq= 1;
    int         minIns          = 1000;
    int         maxIns          = 2000;
    int         delaysPerExec   = 0;
    int         maxOverallMem   = 1024;
    int         memPerFrame     = 64;
    int         minMemPerProc   = 64;
    int         maxMemPerProc   = 256;

    bool loaded = false;

    // Load from file.  Returns true on success.
    bool loadFromFile(const std::string& path = "config.txt");

    // Pretty-print for verification
    std::vector<std::string> dump() const;
};

#endif // CONFIG_H
