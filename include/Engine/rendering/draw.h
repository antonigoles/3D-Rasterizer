#pragma once
#include <SDL2/SDL.h>
#include <Engine/core/core.h>

namespace Engine::Draw
{
    void draw_simple_triangle( Engine::Core::Vector2 pts[3], Engine::Core::Color color, SDL_Renderer * renderer) ; 

    void draw_text(std::string text, int x, int y, int size, Engine::Core::Color color, SDL_Window *window, SDL_Renderer *renderer);

}