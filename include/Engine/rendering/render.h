#pragma once
#include <SDL2/SDL.h>
#include <Engine/core/core.h>

namespace Engine::Render
{
    void draw_scene(Engine::Core::Scene * current_scene, SDL_Window *window, SDL_Renderer * renderer );
    void draw_debug(SDL_Window *window, SDL_Renderer *renderer);
}