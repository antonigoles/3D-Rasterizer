#include <string>
#include <Engine/resources/loader.h>
#include <Engine/core/core.h>


namespace Engine::Tests
{
    // Load 3D file
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

        scene->engine_objects.push_back( *cubeObject );
    }

    void run_tests() 
    {
        // test1();
        test2();
    }
}