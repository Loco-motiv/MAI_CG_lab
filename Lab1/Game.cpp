#include "Game.h"

Game::Game(): m_window("Lab1", sf::Vector2u(800, 600)), m_rect_point_1(-0.5f, 0.5f), m_rect_point_2(0.5f, -0.5f),
    m_line_count(5), m_line_approved(m_line_count), m_lines_in_rect(m_line_count), m_button_count(2),
    m_is_button_pressed(2, false), m_draw_stipple(false), m_stipple_line_lengths(m_line_count)
{
    std::srand(time(0));
    for (int i = 0; i < m_line_count; i++)
    {
        sf::Vector2f l_line_point_1(2 * ((float)std::rand() / RAND_MAX) - 1, 1.8 * ((float)std::rand() / RAND_MAX) - 0.8);
        sf::Vector2f l_line_point_2(2 * ((float)std::rand() / RAND_MAX) - 1, 1.8 * ((float)std::rand() / RAND_MAX) - 0.8);
        m_lines.push_back({l_line_point_1, l_line_point_2});
        m_line_lengths.push_back(GetDistance(l_line_point_1, l_line_point_2));
    }

    m_buttons.push_back({sf::Vector2f(-0.15, -0.8), sf::Vector2f(-0.05, -0.9)});
    m_buttons.push_back({sf::Vector2f(0.05, -0.8), sf::Vector2f(0.15, -0.9)});
    m_loop_points = {m_buttons[0].first + sf::Vector2f(0.015, -0.015), m_buttons[0].second + sf::Vector2f(-0.015, 0.015)};
    m_button_quarter = {m_buttons[0].first + sf::Vector2f(0.05, 0.), m_buttons[0].second + sf::Vector2f(0., 0.05)};

    m_loop_triangle.push_back(m_buttons[0].second + sf::Vector2f(-0.03, 0.05));
    m_loop_triangle.push_back(m_buttons[0].second + sf::Vector2f(-0.015, 0.08));
    m_loop_triangle.push_back(m_buttons[0].second + sf::Vector2f(0., 0.05));

    m_button_rect = {m_buttons[1].first + sf::Vector2f(0.015, -0.015), m_buttons[1].second + sf::Vector2f(-0.015, 0.015)};
    m_button_line = {m_buttons[1].first + sf::Vector2f(0.015, -0.05), m_buttons[1].second + sf::Vector2f(-0.015, 0.05)};
    m_button_stippled_line = {m_buttons[1].first + sf::Vector2f(0.005, -0.05), m_buttons[1].second + sf::Vector2f(-0.005, 0.05)};
}

Game::~Game() {} 

void Game::Update() 
{
    m_window.Update();

    for (int i = 0; i < m_line_count; i++)
    {
        std::pair<sf::Vector2f, sf::Vector2f> new_pair(m_lines[i].first, m_lines[i].second);
        m_line_approved[i] = Clip(new_pair.first, new_pair.second);
        m_lines_in_rect[i] = new_pair;
    }
}

