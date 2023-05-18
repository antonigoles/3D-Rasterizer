#include <Engine/core/core.h>
#include <queue>

#define ENGINE_DEFAULT_EVENT 0

namespace Engine::Events 
{
    class EngineEvent 
    {
        public:
            int type; 
            EngineEvent() { this->type = ENGINE_DEFAULT_EVENT; }
            EngineEvent( int type ) 
            { 
                this->type = type;
            }
    };

    std::queue<EngineEvent*> engine_events;

    void push_event( EngineEvent * ev ) 
    {
        engine_events.push( ev );
    }

    EngineEvent * poll_event()
    {
        if ( engine_events.size() <= 0 ) return nullptr;
        EngineEvent * ev = engine_events.front();
        engine_events.pop();
        return ev;
    }

}