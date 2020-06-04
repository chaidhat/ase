#include <string>
#include <ase.hpp>

class Plugin : public ase::PluginInterface
{
public:

    Plugin() :
    ase::PluginInterface(
        std::string("Sandbox"),
        std::string("ase.company.sandbox"),
        std::string("This is a sample plugin for the ASE."))
    {
        
    }

    ~Plugin()
    {
    }

    void Start()
    {
        ase::Debug::Log("Hello World!");
        DemoIo();

    }

    void Stop()
    {
        // deregister all flightdata
        ase::DataManager::DeregisterDataRef(&m_pDataRef); 
    }

    void Update()
    {
        m_pDataRef = 2; // set eng n1 to 2
        int engN2 = m_pDataRef + 2;

        //m_pDataRef = &engN2; // not allowed! m_pEngN1 looses its address
        ase::Debug::Log(m_pDataRef);
    }

private:
    // register all flightdata
    int& m_pDataRef = ase::DataManager::RegisterDataRef<int>("777/path/dataRef");

    // demonstration of input/output
    void DemoIo()
    {
        // init file
        ase::File myFile("path1/path2/file.txt");

        // smart set/alter full file directory
        myFile.SetFullDir("path1/file.txt"); // from path1/path2/file.txt to path1/file.txt

        // change parts of filedir
        myFile.SetName("newfile"); // now path1/newfile.txt

        // get parts of filedir
        std::string myPath = myFile.GetPath(); // returns path1

        // get parts of the filedir (bool fPath, bool fName, bool fE      xt)
        std::string myFilename = myFile.GetDir(false, true, true); // newfile.txt

        // read a line from file
        std::string in = myFile.Read();

        // write a line to file
        std::string out = "apples";
        myFile.Write(out);

        // write a string to file (without line break)
        myFile.Write(out, false);

        // set log output file to myFile
        ase::Debug::s_logFile = &myFile;
    }
};

ase::PluginInterface* ase::PluginManager::RegisterPlugin()
{
    return new Plugin();
}