void Game::Render()
{
    m_window.BeginDraw();
  
    for (int i = 0; i < m_line_count; i++)
    {
        if (m_line_approved[i])
        {
            m_stipple_line_lengths[i] = {GetDistance(m_lines[i].first, m_lines_in_rect[i].first),
                GetDistance(m_lines_in_rect[i].second, m_lines[i].second)};
            m_window.DrawLine(m_lines_in_rect[i].first, m_lines_in_rect[i].second, false, 1.f,
                (m_line_lengths[i] - m_stipple_line_lengths[i].first)/m_line_lengths[i], 0.f, m_stipple_line_lengths[i].first/m_line_lengths[i],
                m_stipple_line_lengths[i].second/m_line_lengths[i], 0.f, (m_line_lengths[i] - m_stipple_line_lengths[i].second)/m_line_lengths[i]);
        }
    }
    if (m_draw_stipple)
    {
        for (int i = 0; i < m_line_count; i++)
        {
            if (m_line_approved[i])
            {
                m_window.DrawLine(m_lines[i].first, m_lines_in_rect[i].first, true, 0.4f,
                    1.f, 0.f, 0.f,
                    (m_line_lengths[i] - m_stipple_line_lengths[i].first)/m_line_lengths[i], 0.f, m_stipple_line_lengths[i].first/m_line_lengths[i]);
                m_window.DrawLine(m_lines[i].second, m_lines_in_rect[i].second, true, 0.4f,
                    0.f, 0.f, 1.f,
                    m_stipple_line_lengths[i].second/m_line_lengths[i], 0.f, (m_line_lengths[i] - m_stipple_line_lengths[i].second)/m_line_lengths[i]);
            }
            else
            {
                m_window.DrawLine(m_lines[i].first, m_lines[i].second, true, 0.4f);
            }
        }
    }
    m_window.DrawRect(m_rect_point_1, m_rect_point_2);

    for (int i = 0; i < m_button_count; i++)
    {
        m_window.DrawFilledRect(m_buttons[i].first, m_buttons[i].second);
    }
    m_window.DrawRect(m_loop_points.first, m_loop_points.second, true);
    m_window.DrawFilledRect(m_button_quarter.first, m_button_quarter.second);
    m_window.DrawTriangle(m_loop_triangle[0], m_loop_triangle[1], m_loop_triangle[2]);

    m_window.DrawRect(m_button_rect.first, m_button_rect.second);
    m_window.DrawLine(m_button_line.first, m_button_line.second);
    m_window.DrawLine(m_button_stippled_line.first, m_button_line.first, true);
    m_window.DrawLine(m_button_line.second, m_button_stippled_line.second, true);
    
    for (int i = 0; i < m_button_count; i++)
    {
        if (m_is_button_pressed[i])
        {
            if (m_elapsed_time_fixed < sf::seconds(0.2))
            {
                m_window.DrawFilledRect(m_buttons[i].first, m_buttons[i].second, 0.5f, 0.f, 0.f, 0.f);
            }
            else 
            {
                m_is_button_pressed[i] = false;
            }
        }
    }

    m_window.EndDraw();
}

Window* Game::GetWindow() {
    return &m_window;
}

void Game::HandleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && ((m_rect_point_1.y + 0.001) < 1.f))
    {
        m_rect_point_1.y += 0.001;
        m_rect_point_2.y += 0.001;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && ((m_rect_point_2.y - 0.001) > -1.f))
    {
        m_rect_point_1.y -= 0.001;
        m_rect_point_2.y -= 0.001;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && ((m_rect_point_1.x - 0.001) > -1.f))
    {
        m_rect_point_1.x -= 0.001;
        m_rect_point_2.x -= 0.001;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && ((m_rect_point_2.x + 0.001) < 1.f))
    {
        m_rect_point_1.x += 0.001;
        m_rect_point_2.x += 0.001;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && ((m_rect_point_2.x + 0.001) < 1.f) &&
        ((m_rect_point_1.y + 0.001) < 1.f) && ((m_rect_point_2.y - 0.001) > -1.f) &&
        ((m_rect_point_1.x - 0.001) > -1.f))
    {
        m_rect_point_1.x -= 0.001;
        m_rect_point_2.x += 0.001;
        m_rect_point_1.y += 0.001;
        m_rect_point_2.y -= 0.001;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && ((abs(m_rect_point_1.x - m_rect_point_2.x) - 0.002) > 0.f) &&
        ((abs(m_rect_point_1.y - m_rect_point_2.y) - 0.002) > 0.f))
    {
        m_rect_point_1.x += 0.001;
        m_rect_point_2.x -= 0.001;
        m_rect_point_1.y -= 0.001;
        m_rect_point_2.y += 0.001;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && (m_elapsed_time_fixed > sf::seconds(0.25)))
    {
        m_elapsed_time_fixed -= sf::seconds(0.25);
        for (int i = 0; i < m_line_count; i++)
        {
            m_lines[i].first = sf::Vector2f(2 * ((float)std::rand() / RAND_MAX) - 1, 1.8 * ((float)std::rand() / RAND_MAX) - 0.8);
            m_lines[i].second = sf::Vector2f(2 * ((float)std::rand() / RAND_MAX) - 1, 1.8 * ((float)std::rand() / RAND_MAX) - 0.8);
        }
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (m_elapsed_time_fixed > sf::seconds(0.25)))
    {
        sf::Vector2i mouse_coordinates_sfml = sf::Mouse::getPosition(*m_window.GetWindow());
        sf::Vector2f mouse_coordinates_opengl = ConvertCoordinates(mouse_coordinates_sfml);
        for (int i = 0; i < m_button_count; i++)
        {
            if ((mouse_coordinates_opengl.x > m_buttons[i].first.x) && (mouse_coordinates_opengl.x < m_buttons[i].second.x)
                && (mouse_coordinates_opengl.y < m_buttons[i].first.y) && (mouse_coordinates_opengl.y > m_buttons[i].second.y))
                {
                    if (i == 0)
                    {
                        for (int i = 0; i < m_line_count; i++)
                        {
                            m_lines[i].first = sf::Vector2f(2 * ((float)std::rand() / RAND_MAX) - 1, 1.8 * ((float)std::rand() / RAND_MAX) - 0.8);
                            m_lines[i].second = sf::Vector2f(2 * ((float)std::rand() / RAND_MAX) - 1, 1.8 * ((float)std::rand() / RAND_MAX) - 0.8);
                        }
                    }
                    else if (i == 1)
                    {
                        m_draw_stipple = !m_draw_stipple;
                    }
                    m_elapsed_time_fixed -= sf::seconds(0.25);
                    m_is_button_pressed[i] = true;
                }
        }
    }
}

