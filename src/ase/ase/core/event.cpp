#include "asepch.hpp"
#include "ase/core/event.hpp"

namespace ase
{
    namespace EventManager
    {
        void RegisterEvent(EventInterface* pEvent)
        {
            ase::Debug::Log("Events: Registering event");
            s_events.push_back(pEvent);
        }

        void DeregisterEvent(EventInterface* pInpEvent)
        {
            // consider using std::iterators
            //ase::Debug::Log("Events: Deregistering event");
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
            s_updateItr++;
            // consider using std::iterators
            for (EventInterface* pEvent : s_events)
            {
                pEvent->Update();
                // every 1s
                if (s_updateItr == 100)
                    pEvent->LazyUpdate();
            }
            // every 1s
            if (s_updateItr == 100)
                s_updateItr = 0;
        }
    }
    }
