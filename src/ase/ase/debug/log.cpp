#include "asepch.hpp"
#include "ase/debug/log.hpp"

namespace ase
{
    namespace Debug
    {
        void Log(std::string message)
        {
            XPLMDebugString((message + "\n").c_str());
        }

        void Log(int message)
        {
            Log(std::to_string(message));
        }

        void InitLog()
        {
        }
    }
}

