#include "asepch.hpp"
#include "ase/core/event.hpp"

namespace ase
{
    namespace EventManager
    {
        void RegisterEvent(EventInterface* pEvent)
        {
            ase::Debug::Log("Registering event");
            m_events.push_back(pEvent);
        }

        void DeregisterEvent(EventInterface* pInpEvent)
        {
            // consider using std::iterators
            for (EventInterface* pEvent : m_events)
            {
                if (pEvent == pInpEvent)
                    m_events.remove(pEvent);
            }
        }

        void StartEvents()
        {
            // consider using std::iterators
            for (EventInterface* pEvent : m_events)
                pEvent->Start();
        }

        void UpdateEvents()
        {
            // consider using std::iterators
            for (EventInterface* pEvent : m_events)
                pEvent->Update();
        }
    }
}
