#pragma once
#include <fstream> // for file io

#include "ase/debug/log.hpp"

namespace ase
{
    class IoException : public std::runtime_error 
    {
    public:
        IoException(const std::string& msg):
            runtime_error(msg)
        {}
    };

    enum WriteMode
    {
        WM_LNBRK, // line break (default)
        WM_CONT, // continuous, no line breaks
    };

    class File
    {
    public:
        File(std::string filedir);
        ~File();

        std::string GetDir(bool fPath, bool fName, bool fExt);

        std::string GetFullDir();
        void SetFullDir(std::string fullDir);

        std::string GetPath();
        void SetPath(std::string filepath);

        std::string GetName();
        void SetName(std::string filename);

        std::string GetExt();
        void SetExt(std::string fillext);

        std::string Read();
        void Write(const std::string& inputStr, WriteMode mode = WM_LNBRK);

    private:
        void Init();
        void Stop();

        std::string m_path = "";
        std::string m_name = "";
        std::string m_ext = "";

        std::ofstream m_fileOut;
        std::ifstream m_fileIn;
        bool m_fInitialised = false;
    };
}

