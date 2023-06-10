#include <Engine/core/core.h>
#include <Engine/Debug.h>
#include <chrono>
#include <SDL2/SDL.h>
#include <Engine/rendering/draw.h>
#include <vector>
#include <Engine/Engine.h>
#include <Engine/core/math.h>
#include <iostream>
#include <set>

#define v2 Engine::Core::Vector2
#define v3 Engine::Core::Vector2

namespace Engine::Render
{

    struct RenderQueueElement
    {
        float zIndex;
        std::vector<Engine::Core::Vector2> screen_pts;
        float brightness;
        
        bool operator==(const RenderQueueElement& a) const{
            return a.zIndex == zIndex;
        }

        bool operator>=(const RenderQueueElement& a) const{
            return  zIndex >= a.zIndex;
        }

        bool operator<=(const RenderQueueElement& a) const{
            return  zIndex <=  a.zIndex;
        }

        bool operator>(const RenderQueueElement& a) const{
            return  zIndex >  a.zIndex;
        }

        bool operator<(const RenderQueueElement& a) const{
            return  zIndex <  a.zIndex;
        }

    };

    float frame_render_time = 0;
    int polygon_renders_last_frame = 0;
    std::multiset<RenderQueueElement> render_queue;

    void draw_polygon(Engine::Core::Polygon polygon, Engine::Core::Vector3 objectPosition, Engine::Core::Vector3 objectRotation) 
    {
        polygon_renders_last_frame++;
        
        float scale = 8000.0f;
        float near_plane = 50.0f;

        // polygon.print_polygon();
        // std::cout << "\n";

        Engine::Math::v3_rot(&polygon.vertices[0], objectRotation.x, objectRotation.y, objectRotation.z, Engine::Core::Vector3(0.5f,0.5f,0.5f) );
        Engine::Math::v3_rot(&polygon.vertices[1], objectRotation.x, objectRotation.y, objectRotation.z, Engine::Core::Vector3(0.5f,0.5f,0.5f) );
        Engine::Math::v3_rot(&polygon.vertices[2], objectRotation.x, objectRotation.y, objectRotation.z, Engine::Core::Vector3(0.5f,0.5f,0.5f) );


        polygon.vertices[0] = polygon.vertices[0] - objectPosition;
        polygon.vertices[1] = polygon.vertices[1] - objectPosition;
        polygon.vertices[2] = polygon.vertices[2] - objectPosition;

        // polygon.print_polygon();
        // std::cout << "\n";

        int SCREEN_W = 0;
        int SCREEN_H = 0;
        int H_W = SCREEN_W/2; int H_H = SCREEN_H/2;
        SDL_GetRendererOutputSize(renderer, &SCREEN_W, &SCREEN_H);

        float 
            f1 = std::max( 1/(polygon.vertices[0].z+near_plane ), 0.000000000000000001f ),
            f2 = std::max( 1/(polygon.vertices[1].z+near_plane ), 0.000000000000000001f ),
            f3 = std::max( 1/(polygon.vertices[2].z+near_plane ), 0.000000000000000001f )
        ;

        std::vector<v2> screen_pts {
            v2(
                polygon.vertices[0].x * scale * f1,
                polygon.vertices[0].y * scale * f1
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

        Engine::Core::Vector3 polygon_normal = Engine::Math::polygon_normal(polygon);
        float polygon_br = std::min( 1 / Engine::Math::v3_angle(Engine::Core::Vector3(1,0,1), polygon_normal), 1.0f);
  
        RenderQueueElement rqe = { 
            (polygon.vertices[0].z + polygon.vertices[1].z + polygon.vertices[2].z) * 0.3333f, 
            screen_pts, 
            polygon_br 
        };

        render_queue.insert(rqe);

        // Engine::Draw::draw_simple_triangle(
        //     screen_pts, Engine::Core::Color(200 * polygon_br, 200 * polygon_br, 200 * polygon_br), Engine::renderer 
        // );

    }

    void draw_engine_object(Engine::Core::EngineObject * engineObject)
    {
        for ( auto &polygon : engineObject->mesh.polygons ) {
            draw_polygon(polygon, engineObject->position, engineObject->rotation);
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


        for ( auto &engineObject : current_scene->engine_objects ) {
            draw_engine_object(engineObject);
        }  

        // perform render queue

        Engine::Debug::logrich("Rendered");

        std::multiset<RenderQueueElement>::reverse_iterator e;

        for (e = render_queue.rbegin(); e != render_queue.rend(); e++) 
        {
            Engine::Debug::logln( std::to_string( (*e).zIndex ) + " - " + std::to_string((*e).brightness) );
            // Engine::Debug::logrich( std::to_string(e.screen_pts[0].x) );
            Engine::Draw::draw_simple_triangle(
                (*e).screen_pts,
                Engine::Core::Color(
                    200 * (*e).brightness, 
                    200 * (*e).brightness, 
                    200 * (*e).brightness
                ), 
                Engine::renderer
            );   
        }

        render_queue.clear();

        // end performance metrics
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<float> elapsed_seconds = end-start;
        float frame_time = elapsed_seconds.count();
        SDL_Delay( (Uint32)std::max(8-frame_time,(float)0) );
        frame_render_time = frame_time + std::max(1-frame_time*1000,(float)0)/1000;
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
            { "Scene Engine Objects: " + std::to_string(Engine::current_scene->engine_objects.size()), Engine::Core::Color(215,215,215) },
        };

        int idx=0;
        for ( auto engineObject : Engine::current_scene->engine_objects ) {
            idx++;
            lines.push_back(
                {
                    "Object "+ std::to_string(idx),
                    Engine::Core::Color(180,180,180)
                }
            );
            lines.push_back(
                {
                    "- Position: " + engineObject->position.to_string(),
                    Engine::Core::Color(120,120,120)
                }
            );
            lines.push_back(
                {
                    "- Rotation: " + engineObject->rotation.to_string(),
                    Engine::Core::Color(120,120,120)
                }
            );
            lines.push_back(
                {
                    "- Scale: " + engineObject->scale.to_string(),
                    Engine::Core::Color(120,120,120)
                }
            );
        }

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