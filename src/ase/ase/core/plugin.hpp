namespace ase
{
    // plugin interface
    class PluginBehaviour
    {
    public:
        PluginBehaviour(std::string name, std::string sig, std::string desc);
        virtual ~PluginBehaviour();

        std::string name;
        std::string sig;
        std::string desc;

        virtual void Start();
        virtual void Stop();
        virtual void Update();

        virtual void Enable();
        virtual void Disable();
    };

    namespace PluginManager
    {
        void DeregisterPlugin(PluginBehaviour* plugin);

        // defined by CLIENT
        PluginBehaviour* RegisterPlugin();
    }
}
