#include <Engine/core/core.h>
#include <Engine/Debug.h>
#include <chrono>
#include <SDL2/SDL.h>
#include <Engine/rendering/draw.h>
#include <vector>

namespace Engine::Render
{

    void draw_polygon(Engine::Core::Polygon polygon, Engine::Core::Vector3 objectPosition) 
    {

    }

    void draw_engine_object(Engine::Core::EngineObject * engineObject)
    {
        // for ( auto polygon : engineObject->mesh.polygons ) {
        //     draw_polygon(polygon, engineObject->position);
        // }
    }

    double frame_render_time = 0;
    void draw_scene(Engine::Core::Scene * current_scene, SDL_Window *window, SDL_Renderer * renderer) 
    {
        // start performance metrics
        auto start = std::chrono::steady_clock::now();
        // clear screen 
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
	    SDL_RenderClear( renderer );


        for ( auto engineObject : current_scene->engine_objects ) {
            draw_engine_object(engineObject);
        }    

        // end performance metrics
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        double frame_time = elapsed_seconds.count();
        SDL_Delay( (Uint32)std::max(8-frame_time,(double)0) );
        frame_render_time = frame_time + std::max(2-frame_time*1000,(double)0)/1000;
    }

    void draw_debug(SDL_Window *window, SDL_Renderer *renderer)
    {
        int DEBUG_SIZE = 12;
        int LEFT_OFFSET = 5;

        std::vector<std::pair<std::string, Engine::Core::Color>> lines{
            { "Debug info:", Engine::Core::Color(255,255,255) },
            { std::to_string(1/frame_render_time) + " FPS", Engine::Core::Color(120,120,120) }
        };

        for ( int i = 0; i<lines.size(); i++ ) {
            Engine::Draw::draw_text(
                lines[i].first, 
                LEFT_OFFSET, 
                5 + i * (DEBUG_SIZE * 1.5), 
                DEBUG_SIZE, 
                lines[i].second, 
                window, renderer
            );
        }
        
    }
}