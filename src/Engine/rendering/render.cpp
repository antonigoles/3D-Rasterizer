#include <Engine/core/core.h>
#include <Engine/Debug.h>
#include <chrono>
#include <SDL2/SDL.h>

namespace Engine::Render
{
    void draw_scene(Engine::Core::Scene * current_scene, SDL_Window *window) 
    {
        auto start = std::chrono::steady_clock::now();

        // to implement



        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        double frame_time = elapsed_seconds.count();
        Engine::Debug::logrich(
            "Rendering scene time: " 
            + std::to_string(frame_time) 
            + " ( " + std::to_string(1/frame_time) + " FPS )" 
        );
    }
}