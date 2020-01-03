#pragma once

#include <functional>
#include <map>

#include "sly/global.h"
#include "sly/os/operatingsystem.h"
#include "sly/ext/plugin.h"
#include "sly/ext/builders/pluginmanagerbuilder.h"

namespace sly {
    struct PluginDesc {
    public:
        std::string name;
        std::string library;
        std::string entry;    
    };

    class PluginBuilder : public Builder<PluginDesc> {
    public:
        PluginBuilder() : Builder() {}
        virtual ~PluginBuilder() {}

        PluginBuilder& setName(std::string name) { desc_.name = name; return * this ;}
        PluginBuilder& setLibrary(std::string file) { desc_.library = file; return * this ;}
        PluginBuilder& setEntry(std::string function) { desc_.entry = function; return * this ;}
    };

    class IPluginManager {
    public:
        virtual ~IPluginManager() {}
        
        virtual retval<void> init(PluginManagerDesc& desc) = 0;   
        
        virtual retval<IPlugin&>    load(PluginDesc& desc) = 0;
        virtual retval<void>        unload(IPlugin& plugin) = 0;        
        virtual retval<IPlugin&>    find(std::string monker) = 0;    
        virtual gsl::span<const IPlugin* const> plugins() = 0 ;    

    protected:
        IPluginManager() {}
    };
    
    typedef retval<IPlugin*> (*pfCreatePlugin)(const IPluginManager&);

    class PluginManager : public IPluginManager {
    public:
        PluginManager(os::IOperatingSystem* os) : _os(os) {}
        virtual ~PluginManager() {}
        
        virtual retval<void> init(PluginManagerDesc& desc) { 
            PluginBuilder builder;
            builder
                .setEntry("_RegisterPlugin")
                .setLibrary("c:/dev/sly/slyd3d12/bin/slyd3d12.dll");

            load(builder.build());
            return success(); 
        }

        virtual const TypeInfo& getType() {
            static const TypeInfo instance = TypeInfo::get<std::remove_reference<decltype(*this)>::type>();
            return instance;
        }

        virtual retval<IPlugin&>    load(PluginDesc& desc) {
            auto library = _os->loadLibrary(desc.library);

            if(library.failed()) {
                return failed<IPlugin&>();
            }

            auto proc = _os->getProcAddress(desc.entry, library);
            if(proc.failed()) {
                return failed<IPlugin&>();
            }

            auto plugin = ((pfCreatePlugin)proc)(*this);

            if(plugin.failed()) {
                return failed<IPlugin&>();
            }

            plugin->onLoad();
            _plugins.push_back(plugin.result());
            
            return *(plugin.result());
        }

        virtual retval<void>        unload(IPlugin& plugin) {
            auto iter = std::find(_plugins.begin(), _plugins.end(), std::addressof(plugin));
            if(iter == _plugins.end()) {
                return failed<void>(SLY_NOTFOUND, "The plugin was not found.");
            }

            (*iter)->onUnload();
            _plugins.erase(iter);

            return success();
        };   

        virtual retval<IPlugin&>    find(std::string moniker) {
            auto f1 = [](int x, int y) { return x + y; };
            auto unary = [&] (IPlugin* s) { return s->getName() == moniker; };

            auto iter = std::find_if(_plugins.begin(), _plugins.end(), unary);

            if(iter == _plugins.end()) {
                return failed<IPlugin&>(SLY_NOTFOUND, "The plugin was not found.");
            }
            
            return *(*iter);
        }  

        virtual gsl::span<const IPlugin* const> plugins() {
            return _plugins;
        }           
    //protected:
        PluginManager() : _os(nullptr) {}

    private:
        std::vector<IPlugin*> _plugins;
        os::IOperatingSystem* _os;       
    };
}

/*

namespace sly {
    class IPluginManager : public IPlugin {
    public:
        virtual ~IPluginManager() {}
        
        virtual retval<void> init(PluginManagerDesc& desc) = 0;
        
        virtual void set(IPlugin& plugin) = 0;
        virtual void set(const TypeInfo& info, IPlugin& plugin) = 0;

        virtual IPlugin* get(const TypeInfo& info) = 0;

        template<typename TType>
        TType* get() {
            return reinterpret_cast<TType*>(get(TypeInfo::get<TType>()));
        }

        template<typename TType>
        void set(IPlugin& plugin) {
            return set(TypeInfo::get<TType>(), plugin);
        }

    protected:
        IPluginManager() {}
    };

    class PluginManager : public IPluginManager {
    public:
        PluginManager() {}
        virtual ~PluginManager() {}
        
        virtual retval<void> init(PluginManagerDesc& desc) { return success(); }

        virtual const TypeInfo& getType() {
            static const TypeInfo instance = TypeInfo::get<std::remove_reference<decltype(*this)>::type>();
            return instance;
        }

        virtual void set(IPlugin& plugin) {
            set(plugin.getType(), plugin);
        }

        virtual void set(const TypeInfo& info, IPlugin& plugin) {
            _plugins.insert_or_assign(info, &plugin);
        }

        virtual IPlugin* get(const TypeInfo& info) {
            auto iter = _plugins.find( info );

            if(iter != _plugins.end()) {
                return reinterpret_cast<IPlugin*>(iter->second);
            }

            return NULL;
        }

    private:
        std::map<type_id, IPlugin*> _plugins;        
    };
}

*/