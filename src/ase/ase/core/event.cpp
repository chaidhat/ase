#include "asepch.hpp"
#include "ase/core/event.hpp"

namespace ase
{
    namespace EventManager
    {
        void RegisterEvent(EventInterface* pEvent)
        {
            ase::Debug::Log("Registering event");
            s_events.push_back(pEvent);
        }

        void DeregisterEvent(EventInterface* pInpEvent)
        {
            // consider using std::iterators
            for (EventInterface* pEvent : s_events)
            {
                if (pEvent == pInpEvent)
                    s_events.remove(pEvent);
            }
        }

        void StartEvents()
        {
            // consider using std::iterators
            for (EventInterface* pEvent : s_events)
                pEvent->Start();
        }

        void UpdateEvents()
        {
            // consider using std::iterators
            for (EventInterface* pEvent : s_events)
            {
                pEvent->Update();

                // every 1s
                s_updateItr++;
                if (s_updateItr == 100)
                {
                    pEvent->LazyUpdate();
                    s_updateItr = 0;
                }
            }
        }
    }
}
