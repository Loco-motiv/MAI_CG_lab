#pragma once

#include "Graphics.h"
#include "Window.h"

struct SharedContext
{
    SharedContext() : window(nullptr), graphics(nullptr), shader(nullptr) {}
    Window* window;
    Graphics* graphics;
    Shader* shader;
    Shader* textShader;
};