#include "Game.h"

Game::Game() : m_window("Lab3", sf::Vector2u(800, 600)), m_GUI(&m_sharedContext, 0.5f, 1.0f, 0.15f, 0.045f),
               m_camera(&m_sharedContext, 0.05f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 3.0f)
{
    m_sharedContext.graphics   = &m_graphics;
    m_sharedContext.window     = &m_window;
    m_sharedContext.shader     = m_graphics.m_shader;
    m_sharedContext.textShader = m_graphics.m_textShader;

    auto changeProjection = std::bind([this]()
                                      { m_flag = !m_flag; });

    auto changeRotate = std::bind([this]()
                                  { m_flagRotate = !m_flagRotate; m_rotateAccumulator = 0.0f; });

    auto changeRotateDirection = std::bind([this]()
                                           { m_rotateDirection = -m_rotateDirection; });

    auto getTime = std::bind([this]()
                             { return m_elapsedFixed.asSeconds(); });

    m_GUI.MakeSlider("Turn speed", &m_turnSpeed, 0, 10);
    m_GUI.MakeButton("Projection switch", changeProjection);
    m_GUI.MakeSlider("Scale", &m_scale, 0, 6);
    // m_GUI.MakeSlider("Element gap", &(m_GUI.m_elementGap), 0, 0.11);
    // m_GUI.MakeSlider("Element height", &(m_GUI.m_elementHeight), 0.15, 0.30);
    // m_GUI.MakeSlider("Left border", &(m_GUI.m_leftBorder), -1, 0.85);
    m_GUI.MakeHUDElement("Time", getTime);
    m_GUI.MakeButton("Rotate switch", changeRotate);
    m_GUI.MakeButton("Rotate direction switch", changeRotateDirection);
}

Game::~Game() {}

void Game::Update()
{
    m_window.Update();

    MatrixFloat modelMatrix;
    MatrixFloat translationMatrix;
    MatrixFloat translationMatrix2;
    MatrixFloat rotationMatrix;
    MatrixFloat scaleModelMatrix;
    MatrixFloat projectionMatrix;
    MatrixFloat m_viewMatrix = m_camera.getViewMatrix();

    scaleModelMatrix.ScaleXYZ(m_scale);

    if (m_flagRotate)
    {
        GLfloat cameraDistance   = 10.0f;
        sf::Vector3f targetPoint = m_camera.getTargetPoint(cameraDistance);

        translationMatrix.Move(targetPoint.x, targetPoint.y, targetPoint.z);

        Normalize(targetPoint);

        GLfloat radius = 2.0f;
        translationMatrix2.Move(-targetPoint.x * radius, -targetPoint.y * radius, -targetPoint.z * radius);
    }

    rotationMatrix.Rotate(m_rotateAccumulator, 0, 0);

    modelMatrix = translationMatrix * rotationMatrix * translationMatrix2 * scaleModelMatrix;

    if (m_flag)
    {
        projectionMatrix.OrthographicProjection((float)m_window.GetWindowSize().x / (float)m_window.GetWindowSize().y,
                                                1.0f, -1.0f, 1.0f, -1.0f, 0.1f, 100.0f);
    }
    else
    {
        projectionMatrix.PerspectiveProjection(30, (float)m_window.GetWindowSize().x / (float)m_window.GetWindowSize().y,
                                               0.1f, 100.0f);
    }

    m_transformMatrix = projectionMatrix * m_viewMatrix * modelMatrix;

    m_camera.Update(m_elapsed.asMilliseconds());
    m_GUI.Update(m_elapsed.asMilliseconds());
}

void Game::Render()
{
    m_window.BeginDraw();

    m_graphics.m_shader->SetFloat("alpha", 1.0f); //* all objects are 100% opaque by default
    m_graphics.m_shader->SetFloatMatrix("transformMatrix", m_transformMatrix.GetArray());
    m_graphics.DrawCube();

    m_graphics.m_textShader->SetFloat("alpha", 1.0f);
    m_GUI.Render();

    m_window.EndDraw();
}

Window* Game::GetWindow()
{
    return &m_window;
}

void Game::HandleInput()
{
    m_camera.HandleCameraInput();

    m_GUI.HandleInput();
}

void Game::RestartClock()
{
    m_elapsed = m_clock.restart();

    m_elapsedFixed += m_elapsed;

    m_rotateAccumulator += m_rotateDirection * m_elapsed.asSeconds() * m_turnSpeed;
}