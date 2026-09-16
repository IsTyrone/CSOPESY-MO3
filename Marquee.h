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

    int copyWidth() const { return m_copyWidth; }
    int period()    const { return m_period; }

private:
    std::string              m_text;
    std::vector<std::string> m_artRows;
    int m_speed;
    int m_position;
    int m_frame;
    int m_copyWidth;
    int m_period;
    bool m_running;

    std::chrono::steady_clock::time_point m_lastUpdate;

    void rebuildArt();
};