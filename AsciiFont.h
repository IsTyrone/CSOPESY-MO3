#pragma once
#include <string>
#include <vector>
#include <map>

// Runtime-loaded ASCII font.
// The font is read from an external text file (default: "font.txt")
// so no glyph shapes are baked into the C++ source.
namespace AsciiFont {

    // Loads a font file into a map<char, vector<string>>.
    // Returns true on success, false if the file could not be opened.
    bool loadFont(const std::string& path);

    // Height (number of rows) of the loaded font. 0 if not loaded.
    int glyphHeight();

    // Renders a whole string into N rows of ASCII art (N = glyphHeight()).
    // Unknown characters are rendered as blank glyphs.
    std::vector<std::string> renderString(const std::string& text);

} // namespace AsciiFont