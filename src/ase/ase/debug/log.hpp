#pragma once
#include "asepch.hpp"

#include "ase/core/io.hpp"

namespace ase
{
    class Debug
    {
    public:
        //static void LogInit();

        static void Log(std::string message);
        static void Log(int message);
        
        static File* s_logFile;
    };
}
