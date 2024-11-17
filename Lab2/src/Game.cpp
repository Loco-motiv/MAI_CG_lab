#include "Game.h"

Game::Game() : m_window("Lab2", sf::Vector2u(800, 600)), m_GUI(&m_sharedContext, 0.5f, 1.0f, 0.15f, 0.04f)
{
    m_sharedContext.graphics = &m_graphics;
    m_sharedContext.window   = &m_window;
    m_sharedContext.shader   = m_graphics.m_shader;

    auto temp = std::bind([this]()
                          { m_flag = !m_flag; });

    m_GUI.MakeSlider("Turn speed", &m_turnSpeed, 0, 10);
    m_GUI.MakeButton("Projection", temp);
    m_GUI.MakeSlider("Scale", &m_scale, 0, 6);
    m_GUI.MakeSlider("Element gap", &(m_GUI.m_elementGap), 0, 0.11);
    m_GUI.MakeSlider("Left border", &(m_GUI.m_leftBorder), -1, 0.85);

    m_viewMatrix.Move(0.0f, 0.0f, -3.0f);
}

Game::~Game() {}

void Game::Update()
{
    m_window.Update();

    MatrixFloat modelMatrix;
    MatrixFloat scaleModelMatrix;
    MatrixFloat projectionMatrix;

    scaleModelMatrix.ScaleXYZ(m_scale);

    modelMatrix.Rotate((float)m_elapsedFixed.asSeconds() * m_turnSpeed, (float)m_elapsedFixed.asSeconds() * m_turnSpeed,
                       (float)m_elapsedFixed.asSeconds() * m_turnSpeed);
    modelMatrix = scaleModelMatrix * modelMatrix;

    if (m_flag)
    {
        projectionMatrix.OrthographicProjection((float)m_window.GetWindowSize().x / (float)m_window.GetWindowSize().y,
                                                1.0f, 1.0f, 0.1f, 100.0f);
    }
    else
    {
        projectionMatrix.PerspectiveProjection(30, (float)m_window.GetWindowSize().x / (float)m_window.GetWindowSize().y,
                                               0.1f, 100.0f);
    }

    m_transformMatrix = modelMatrix * m_viewMatrix * projectionMatrix;

    m_GUI.Update(m_elapsed.asMilliseconds());
}

void Game::Render()
{
    m_window.BeginDraw();

    m_sharedContext.shader->SetFloat("alpha", 1.0f); //* all objects are 100% opaque by default
    m_graphics.m_shader->SetFloatMatrix("transformMatrix", m_transformMatrix.GetArray());
    m_graphics.DrawCube();

    m_GUI.Render();

    m_window.EndDraw();
}

Window* Game::GetWindow()
{
    return &m_window;
}

void Game::HandleInput()
{
    m_GUI.HandleInput();
}

void Game::RestartClock()
{
    m_elapsed = m_clock.restart();

    m_elapsedFixed += m_elapsed;
}