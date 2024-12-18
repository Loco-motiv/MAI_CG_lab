#pragma once

#include "Camera.h"
#include "GUI.h"
#include "Matrix.h"

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

    sf::Clock m_clock;
    sf::Time m_elapsed;
    sf::Time m_elapsedFixed;

    GLboolean m_flag       = false;
    GLboolean m_flagRotate = false;

    GLdouble m_turnSpeed        = 1.0f;
    GLfloat m_rotateDirection   = 1.0f;
    GLfloat m_rotateAccumulator = 0.0f;
    GLdouble m_scale            = 0.8f;

    MatrixFloat m_transformMatrix;
};