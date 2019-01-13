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
}