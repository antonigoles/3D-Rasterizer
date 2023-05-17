#pragma once

#include <Engine/core/Mesh.h>

namespace Engine::Core
{
    class Camera
    {
        public: 
            Vector3 position;
            Vector3 rotation;
            Camera() {
                this->rotation = Vector3(); 
                this->position = Vector3(); 
            };
    };
}
