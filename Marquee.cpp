#include "Marquee.h"
#include "ConsoleUI.h"
#include "AsciiFont.h"

static const int MARQUEE_GAP = 6;

static int widestRow(const std::vector<std::string>& rows) {
    int w = 0;
    for (const auto& r : rows)
        if (static_cast<int>(r.size()) > w) w = static_cast<int>(r.size());
    return w;
}

Marquee::Marquee()
    : m_text("Hello World in CSOPESY!")
    , m_speed(60)
    , m_position(0)
    , m_frame(0)
    , m_copyWidth(1)
    , m_period(1)
    , m_running(false)
    , m_lastUpdate(std::chrono::steady_clock::now())
{
    rebuildArt();
}

void Marquee::rebuildArt() {
    m_artRows = AsciiFont::renderString(m_text);
    m_copyWidth = widestRow(m_artRows);
    if (m_copyWidth < 1) m_copyWidth = 1;
    m_period = m_copyWidth + MARQUEE_GAP;

    m_position = ConsoleUI::getConsoleWidth() + 1;
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

    m_position -= 1;

    if (m_position <= -m_period) {
        m_position += m_period;
    }

    ++m_frame;
    ConsoleUI::drawMarqueeArt(m_artRows, m_position, m_frame,
                              m_copyWidth, MARQUEE_GAP);
    return true;
}