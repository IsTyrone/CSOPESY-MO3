#pragma once
#include <string>
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

private:
    std::string m_text;
    int m_speed;       
    int m_position;    
    int m_direction;   
    bool m_running;

    std::chrono::steady_clock::time_point m_lastUpdate;
};
