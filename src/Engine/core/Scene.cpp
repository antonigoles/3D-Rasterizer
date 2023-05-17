

#include <Engine/core/EngineObject.h>
#include <vector>

namespace Engine::Core
{ 
    class Scene
    {
        public:
            Scene() {};
            std::vector<EngineObject> engine_objects;   
    };
}