#include "asepch.hpp"
#include "ase/core/io.hpp"

namespace ase
{
    File::File(std::string filedir)
    {
        SetFullDir(filedir);
    }

    File::~File()
    {
        if (m_fInitialised)
            Stop();
    }


    std::string File::GetDir(bool fPath, bool fName, bool fExt)
    {
        std::string outputStr = "";
        if (fPath)
            outputStr.append(m_path);
        if (fPath && fName)
            outputStr.append("/");
        if (fName)
            outputStr.append(m_name);
        if (fExt)
            outputStr.append(m_ext);
        return outputStr;
    }

    std::string File::GetFullDir()
    {
        return GetDir(true,true,true);
    }

    void File::SetFullDir(std::string fullDir)
    {
        if (m_fInitialised)
            Stop();

        int latestSeperator = 0;
        int latestDot = 0;
        for (int i = 0; i < fullDir.length(); i++)
        {
            if (fullDir.at(i) == '\\' || fullDir.at(i) == '/')
            {
                latestSeperator = i;
            }
        }
        for (int i = 0; i < fullDir.length(); i++)
        {
            if (fullDir.at(i) == '.')
            {
                latestDot = i;
            }
        }

        m_path = "";
        m_name = "";
        m_ext = "";
        if (latestSeperator == 0)
        {
            if (latestDot == 0)
            {
                // file
                m_name = fullDir;
            }
            else
            {
                // file.txt
                m_name = fullDir.substr(0, latestDot); // first part
                m_ext = fullDir.substr(latestDot, fullDir.length()); // latter part
            }
        }
        else
        {
            if (latestDot == 0)
            {
                // path/file
                m_path = fullDir.substr(0, latestSeperator); // first part
                m_name = fullDir.substr(latestSeperator, fullDir.length()); // latter part
            }
            else
            {
                // path/file.txt
                m_path = fullDir.substr(0, latestSeperator); // first part
                m_name = fullDir.substr(latestSeperator, latestDot);
                m_ext = fullDir.substr(latestDot, fullDir.length()); // latter part
            }
        }
    }

    std::string File::GetPath() { return m_path; }
    void File::SetPath(std::string filepath)
    {
        if (m_fInitialised)
            Stop();
        m_path = filepath;
    }

    std::string File::GetName() { return m_name; }
    void File::SetName(std::string filename)
    {
        if (m_fInitialised)
            Stop();
        m_name = filename;
    }

    std::string File::GetExt() { return m_ext; }
    void File::SetExt(std::string fileext)
    {
        if (m_fInitialised)
            Stop();
        m_ext = fileext;
    }

    std::string File::Read()
    {
        Debug::Log("Io: Reading from " + GetFullDir() + ".");
        if (!m_fInitialised)
            Init();

        if (m_fileIn.good())
        {
            std::string outputStr;
            getline(m_fileIn, outputStr);
            Stop();
            return outputStr;
        }
        else
        {
            Debug::Log("BAD.");
            throw IoException("BAD file " + GetFullDir() + ".");
            return NULL; // if file is not good
        }
    }

    void File::Write(const std::string& inputStr, WriteMode mode /*= WM_LNBRK*/)
    {
        Debug::Log("Io: Writing to " + GetFullDir() + ".");
        if (!m_fInitialised)
            Init();

        if (m_fileIn.good())
        {
            switch (mode)
            {
                case WM_LNBRK:
                    m_fileOut << inputStr << std::endl;
                    break;
                case WM_CONT:
                    m_fileOut << inputStr;
                    break;
            }
        }
        else
        {
            Debug::Log("BAD.");
            throw IoException("BAD file " + GetFullDir() + ".");
        }
        Stop();
    }

    void File::Init()
    {
        try 
        {
            m_fileOut = std::ofstream(GetFullDir().c_str());
            m_fileIn = std::ifstream(GetFullDir().c_str());
            m_fInitialised = true;
        }
        catch (...)
        {
            throw IoException("Erroring opening file " + GetFullDir() + ".");
        }
    }

    void File::Stop()
    {
        m_fileOut.close();
        m_fileIn.close();
        m_fInitialised = false;
    }
}

