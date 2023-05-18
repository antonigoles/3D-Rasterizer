#include <Engine/core/core.h>
#include <Engine/Debug.h>
#include <chrono>
#include <SDL2/SDL.h>
#include <Engine/rendering/draw.h>
#include <vector>
#include <Engine/Engine.h>
#include <Engine/core/math.h>
#include <iostream>

#define v2 Engine::Core::Vector2
#define v3 Engine::Core::Vector2

namespace Engine::Render
{
    double frame_render_time = 0;
    int polygon_renders_last_frame = 0;


    void draw_polygon(Engine::Core::Polygon polygon, Engine::Core::Vector3 objectPosition) 
    {
        polygon_renders_last_frame++;
        
        float scale = 20.0f;
        float near_plane = 10.0f;

        polygon.print_polygon();
        std::cout << "\n";

        polygon.vertices[0] = polygon.vertices[0] - objectPosition;
        polygon.vertices[1] = polygon.vertices[1] - objectPosition;
        polygon.vertices[2] = polygon.vertices[2] - objectPosition;

        

        float 
            f1 = std::max( near_plane/(polygon.vertices[0].z ), 0.0000001f ),
            f2 = std::max( near_plane/(polygon.vertices[1].z ), 0.0000001f ),
            f3 = std::max( near_plane/(polygon.vertices[2].z ), 0.0000001f )
        ;

        v2 screen_pts[3] {
            v2(
                polygon.vertices[0].x * scale * f1,
                polygon.vertices[0].y * scale  * f1
            ),

            v2(
                polygon.vertices[1].x * scale * f2,
                polygon.vertices[1].y * scale * f2
            ),

            v2(
                polygon.vertices[2].x * scale * f3,
                polygon.vertices[2].y * scale * f3
            )
        };


        Engine::Draw::draw_simple_triangle(
            screen_pts, Engine::Core::Color(200, 200, 200), Engine::renderer 
        );

    }

    void draw_engine_object(Engine::Core::EngineObject * engineObject)
    {
        for ( auto polygon : engineObject->mesh.polygons ) {
            draw_polygon(polygon, engineObject->position);
        }
    }

    
    void draw_scene(Engine::Core::Scene * current_scene, SDL_Window *window, SDL_Renderer * renderer) 
    {
        // start performance metrics
        auto start = std::chrono::steady_clock::now();
        // clear screen 
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
	    SDL_RenderClear( renderer );
        polygon_renders_last_frame=0;


        for ( auto engineObject : current_scene->engine_objects ) {
            draw_engine_object(engineObject);
        }    

        // end performance metrics
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        double frame_time = elapsed_seconds.count();
        SDL_Delay( (Uint32)std::max(8-frame_time,(double)0) );
        frame_render_time = frame_time + std::max(1-frame_time*1000,(double)0)/1000;
    }

    void draw_debug(SDL_Window *window, SDL_Renderer *renderer)
    {
        int DEBUG_SIZE = 12;
        int LEFT_OFFSET = 5;

        std::vector<std::pair<std::string, Engine::Core::Color>> lines{
            { "Debug info:", Engine::Core::Color(255,255,255) },
            { std::to_string(1/frame_render_time) + " FPS", Engine::Core::Color(120,120,120) },
            { "frame_render_time: " + std::to_string(frame_render_time), Engine::Core::Color(120,120,120) },
            { "polygon_renders_last_frame: " + std::to_string(polygon_renders_last_frame), Engine::Core::Color(120,120,120) },
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