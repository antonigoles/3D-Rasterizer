#pragma once

#include <Engine/core/Mesh.h>

namespace Engine
{
    class EngineObject
    {
        public: 
            Mesh mesh;
            void set_mesh(Mesh mesh) {
                mesh = mesh;
            }
    };
}
