#include <string>

#include <ase.hpp>

class Plugin : public ase::PluginBehaviour
{
public:
    Plugin() :
    ase::PluginBehaviour(
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
    }

    void Stop()
    {
    }

    void Update()
    {
    }
};

ase::PluginBehaviour* ase::PluginManager::RegisterPlugin()
{
    return new Plugin();
}

