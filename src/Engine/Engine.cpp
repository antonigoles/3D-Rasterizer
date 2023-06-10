#include <stdio.h> /* printf and fprintf */
#include <SDL2/SDL.h> /* macOS- and GNU/Linux-specific */
#include <SDL2/SDL_ttf.h>
#include <Engine/Events.h>
#include <Engine/core/core.h>
#include <Engine/Debug.h>
#include <Engine/rendering/render.h>
#include <Engine/rendering/draw.h>
#include <Engine/Tests.h>

/* Sets constants */
#define WIDTH 1440
#define HEIGHT 960

namespace Engine
{

    SDL_Renderer *renderer;

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
            Engine::Debug::errorrich("SDL failed to initialise: " + (std::string)SDL_GetError());
            return NULL;
        }

        if ( TTF_Init() < 0 ) {
            Engine::Debug::errorrich("Error initializing SDL_ttf: " + (std::string)TTF_GetError());
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

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
        if ( !renderer ) {
            Engine::Debug::errorrich("Error creating renderer: " + (std::string)SDL_GetError()); 
            return NULL;
        }

        return window;
    }

    Engine::Core::Scene * current_scene;

    void switch_scene( Engine::Core::Scene * new_scene ) 
    {
        // TO IMPLEMENT
        current_scene = new_scene;

    }

    void draw_scene(SDL_Window *window) 
    {
        Engine::Render::draw_scene(current_scene, window, renderer);
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

        Engine::Events::EngineEvent * eev = Engine::Events::poll_event();
        while ( eev ) 
        {
            switch (ev.type) 
            {
                case ENGINE_DEFAULT_EVENT:
                    Engine::Debug::logrich("An event has been called");
                    break;
            }
        }	  
    }

    void handle_engine_loop(SDL_Window *window, bool &running ) 
    {
        while ( running ) 
        {
            handle_window_events(window, running);
            draw_scene(window);

            Engine::Render::draw_debug(window, renderer);

            Engine::Tests::run_each_frame_tests( Engine::Render::frame_render_time );

            SDL_RenderPresent( renderer );
        }
    }
}

