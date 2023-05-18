#pragma once
#include <SDL2/SDL.h>
#include <Engine/core/core.h>

namespace Engine::Draw
{
    void draw_polygon( Engine::Core::Polygon * polygon, Engine::Core::Camera * camera, SDL_Renderer * renderer ); 

    void draw_text(std::string text, int x, int y, int size, Engine::Core::Color color, SDL_Window *window, SDL_Renderer *renderer);

}