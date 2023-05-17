#pragma once

#include <Engine/core/core.h>
#include <queue>

#define ENGINE_DEFAULT_EVENT 0
#define ENGINE_SWITCH_SCENE 2

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

    class SwitchSceneEvent : EngineEvent
    {
        public:
            int type; 
            SwitchSceneEvent(Engine::Core::Scene * newScene) 
            { 
                this->type = ENGINE_SWITCH_SCENE;
            }
    };

    std::queue<EngineEvent*> __engine_events;

    void push_event( EngineEvent * ev ) 
    {
        __engine_events.push( ev );
    }

    EngineEvent * poll_event()
    {
        if ( __engine_events.size() <= 0 ) return nullptr;
        EngineEvent * ev = __engine_events.front();
        __engine_events.pop();
        return ev;
    }

}