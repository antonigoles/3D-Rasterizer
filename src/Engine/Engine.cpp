#include <stdio.h> /* printf and fprintf */
#include <SDL2/SDL.h> /* macOS- and GNU/Linux-specific */


/* Sets constants */
#define WIDTH 1280
#define HEIGHT 720

namespace Engine
{
    SDL_Window *initialize_window() 
    {
        /* Initialises data */
        SDL_Window *window = NULL;
        SDL_Surface *winSurface = NULL;

        /*
        * Initialises the SDL video subsystem (as well as the events subsystem).
        * Returns 0 on success or a negative error code on failure using SDL_GetError().
        */
        if (SDL_Init( SDL_INIT_EVERYTHING ) != 0) {
            fprintf(stderr, "SDL failed to initialise: %s\n", SDL_GetError());
            return NULL;
        }

        /* Creates a SDL window */
        window = SDL_CreateWindow(
            "Engine", /* Title of the SDL window */
            SDL_WINDOWPOS_UNDEFINED, /* Position x of the window */
            SDL_WINDOWPOS_UNDEFINED, /* Position y of the window */
            WIDTH, /* Width of the window in pixels */
            HEIGHT, /* Height of the window in pixels */
            SDL_WINDOW_SHOWN 
        ); 

        /* Checks if window has been created; if not, exits program */
        if (window == NULL) {
            fprintf(stderr, "SDL window failed to initialise: %s\n", SDL_GetError());
            return NULL;
        }

        winSurface = SDL_GetWindowSurface( window );
        return window;
    }

    void handle_window_events(SDL_Window *window, bool &running)
    {	
        SDL_Event ev; 
        while ( SDL_PollEvent( &ev ) != 0 ) 
        {
            switch (ev.type) 
            {
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }	  
    }

    void handle_engine_loop(SDL_Window *window, bool &running ) 
    {
        while ( running ) 
        {
            handle_window_events(window, running);
        }
    }

}

