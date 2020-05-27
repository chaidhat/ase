#include "asepch.hpp"
#include "ase/core/plugin.hpp"

namespace ase
{
    PluginBehaviour::PluginBehaviour(std::string name, std::string sig, std::string desc) : name(name), sig(sig),
    desc(desc)
    {
    }
    PluginBehaviour::~PluginBehaviour()
    {
    }

    void PluginBehaviour::Start()
    {
    }

    void PluginBehaviour::Stop()
    {
    }

    void PluginBehaviour::Update()
    {
    }

    void PluginBehaviour::Enable()
    {
    }

    void PluginBehaviour::Disable()
    {
    }

    namespace PluginManager
    {
        void DeregisterPlugin(PluginBehaviour* plugin)
        {
            XPLMDisablePlugin(XPLMGetMyID());
        }

        // defined by CLIENT
        PluginBehaviour* RegisterPlugin();
    }
}

