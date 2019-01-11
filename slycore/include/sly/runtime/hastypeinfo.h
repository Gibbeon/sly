#pragma once

#include <string>

namespace sly {

    class IHasTypeInfo {
    public:
        virtual ~IHasTypeInfo() {}

        virtual size_t getTypeIID() = 0;
        virtual std::string getTypeName() = 0;

    protected:
        IHasTypeInfo() {}
    };
}

