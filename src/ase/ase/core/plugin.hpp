#pragma once

namespace ase
{
    // plugin interface
    class PluginInterface
    {
    public:
        PluginInterface(std::string name, std::string sig, std::string desc);
        virtual ~PluginInterface();

        std::string m_name;
        std::string m_sig;
        std::string m_desc;

        virtual void Start();
        virtual void Stop();
        virtual void Update();

        virtual void Enable();
        virtual void Disable();
    };

    namespace PluginManager
    {
        void DeregisterPlugin(PluginInterface* pPlugin);

        // defined by CLIENT
        PluginInterface* RegisterPlugin();
    }
}
