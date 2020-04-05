#pragma once

#include "sly/global.h"

namespace sly {
    class Thread {
        public:
            static void setName(gsl::czstring<> name) {
                S_LOG_VERBOSE("Set Name = %s", name);
                _name = name;

                auto v = std::string(name);
                HRESULT r;
                    r = SetThreadDescription(
                        GetCurrentThread(),
                        std::wstring(v.begin(), v.end()).c_str()
                    );

                
            }

            static std::string& name() {
                static thread_local bool_t initialized = false;
                if(!initialized) {           
                    std::ostringstream ss;
                    ss << "Thread #" << _count++;
                    _name = ss.str();
                    initialized = true;
                    
                }

                return _name;
            }

        private:
            
            static s32 _count;
            static thread_local std::string _name;
    };
}