/* struct PluginActivatorArgs : public EventArgs {
public:
    IPluginActivator& plugin;
};

class PluginSystem {
public:
    virtual void add(IPluginActivator& activator) {
        _plugins.insert_or_assign(activator.getType(), activator);
    }

    EventHandler<PluginManagerChangeArgs> onRegister;

private:
    std::map<ePluginType, IPluginActivator&> _plugins;
}; */