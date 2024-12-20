#include "Game.h"

Game::Game() : m_window("Lab4", sf::Vector2u(800, 600)), m_GUI(&m_sharedContext, 0.5f, 1.0f, 0.15f, 0.045f),
               m_camera(&m_sharedContext, 30.0f, 0.05f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 3.0f),
               m_sceneManager(&m_sharedContext)
{
    m_sharedContext.graphics   = &m_graphics;
    m_sharedContext.camera     = &m_camera;
    m_sharedContext.window     = &m_window;
    m_sharedContext.shader     = m_graphics.m_shader;
    m_sharedContext.textShader = m_graphics.m_textShader;
    m_sharedContext.GUIShader  = m_graphics.m_GUIShader;
    // auto getTime = std::bind([this]()
    //                          { return m_elapsedFixed.asSeconds(); });

    m_cube = m_sceneManager.MakeCube({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.8f, ObjectMaterial::cyanPlastic, 1.0f);
    m_sceneManager.MakeLightCube({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, 0.2f, { 1.0f, 1.0f, 1.0f });

    m_GUI.MakeSlider("Turn speed", &m_turnSpeed, 0, 10);
    m_GUI.MakeButton("Projection switch", std::bind([this]()
                                                    { m_sceneManager.m_flagProjection = !m_sceneManager.m_flagProjection; }));
    // m_GUI.MakeSlider("Scale", &m_scale, 0, 6);
    // m_GUI.MakeSlider("Element gap", &(m_GUI.m_elementGap), 0, 0.11);
    // m_GUI.MakeSlider("Element height", &(m_GUI.m_elementHeight), 0.15, 0.30);
    // m_GUI.MakeSlider("Left border", &(m_GUI.m_leftBorder), -1, 0.85);
    // m_GUI.MakeHUDElement("Time", getTime);
    m_GUI.MakeButton("Rotate switch", std::bind([this]()
                                                { m_flagRotate = !m_flagRotate; m_rotateAccumulator = 0.0f; }));
    m_GUI.MakeButton("Rotate direction switch", std::bind([this]()
                                                          { m_rotateDirection = -m_rotateDirection; }));
    m_GUI.MakeSlider("Light red value", &m_sceneManager.m_lightSources[0]->m_lightColor.x, 0, 1);
    m_GUI.MakeSlider("Light green value", &m_sceneManager.m_lightSources[0]->m_lightColor.y, 0, 1);
    m_GUI.MakeSlider("Light blue value", &m_sceneManager.m_lightSources[0]->m_lightColor.z, 0, 1);
    m_GUI.MakeButton("Stop following", std::bind([this]()
                                                 { m_flagFollow = !m_flagFollow; }));
    m_GUI.MakeSlider("Radius", &m_radius, 0, 10);

    m_GUI.MakeSlider("Specular red", &m_cube->m_materialSpecular.x, 0, 1);
    m_GUI.MakeSlider("Specular green", &m_cube->m_materialSpecular.y, 0, 1);
    m_GUI.MakeSlider("Specular blue", &m_cube->m_materialSpecular.z, 0, 1);
    m_GUI.MakeSlider("Shininess", &m_cube->m_materialShininess, 0, 256);
}

Game::~Game() {}

void Game::Update()
{
    m_window.Update();

    MatrixFloat modelMatrix;
    MatrixFloat translationMatrix;
    MatrixFloat translationMatrix2;
    MatrixFloat rotationMatrix;

    if (m_flagRotate)
    {
        GLfloat cameraDistance = 10.0f;
        if (m_flagFollow)
        {
            m_targetPoint = m_camera.getTargetPoint(cameraDistance);
        }

        translationMatrix.Move(m_targetPoint.x, m_targetPoint.y, m_targetPoint.z);

        translationMatrix2.Move(m_radius, m_radius, 0);
    }

    rotationMatrix.Rotate(m_rotateAccumulator, 0, 0);

    rotationMatrix = rotationMatrix * translationMatrix2;

    m_cube->m_translateMatrix = translationMatrix;
    m_cube->m_rotateMatrix    = rotationMatrix;

    m_sceneManager.Update();

    m_camera.Update(m_elapsed.asMilliseconds());
    m_GUI.Update(m_elapsed.asMilliseconds());
}

void Game::Render()
{
    m_window.BeginDraw();

    m_sceneManager.Render();

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