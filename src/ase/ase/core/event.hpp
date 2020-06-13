#pragma once
#include <list>

#include "ase/debug/log.hpp"

namespace ase
{
    // pure abstract class
    class EventInterface
    {
    public:
        virtual void Start() = 0;
        virtual void Stop() = 0;

        virtual void Update() = 0;
        virtual void LazyUpdate() = 0;
    };

    namespace EventManager
    {
        static std::list<EventInterface*> s_events;
        static char s_updateItr = 0;

        void RegisterEvent(EventInterface* pEvent);
        void DeregisterEvent(EventInterface* pInpEvent);

        void StartEvents();
        void UpdateEvents();
    }
}
