#pragma once
#include <string>
#include <vector>

namespace AsciiFont {

    constexpr int GLYPH_HEIGHT = 5;
    constexpr int GLYPH_WIDTH  = 5;

    // Returns 5 rows for a single character. Unknown -> blank glyph.
    std::vector<std::string> getGlyph(char c);

    // Renders a string into 5 rows of ASCII art (one row per font row).
    std::vector<std::string> renderString(const std::string& text);

} // namespace AsciiFont