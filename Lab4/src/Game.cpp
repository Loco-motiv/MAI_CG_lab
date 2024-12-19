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
}

Game::~Game() {}

void Game::Update()
{
    m_window.Update();

    MatrixFloat modelMatrix;
    MatrixFloat translationMatrix;
    MatrixFloat translationMatrix2;
    MatrixFloat rotationMatrix;
    // MatrixFloat scaleModelMatrix;
    // MatrixFloat projectionMatrix;
    // MatrixFloat m_viewMatrix = m_camera.getViewMatrix();

    // scaleModelMatrix.ScaleXYZ(m_scale);

    //!

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

    //!

    // m_modelMatrix = translationMatrix * rotationMatrix * translationMatrix2 * scaleModelMatrix;

    // if (m_flag)
    // {
    //     projectionMatrix.OrthographicProjection((float)m_window.GetWindowSize().x / (float)m_window.GetWindowSize().y,
    //                                             1.0f, -1.0f, 1.0f, -1.0f, 0.1f, 100.0f);
    // }
    // else
    // {
    //     projectionMatrix.PerspectiveProjection(m_camera.getFOV(), (float)m_window.GetWindowSize().x / (float)m_window.GetWindowSize().y,
    //                                            0.1f, 100.0f);
    // }

    // m_transformMatrix = projectionMatrix * m_viewMatrix * m_modelMatrix;

    // modelMatrix      = MatrixFloat();
    // scaleModelMatrix = MatrixFloat();
    // modelMatrix.Move(1.0f, 1.0f, 1.0f);
    // scaleModelMatrix.ScaleXYZ(0.2f);

    // modelMatrix = modelMatrix * scaleModelMatrix;

    // m_transformMatrixLight = projectionMatrix * m_viewMatrix * modelMatrix;

    m_sceneManager.Update();

    m_camera.Update(m_elapsed.asMilliseconds());
    m_GUI.Update(m_elapsed.asMilliseconds());
}

void Game::Render()
{
    m_window.BeginDraw();

    m_sceneManager.Render();

    // m_graphics.m_shader->SetFloatVec3("light.ambient", m_lightColor.x * 0.1f, m_lightColor.y * 0.1f, m_lightColor.z * 0.1f);
    // m_graphics.m_shader->SetFloatVec3("light.diffuse", m_lightColor.x * 0.9f, m_lightColor.y * 0.9f, m_lightColor.z * 0.9f);
    // m_graphics.m_shader->SetFloatVec3("light.specular", 1.0f, 1.0f, 1.0f);
    // m_graphics.m_shader->SetFloatVec3("light.position", 1.0f, 1.0f, 1.0f);
    // m_graphics.m_shader->SetFloatVec3("material.ambient", 1.0f, 0.5f, 0.31f);
    // m_graphics.m_shader->SetFloatVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
    // m_graphics.m_shader->SetFloatVec3("material.specular", 0.5f, 0.5f, 0.5f);
    // m_graphics.m_shader->SetFloat("material.shininess", 32.0f);

    // m_graphics.m_shader->SetFloatVec3("viewPosition", m_camera.getPosition().x, m_camera.getPosition().y, m_camera.getPosition().z);
    // m_graphics.m_shader->SetFloatMatrix("modelMatrix", m_modelMatrix.GetArray());
    // m_graphics.m_shader->SetFloat("alpha", 1.0f); //* all objects are 100% opaque by default
    // m_graphics.m_shader->SetFloatMatrix("transformMatrix", m_transformMatrix.GetArray());
    // m_graphics.DrawCube();

    // m_graphics.m_lightSourceShader->SetFloatMatrix("transformMatrix", m_transformMatrixLight.GetArray());
    // m_graphics.m_lightSourceShader->SetFloatVec3("lightColor", m_lightColor.x, m_lightColor.y, m_lightColor.z);
    // m_graphics.DrawLightSourceCube();

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