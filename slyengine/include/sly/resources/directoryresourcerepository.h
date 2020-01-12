#pragma once

#include <filesystem>
#include "sly/global.h"
#include "sly/kernel.h"
#include "sly/resources/resourcerepository.h"
#include "sly/resources/resourcehandle.h"

namespace sly {     
    class DirectoryResourceRepository : public IResourceRepository {
    public:
        virtual retval<void> release() {
            
            return success();
        }
        
        virtual retval<void> open(gsl::czstring<> moniker) {
            _basePath = moniker;

            for(auto& p: std::filesystem::directory_iterator(moniker)) {
                if(p.is_regular_file()) {
                    ResourceHandle value;

                    auto a = std::filesystem::absolute(p.path());
                    auto b = std::filesystem::absolute(moniker);

                    auto path = std::filesystem::relative(a, b);

                    auto extension = std::wstring(path.extension());
                    auto stem = std::wstring(path.stem());
                    
                    value.moniker = std::string(stem.begin(), stem.end());  
                    value.extension = std::string(extension.begin(), extension.end());

                    std::transform(value.extension.begin(), value.extension.end(), value.extension.begin(), [](unsigned char c){ return std::tolower(c); });
                    std::transform(value.moniker.begin(), value.moniker.end(), value.moniker.begin(), [](unsigned char c){ return std::tolower(c); });
                    
                    _resources.push_back(value);
                }
            }
            
            return success();
        }

        virtual retval<void> close() {
            return success();
        }

        virtual retval<IInputStream&> getStream(ResourceHandle& handle) {
            return Kernel::get().filesystem().open((_basePath +"/" + handle.moniker + handle.extension).c_str())->stream();
        }

        virtual std::vector<ResourceHandle> resources() const {
            return _resources;
        }

    protected:
        std::vector<ResourceHandle> _resources;
        std::string _basePath;
    };
}



