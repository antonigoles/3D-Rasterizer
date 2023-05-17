#pragma once

#include <Engine/core/EngineObject.h>
#include <vector>

namespace Engine
{ 
    class Scene
    {
        public:
            Scene() {};
            std::vector<EngineObject> engine_objects; 
            
    };
}
