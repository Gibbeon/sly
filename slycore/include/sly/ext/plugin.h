/* #pragma once

#include <functional>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

class IPlugin {
public:
    
};

// for each dynamically loaded dll in configuration file of some sort
// call _registerplugins
// _registerplugins will insert data
// 


class Configuration {
public:
    Value& get(std::string setting);

    template<typename T>
    void set(std::string setting, T value);

private:
};





 */