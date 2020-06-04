#include "asepch.hpp"
#include "ase/core/plugin.hpp"

namespace ase
{
    PluginInterface::PluginInterface(std::string name, std::string sig, std::string desc) : 
        m_name(name), m_sig(sig), m_desc(desc)
    {
    }
    PluginInterface::~PluginInterface()
    {
    }

    void PluginInterface::Start()
    {
        // undefined start, throw an error
    }

    void PluginInterface::Stop()
    {
    }

    void PluginInterface::Update()
    {
    }

    void PluginInterface::Enable()
    {
    }

    void PluginInterface::Disable()
    {
    }

    namespace PluginManager
    {
        void DeregisterPlugin(PluginInterface* pPlugin)
        {
            XPLMDisablePlugin(XPLMGetMyID());
        }

        // defined by CLIENT
        PluginInterface* RegisterPlugin();
    }
}

