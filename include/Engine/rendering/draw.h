#pragma once
#include <SDL2/SDL.h>
#include <Engine/core/core.h>

namespace Engine::Draw
{
    void draw_polygon( Engine::Core::Polygon * polygon, Engine::Core::Camera * camera, SDL_Renderer * renderer ); 
}