void Game::RestartClock() 
{
    m_elapsed_time_fixed += m_clock.restart();
    if (m_elapsed_time_fixed > sf::seconds(0.27)) 
    {
        m_elapsed_time_fixed -= sf::seconds(0.01);
    }
}

OutCode Game::ComputeOutCode(const sf::Vector2f& l_point)
{
	OutCode code = INSIDE;

	if (l_point.x < m_rect_point_1.x)
		code |= LEFT;
	else if (l_point.x > m_rect_point_2.x)
		code |= RIGHT;
	if (l_point.y < m_rect_point_2.y)
		code |= BOTTOM;
	else if (l_point.y > m_rect_point_1.y)
		code |= TOP;

	return code;
}

bool Game::Clip(sf::Vector2f& l_point_1, sf::Vector2f& l_point_2)
{
	OutCode outcode0 = ComputeOutCode(l_point_1);
	OutCode outcode1 = ComputeOutCode(l_point_2);
	bool accept = false;

	while (true) {
		if (!(outcode0 | outcode1)) {
			accept = true;
			break;
		} else if (outcode0 & outcode1) {
			break;
		} else {
            sf::Vector2f new_point;

			OutCode outcodeOut = outcode1 > outcode0 ? outcode1 : outcode0;

			if (outcodeOut & TOP) {   
				new_point.x = l_point_1.x + (l_point_2.x - l_point_1.x) * (m_rect_point_1.y - l_point_1.y) / (l_point_2.y - l_point_1.y);
				new_point.y = m_rect_point_1.y;
			} else if (outcodeOut & BOTTOM) { 
				new_point.x = l_point_1.x + (l_point_2.x - l_point_1.x) * (m_rect_point_2.y - l_point_1.y) / (l_point_2.y - l_point_1.y);
				new_point.y = m_rect_point_2.y;
			} else if (outcodeOut & RIGHT) {
				new_point.y = l_point_1.y + (l_point_2.y - l_point_1.y) * (m_rect_point_2.x - l_point_1.x) / (l_point_2.x - l_point_1.x);
				new_point.x = m_rect_point_2.x;
			} else if (outcodeOut & LEFT) {
				new_point.y = l_point_1.y + (l_point_2.y - l_point_1.y) * (m_rect_point_1.x - l_point_1.x) / (l_point_2.x - l_point_1.x);
				new_point.x = m_rect_point_1.x;
			}

			if (outcodeOut == outcode0) {
				l_point_1.x = new_point.x;
				l_point_1.y = new_point.y;
				outcode0 = ComputeOutCode(l_point_1);
			} else {
				l_point_2.x = new_point.x;
				l_point_2.y = new_point.y;
				outcode1 = ComputeOutCode(l_point_2);
			}
		}
	}
	return accept;
}

sf::Vector2f Game::ConvertCoordinates(sf::Vector2i& l_point)
{
    return sf::Vector2f(2.f * ((float)l_point.x / m_window.GetWindowSize().x) - 1.f,
        1.f - (2.f * ((float)l_point.y / m_window.GetWindowSize().y)));
}

float Game::GetDistance(sf::Vector2f& l_point_1, sf::Vector2f& l_point_2)
{
    return std::sqrt(std::pow(l_point_1.x - l_point_2.x, 2) +
            std::pow(l_point_1.y - l_point_2.y, 2));
}