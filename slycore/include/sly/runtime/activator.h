#pragma once

#include <functional>
#include <map>
#include "sly/global.h"

namespace sly {

    class Activator {
    public:
        Activator() {}
        ~Activator() {}
        
        template<typename TType, typename std::enable_if_t<!std::is_constructible<TType>::value>* = nullptr>
        retval<TType*> create(gsl::czstring<> name, vptr_t buffer = nullptr, size_t size = sizeof(TType)) {
            Expects(size >= sizeof(TType));

            auto iter = _map.find(name);

            if(iter == _map.end()) {
                return failed<TType*>();
            }

        auto pair = (*iter).second;
            
            if(buffer == nullptr) {
                size = pair.first;
                buffer = malloc(size);
            }

            Expects(size >= pair.first);
            auto value = reinterpret_cast<TType*>(pair.second(buffer));
            return value;
        }

        template<typename TType, typename std::enable_if_t<std::is_constructible<TType>::value>* = nullptr>
        retval<TType*> create(gsl::czstring<> name, vptr_t buffer = nullptr, size_t size = sizeof(TType)) {
            Expects(size >= sizeof(TType));

            auto iter = _map.find(name);

            if(iter == _map.end()) {
                if(buffer == nullptr) {
                    buffer = malloc(size);
                }

                return new (buffer) TType();
            }
            
            auto pair = (*iter).second;

            if(buffer == nullptr) {
                size = pair.first;
                buffer = malloc(size);
            }

            Expects(size >= pair.first);
            return reinterpret_cast<TType*>(pair.second(buffer));
        }


        template<typename TType>
        retval<TType> create(gsl::czstring<> name, TType& result) {
            return *create<TType>(name, &result);
        }

        template<typename TType>
        retval<TType*> create(gsl::czstring<> name, TType*& result) {
            auto value = create<TType>(name, nullptr, sizeof(TType));
            if(value.succeeded()) {
                result = value.result();
            } else {
                result = nullptr;
            }
            return value;
        }

        template<typename TType>
        retval<void> add(gsl::czstring<> name, std::function<TType*(vptr_t)> constructor, size_t size = sizeof(TType)) {

            _map.insert_or_assign(name, std::make_pair( size, std::bind( constructor , std::placeholders::_1 )));
            return success();
        }

        template<typename TFrom, typename TTo = TFrom>
        retval<void> add() {
            return add<TTo>(
                TypeInfo::get<TFrom>().name(), 
                [](vptr_t ptr) {
                    return new (ptr) TTo();
            });
        }

    protected:
        std::map<std::string, std::pair<size_t, 
            std::function<vptr_t(vptr_t)>>
        > _map;
    };
}
