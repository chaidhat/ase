#pragma once
#include "asepch.hpp"

#include "ase/core/io.hpp"

namespace ase
{
    class Debug
    {
    public:
        //static void InitLog();

        static void Log(const std::string message);
        static void Log(const int message);
        
        static File* s_logFile;
    };
}
