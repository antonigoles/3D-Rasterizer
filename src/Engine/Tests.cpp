#include <string>
#include <Engine/resources/loader.h>
#include <Engine/core/core.h>
#include <Engine/Engine.h>
#include <Engine/rendering/draw.h>


namespace Engine::Tests
{
    // Load 3D file
    namespace Single 
    {
        void test1()
        {
            std::string path = "../assets/Meshes/cube.3d";
            Engine::Core::Mesh *mesh = Engine::Loader::load_mesh_from_native_engine_file(path);
            mesh->print_mesh();
        }


        // Render 3D cube
        void test2() 
        {
            std::string path = "../assets/Meshes/cube.3d";
            Engine::Core::Mesh *mesh = Engine::Loader::load_mesh_from_native_engine_file(path);

            Engine::Core::Scene *scene = new Engine::Core::Scene(); 
            Engine::Core::EngineObject *cubeObject = new Engine::Core::EngineObject();

            cubeObject->set_mesh( *mesh );

            scene->engine_objects.push_back( cubeObject );

            Engine::switch_scene(scene);
        }
    }
    
    namespace EachFrame
    {
        void test1() 
        {
            Engine::Core::Vector2 screen_pts[3]{ 
                Engine::Core::Vector2(300,300), 
                Engine::Core::Vector2(450, 600), 
                Engine::Core::Vector2(600, 400)
            };
            Engine::Draw::draw_simple_triangle(
                screen_pts,
                Engine::Core::Color(255,255,255),
                Engine::renderer
            );
        }
    }

    

    void run_single_tests() 
    {
        // Single::test1();
        Single::test2();
    }

    void run_each_frame_tests()
    {
        EachFrame::test1();
    }
}