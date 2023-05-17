#pragma once
#include <Engine/core/Mesh.h>
#include <string>

namespace Engine 
{
    namespace Loader 
    {
        Core::Mesh *load_mesh_from_native_engine_file(std::string path);
    }   
}
