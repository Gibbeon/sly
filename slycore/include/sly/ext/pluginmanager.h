#pragma once

#include <functional>
#include <map>

#include "sly/global.h"
#include "sly/plugin.h"

namespace sly {
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