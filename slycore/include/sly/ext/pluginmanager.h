#pragma once

#include <functional>
#include <map>

#include "sly/global.h"
#include "sly/plugin.h"

namespace sly {

    class TypeActivator {
    public:
        template<typename TInterface, typename TClass>
        void assign() {
            _map.insert_or_assign(TypeInfo::get<TInterface>(), []() { return reinterpret_cast<vptr_t>(new TClass()); });
        }

        template<typename TInterface>
        TInterface* create() {
            auto iter = _map.find( TypeInfo::get<TInterface>() );

            if(iter !== _map.end()) {
                return reinterpret_cast<TInterface*>(iter->second());
            }

            return NULL;
        }

        template<typename TInterface, typename TClass>
        TInterface* create() {
            auto iter = _map.find( TypeInfo::get<TInterface>() );

            if(iter !== _map.end()) {
                return reinterpret_cast<TInterface*>(iter->second());
            }

            return new TClass();
        }

    protected:
        std::map< type_id, std::function<vptr_t(void)> > _map;
    };

    class IPluginManager : public IPlugin {
    public:
        virtual ~IPluginManager() {}
        
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

        virtual const TypeInfo& getType() {
            static const TypeInfo instance = TypeInfo::get<decltype(*this)>();
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