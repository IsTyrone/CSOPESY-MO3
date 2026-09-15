#include "AsciiFont.h"
#include <fstream>
#include <iostream>

namespace AsciiFont {

    static std::map<char, std::vector<std::string>> s_font;
    static int s_height = 0;

    static std::string stripEol(std::string s) {
        while (!s.empty() && (s.back() == '\r' || s.back() == '\n'))
            s.pop_back();
        return s;
    }

    bool loadFont(const std::string& path) {
        s_font.clear();
        s_height = 0;

        std::ifstream in(path);
        if (!in) {
            std::cerr << "[AsciiFont] Could not open font file: "
                      << path << "\n";
            return false;
        }

        // 1. Read the height
        std::string line;
        if (!std::getline(in, line)) return false;
        line = stripEol(line);
        try {
            s_height = std::stoi(line);
        } catch (...) {
            std::cerr << "[AsciiFont] First line must be an integer "
                         "(glyph height).\n";
            return false;
        }
        if (s_height <= 0) return false;

        // 2. Read each glyph: 1 header line + s_height art rows
        while (std::getline(in, line)) {
            line = stripEol(line);
            if (line.empty()) continue;

            char ch = line[0];

            std::vector<std::string> rows;
            rows.reserve(s_height);
            bool ok = true;
            for (int r = 0; r < s_height; ++r) {
                if (!std::getline(in, line)) { ok = false; break; }
                rows.push_back(stripEol(line));
            }
            if (!ok) break;

            s_font[ch] = std::move(rows);
        }

        std::cout << "[AsciiFont] Loaded " << s_font.size()
                  << " glyphs (" << s_height << " rows each) from "
                  << path << "\n";
        return true;
    }

    int glyphHeight() { return s_height; }

    std::vector<std::string> renderString(const std::string& text) {
        std::vector<std::string> result;
        if (s_height <= 0) return result;

        result.assign(s_height, "");

        const int FALLBACK_WIDTH = 5;

        for (char c : text) {
            auto it = s_font.find(c);
            if (it == s_font.end()) {
                for (int r = 0; r < s_height; ++r)
                    result[r] += std::string(FALLBACK_WIDTH, ' ');
                continue;
            }

            const auto& rows = it->second;
            for (int r = 0; r < s_height; ++r) {
                result[r] += rows[r];
                result[r] += ' ';   // 1-column gap between glyphs
            }
        }
        return result;
    }

} // namespace AsciiFont