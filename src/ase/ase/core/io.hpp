#pragma once

#include <fstream> // for file io

namespace ase
{
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
        void Write(std::string inputStr);
        void Write(std::string inputStr, bool fEndLine);
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

