#pragma once

#include <Engine/core/Mesh.h>

namespace Engine::Core
{
    class EngineObject
    {
        public: 
            Mesh mesh;
            Vector3 position;
            Vector3 scale;
            void set_mesh(Mesh mesh) {
                this->mesh = mesh;
            };
    };
}
