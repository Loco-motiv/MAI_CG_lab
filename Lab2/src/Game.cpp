#include "Game.h"

Game::Game(): m_window("Lab2", sf::Vector2u(800, 600))
{
    // std::srand(time(0));
}

Game::~Game() {} 

void Game::Update() 
{
    m_window.Update();
    // for (int i = 0; i < m_line_count; i++)
    // {
    //     std::pair<sf::Vector2f, sf::Vector2f> new_pair(m_lines[i].first, m_lines[i].second);
    //     //m_line_approved[i] = Clip(new_pair.first, new_pair.second);
    //     m_lines_in_rect[i] = new_pair;
    // }
}

void Game::Render()
{
    m_window.BeginDraw();

    m_window.DrawTriangle();

    m_window.EndDraw();
}

Window* Game::GetWindow() {
    return &m_window;
}

void Game::HandleInput()
{
    // if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (m_elapsed_time_fixed > sf::seconds(0.25)))
    // {
    //     sf::Vector2i mouse_coordinates_sfml = sf::Mouse::getPosition(*m_window.GetWindow());
    //     sf::Vector2f mouse_coordinates_opengl = ConvertCoordinates(mouse_coordinates_sfml);
    //     for (int i = 0; i < m_button_count; i++)
    //     {
    //         if ((mouse_coordinates_opengl.x > m_buttons[i].first.x) && (mouse_coordinates_opengl.x < m_buttons[i].second.x)
    //             && (mouse_coordinates_opengl.y < m_buttons[i].first.y) && (mouse_coordinates_opengl.y > m_buttons[i].second.y))
    //             {
    //                 if (i == 0)
    //                 {
    //                     for (int i = 0; i < m_line_count; i++)
    //                     {
    //                         m_lines[i].first = sf::Vector2f(2 * ((float)std::rand() / RAND_MAX) - 1, 1.8 * ((float)std::rand() / RAND_MAX) - 0.8);
    //                         m_lines[i].second = sf::Vector2f(2 * ((float)std::rand() / RAND_MAX) - 1, 1.8 * ((float)std::rand() / RAND_MAX) - 0.8);
    //                         m_line_lengths[i] = GetDistance(m_lines[i].first, m_lines[i].second);
    //                     }
    //                 }
    //                 else if (i == 1)
    //                 {
    //                     m_draw_stipple = !m_draw_stipple;
    //                 }
    //                 m_elapsed_time_fixed -= sf::seconds(0.25);
    //                 m_is_button_pressed[i] = true;
    //             }
    //     }
    // }
}

void Game::RestartClock() 
{
    m_elapsedFixed += m_clock.restart();
    if (m_elapsedFixed > sf::seconds(0.27)) 
    {
        m_elapsedFixed -= sf::seconds(0.01);
    }
}

// sf::Vector2f Game::ConvertCoordinates(sf::Vector2i& l_point)
// {
//     return sf::Vector2f(2.f * ((float)l_point.x / m_window.GetWindowSize().x) - 1.f,
//         1.f - (2.f * ((float)l_point.y / m_window.GetWindowSize().y)));
// }

// float Game::GetDistance(sf::Vector2f& l_point_1, sf::Vector2f& l_point_2)
// {
//     return std::sqrt(std::pow(l_point_1.x - l_point_2.x, 2) +
//             std::pow(l_point_1.y - l_point_2.y, 2));
// }