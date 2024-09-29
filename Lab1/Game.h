#pragma once
#include "window.h"
#include "vector"
#include <cmath>

typedef int OutCode;

const int INSIDE = 0b0000;
const int LEFT   = 0b0001;
const int RIGHT  = 0b0010;
const int BOTTOM = 0b0100;
const int TOP    = 0b1000;

class Game{
public:
    Game();
    ~Game();

    void HandleInput();
    void Update();
    void Render();
    Window* GetWindow();
    void RestartClock();

private:
    bool Clip(sf::Vector2f& l_point_1, sf::Vector2f& l_point_2);
    OutCode ComputeOutCode(const sf::Vector2f& l_point);
    sf::Vector2f ConvertCoordinates(sf::Vector2i& l_point);
    float GetDistance(sf::Vector2f& l_point_1, sf::Vector2f& l_point_2);

    bool m_draw_stipple;
    int m_line_count;
    Window m_window;
    sf::Clock m_clock;
    sf::Time m_elapsed_time_fixed;
    sf::Vector2f m_rect_point_1;
    sf::Vector2f m_rect_point_2;
    std::vector<std::pair<sf::Vector2f, sf::Vector2f>> m_lines;
    std::vector<std::pair<sf::Vector2f, sf::Vector2f>> m_lines_in_rect;
    std::vector<bool> m_line_approved;
    std::vector<float> m_line_lengths;
    std::vector<std::pair<float, float>> m_stipple_line_lengths;

    int m_button_count;
    std::vector<std::pair<sf::Vector2f, sf::Vector2f>> m_buttons;
    std::pair<sf::Vector2f, sf::Vector2f> m_loop_points;
    std::vector<sf::Vector2f> m_loop_triangle;
    std::pair<sf::Vector2f, sf::Vector2f> m_button_quarter;
    std::pair<sf::Vector2f, sf::Vector2f> m_button_rect;
    std::pair<sf::Vector2f, sf::Vector2f> m_button_line;
    std::pair<sf::Vector2f, sf::Vector2f> m_button_stippled_line;
    std::vector<bool> m_is_button_pressed;
};