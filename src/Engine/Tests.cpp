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

            cubeObject->position.x = 0.5;
            cubeObject->position.y = 0.5;

            cubeObject->set_mesh( *mesh );

            scene->engine_objects.push_back( cubeObject );

            Engine::switch_scene(scene);
        }
    }
    
    namespace EachFrame
    {
        void test1(float deltaTime) 
        {
            Engine::Core::Vector2 screen_pts[3]{ 
                Engine::Core::Vector2(0,0), 
                Engine::Core::Vector2(200, 200), 
                Engine::Core::Vector2(440, 50)
            };
            Engine::Draw::draw_simple_triangle(
                screen_pts,
                Engine::Core::Color(255,255,255),
                Engine::renderer
            );
        }

        // [Requires test2 in Single_Tests]
        void test2(float deltaTime) 
        {
            Engine::current_scene->engine_objects[0]->rotateBy(deltaTime * 1500, deltaTime * 1500,0);
        }
    }

    

    void run_single_tests() 
    {
        // Single::test1();
        Single::test2();
    }

    void run_each_frame_tests(float deltaTime)
    {
        // EachFrame::test1(deltaTime);
        EachFrame::test2(deltaTime);
    }
}