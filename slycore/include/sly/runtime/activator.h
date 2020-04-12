#pragma once

#include <functional>
#include <map>
#include "sly/global.h"

namespace sly {

    class Activator {
    public:
        Activator() {}
        ~Activator() {}

        retval<ISerializable&> create(gsl::czstring<> name) {
            auto fn = _map[name];
            auto value = fn();
            
            //ISerializable* convert = reinterpret_cast<ISerializable*>(value);

            //std::shared_ptr<ISerializable> result;
            //result.reset((ISerializable*)value);
            return *value;
        }

        template<typename TType>
        retval<void> assign(gsl::czstring<> name, std::function<TType*()> fn) {
            _map.insert( std::make_pair( name, std::bind( fn ) ));
            //auto kvp = _map.insert_or_assign(name, fn);
            return success();
        }

    protected:
        std::map<std::string, std::function<ISerializable*()>> _map;
    };
}
