#pragma once

#include "ase/core/io.hpp"

namespace ase
{
    namespace Debug
    {
        void InitLog();

        void Log(std::string message);
        void Log(int message);
        
        static File* s_logFile;
    };
}
