#pragma once

#include "ase/debug/log.hpp"

namespace ase
{
    // pure abstract class
    class EventInterface
    {
    public:
        virtual void Start() = 0;
        virtual void Update() = 0;
    };

    namespace EventManager
    {
        static std::list<EventInterface*> m_events;

        void RegisterEvent(EventInterface* pEvent);
        void DeregisterEvent(EventInterface* pInpEvent);

        void StartEvents();
        void UpdateEvents();
    }
}
