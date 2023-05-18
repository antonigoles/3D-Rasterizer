#pragma once
#include <stdio.h> /* printf and fprintf */
#include <SDL2/SDL.h>
#include <Engine/core/core.h>

namespace Engine
{
    SDL_Window *initialize_window();

    void handle_window_events(SDL_Window *window, bool &running);

    void handle_engine_loop(SDL_Window *window, bool &running );

    void draw_scene(SDL_Window *window);

    void switch_scene(Engine::Core::Scene * new_scene);

    extern Engine::Core::Scene * current_scene;

    extern SDL_Renderer *renderer;
    
}