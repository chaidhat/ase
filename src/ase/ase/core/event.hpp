#pragma once

#include <asepch.hpp>

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
        static std::list<DataInterface*> m_events;
        void RegisterEvent(EventInterface* pEvent)
        {
            m_events.push_back(pEvent);
        }

        void DeregisterEvent(EventInterface* pEvent)
        {
        }
    }
}
