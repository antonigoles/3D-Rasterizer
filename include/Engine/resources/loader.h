#pragma once
#include <Engine/core/core.h>
#include <string>

namespace Engine 
{
    namespace Loader 
    {
        Engine::Core::Mesh *load_mesh_from_native_engine_file(std::string path);
    }   
}
