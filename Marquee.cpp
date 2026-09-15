#include "Marquee.h"
#include "ConsoleUI.h"

Marquee::Marquee(): m_text("Hello World in CSOPESY!")
    , m_speed(100)
    , m_position(2)
    , m_direction(1)
    , m_frame(0)
    , m_running(false)
    , m_lastUpdate(std::chrono::steady_clock::now())
{
}

void Marquee::start() {
    if (m_running) 
        return;
    m_running = true;
    m_position = 2;
    m_direction = 1;
    m_lastUpdate = std::chrono::steady_clock::now();
}

void Marquee::stop() {
    if (!m_running) 
        return;
    m_running = false;
    ConsoleUI::clearMarqueeRow();
}

bool Marquee::isRunning() const { return m_running; }

void Marquee::setText(const std::string& t){
    m_text = t; m_position = 2; m_direction = 1;
}
std::string Marquee::getText() const{ 
    return m_text; 
}
void Marquee::setSpeed(int ms) { 
    if (ms > 0) m_speed = ms; 
}
int Marquee::getSpeed() const { 
    return m_speed; 
}

bool Marquee::update() {
    if (!m_running || m_text.empty()) 
        return false;

    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_lastUpdate).count();

    if (elapsed < m_speed) 
        return false;

    m_lastUpdate = now;

    int width = ConsoleUI::getConsoleWidth();
    int textLen = static_cast<int>(m_text.size());

    m_position += m_direction;

    if (m_position + textLen >= width - 1) {
        m_position  = width - textLen - 1;
        m_direction = -1;
    }

    if (m_position <= 1) {
        m_position  = 1;
        m_direction = 1;
    }

    ++m_frame;
    ConsoleUI::drawMarqueeRow(m_text, m_position, m_frame);
    return true;
}
