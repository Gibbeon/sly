#pragma once

#include <functional>
#include <unordered_map>

#include "sly/global.h"
#include "sly/plugin.h"

namespace sly {

    class TypeActivator {
    public:
        template<typename TInterface, typename TClass>
        void assign() {
            //_map.insert_or_assign(TypeInfo::get<TInterface>(), [=](vptr_t buffer) { return reinterpret_cast<vptr_t>(new (buffer) TClass()); });
            _map.insert_or_assign(TypeInfo::get<TInterface>().getId(), TypeInfo::get<TClass>());
            _map.insert_or_assign(TypeInfo::get<TClass>().getId(), TypeInfo::get<TClass>());
        }

        template<typename TInterface>
        TInterface* create() {
            auto iter = _map.find( TypeInfo::get<TInterface>() );

            if(iter != _map.end()) {
                return reinterpret_cast<TInterface*>(iter->second());
            }

            return NULL;
        }

        template<typename TInterface, typename TClass>
        TInterface* create() {
            auto iter = _map.find( TypeInfo::get<TInterface>() );

            if(iter != _map.end()) {
                return reinterpret_cast<TInterface*>(iter->second());
            }

            return new TClass();
        }

        
        vptr_t create(type_id id, vptr_t buffer) {
            auto iter = _map.find( id );

            if(iter != _map.end()) {
                return reinterpret_cast<vptr_t>(iter->second.getDefaultConstructor()(buffer));
            }

            return NULL;
        }

        const TypeInfo& getTypeInfo(type_id id) {
            auto iter = _map.find( id );

            if(iter != _map.end()) {
                return iter->second;
            }

            return TypeInfo::get<void*>();
        }

        template<typename T>
        void add() {
            assign<T,T>();
        }

    protected:
        //std::map< type_id, std::function<vptr_t(vptr_t)> > _map;
        std::unordered_map< type_id, TypeInfo > _map;
    };
}