#pragma once
#include <stdio.h> /* printf and fprintf */
#include <SDL2/SDL.h>

namespace Engine
{
    SDL_Window *initialize_window();

    void handle_window_events(SDL_Window *window, bool &running);

    void handle_engine_loop(SDL_Window *window, bool &running );
    
}