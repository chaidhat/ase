#include "asepch.hpp"
#include "ase/debug/log.hpp"


#include <iostream>

namespace ase
{
    namespace Debug
    {
        void InitLog ()
        {
        }

        void Log (std::string message)
        {
            std::cout << message << std::endl;
            XPLMDebugString(message.c_str());
        }

        void Log (int message)
        {
            std::cout << std::to_string(message) << std::endl;
            XPLMDebugString(std::to_string(message).c_str());
        }
    }
}

