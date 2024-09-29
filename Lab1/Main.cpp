#include "game.h"

int main()
{
    Game game; // Creating our game object.
    while (!game.GetWindow()->IsOver())
    {
        // Game loop.
        game.HandleInput();
        game.Update();
        game.Render();
        game.RestartClock();
    }
    return 0;
}