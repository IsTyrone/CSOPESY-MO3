#pragma once
#include <string>
#include <vector>
#include <chrono>

class Marquee {
public:
    Marquee();

    void start();
    void stop();
    bool isRunning() const;

    void setText(const std::string& text);
    std::string getText() const;
    void setSpeed(int ms);
    int getSpeed() const;

    bool update();

    // Exposed so ConsoleUI can tile the art across the console width.
    int copyWidth() const { return m_copyWidth; }
    int period()    const { return m_period; }

private:
    std::string              m_text;
    std::vector<std::string> m_artRows;   // ONE copy of the text
    int m_speed;
    int m_position;                       // in (-period, 0]
    int m_frame;
    int m_copyWidth;                      // width of one copy
    int m_period;                         // copyWidth + gap
    bool m_running;

    std::chrono::steady_clock::time_point m_lastUpdate;

    void rebuildArt();
};