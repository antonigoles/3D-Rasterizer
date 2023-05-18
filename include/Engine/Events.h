#pragma once

#include <Engine/core/core.h>
#include <queue>

#define ENGINE_DEFAULT_EVENT 0

namespace Engine::Events 
{
    class EngineEvent 
    {
        public:
            int type; 
            EngineEvent();
            EngineEvent( int type );
    };

    extern std::queue<EngineEvent*> engine_events;

    void push_event( EngineEvent * ev );

    EngineEvent * poll_event();

}