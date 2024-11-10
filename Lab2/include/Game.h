#pragma once

#include "GUI.h"
#include "Matrix.h"

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
    SharedContext m_sharedContext;

    Window m_window;
    Graphics m_graphics;
    GUI m_GUI;

    sf::Clock m_clock;
    sf::Time m_elapsed;
    sf::Time m_elapsedFixed;

    GLboolean m_flag = false;
    GLdouble m_turnSpeed = 1;
    GLdouble m_scale = 0.8;

    MatrixFloat m_viewMatrix;
    MatrixFloat m_transformMatrix;
};