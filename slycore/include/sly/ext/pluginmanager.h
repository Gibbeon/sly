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
    
    typedef sly::retval< std::function<sly::IPlugin*(void)> > (*pfGetType)();

    class PluginManager : public IPluginManager {
    public:
        virtual ~PluginManager() {}
        
        virtual retval<void> init(PluginManagerDesc& desc) { 
            #if _WIN32
            PluginBuilder builder;
            builder
                .setEntry("GetD3D12Renderer")
                .setLibrary("c:/dev/sly/slyd3d12/bin/slyd3d12.dll");

            load(builder.build());
            #endif
            
            return success(); 
        }

        virtual const TypeInfo& getType() {
            static const TypeInfo instance = TypeInfo::get<std::remove_reference<decltype(*this)>::type>();
            return instance;
        }

        virtual retval<IPlugin&>    load(PluginDesc& desc) {
            os::SystemInterface os;
            os.init(os::SystemInterfaceBuilder().build());

            auto library = os.loadLibrary(desc.library);

            if(library.failed()) {
                return failed<IPlugin&>();
            }

            auto proc = os.getProcAddress(desc.entry, library.result());
            if(proc.failed()) {
                return failed<IPlugin&>();
            }

            auto plugin = ((pfGetType)proc)();

            if(plugin.failed()) {
                return failed<IPlugin&>();
            }

            IPlugin* value = (IPlugin*)(plugin.result())();

            _plugins.push_back(value);
            
            return *value;
        }

        virtual retval<void>        unload(IPlugin& plugin) {
            auto iter = std::find(_plugins.begin(), _plugins.end(), std::addressof(plugin));
            if(iter == _plugins.end()) {
                return failed<void>(SLY_NOTFOUND, "The plugin was not found.");
            }

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
        PluginManager() {}

    private:
        std::vector<IPlugin*> _plugins;    
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