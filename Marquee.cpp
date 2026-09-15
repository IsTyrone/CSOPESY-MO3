#include "Marquee.h"
#include "ConsoleUI.h"
#include "AsciiFont.h"

Marquee::Marquee()
    : m_text("Hello World in CSOPESY!")
    , m_speed(100)
    , m_position(0)
    , m_direction(-1)
    , m_frame(0)
    , m_running(false)
    , m_lastUpdate(std::chrono::steady_clock::now())
{
    rebuildArt();
}

void Marquee::rebuildArt() {
    m_artRows = AsciiFont::renderString(m_text);
    m_position  = ConsoleUI::getConsoleWidth();
    m_direction = -1;
}

void Marquee::start() {
    if (m_running) return;
    m_running = true;
    rebuildArt();
    m_lastUpdate = std::chrono::steady_clock::now();
}

void Marquee::stop() {
    if (!m_running) return;
    m_running = false;
    ConsoleUI::clearMarqueeArea();
}

bool Marquee::isRunning() const { return m_running; }

void Marquee::setText(const std::string& t) {
    m_text = t;
    rebuildArt();
}

std::string Marquee::getText() const { return m_text; }

void Marquee::setSpeed(int ms) { if (ms > 0) m_speed = ms; }
int  Marquee::getSpeed() const { return m_speed; }

bool Marquee::update() {
    if (!m_running || m_text.empty() || m_artRows.empty())
        return false;

    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                       now - m_lastUpdate).count();
    if (elapsed < m_speed) return false;
    m_lastUpdate = now;

    int width = ConsoleUI::getConsoleWidth();

    int artWidth = 0;
    for (const auto& r : m_artRows)
        if (static_cast<int>(r.size()) > artWidth)
            artWidth = static_cast<int>(r.size());

    m_position += m_direction;
    if (m_position + artWidth < 1) {
        m_position = width;
    }

    ++m_frame;
    ConsoleUI::drawMarqueeArt(m_artRows, m_position, m_frame);
    return true;
}