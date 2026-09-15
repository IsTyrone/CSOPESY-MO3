#pragma once
#include <string>
#include <vector>

// Hard-coded 5-row ASCII font.
// Uses only '#' and space. Every glyph is exactly 5 columns wide.
namespace AsciiFont {

    constexpr int GLYPH_HEIGHT = 5;
    constexpr int GLYPH_WIDTH  = 5;

    // Returns 5 rows for a single character. Unknown -> blank glyph.
    std::vector<std::string> getGlyph(char c);

    // Renders a string into 5 rows of ASCII art (one row per font row).
    std::vector<std::string> renderString(const std::string& text);

} // namespace AsciiFont