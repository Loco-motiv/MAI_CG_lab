#pragma once

#include "Camera.h"
#include "GUI.h"
#include "Matrix.h"
#include "SceneManager.h"

class Game
{
public:
    Game();
    ~Game();

    void HandleInput();
    void Update();
    void Render();
    Window* GetWindow();
    void RestartClock();

private:
    SharedContext m_sharedContext;

    Window m_window;
    Graphics m_graphics;
    GUI m_GUI;
    Camera m_camera;
    SceneManager m_sceneManager;

    sf::Clock m_clock;
    sf::Time m_elapsed;
    sf::Time m_elapsedFixed;

    // GLboolean m_flag       = false;
    GLboolean m_flagRotate = false;
    GLboolean m_flagFollow = true;

    GLdouble m_turnSpeed        = 1.0f;
    GLfloat m_rotateDirection   = 1.0f;
    GLfloat m_rotateAccumulator = 0.0f;
    GLdouble m_radius           = 1.0f;
    // GLdouble m_scale            = 0.8f;

    // sf::Vector3<GLdouble> m_lightColor{ 1.0f, 1.0f, 1.0f };

    sf::Vector3f m_targetPoint{ 0.0f, 0.0f, 0.0f };

    Cube* m_cube;

    // MatrixFloat m_transformMatrix;
    // MatrixFloat m_transformMatrixLight;
    // MatrixFloat m_modelMatrix;
};