#pragma once

#include <map>
#include <string>
#include <vector>
#include <functional>

#include "sly/global.h"
#include "sly/mem/heap.h"

namespace sly {
    namespace mem {
        typedef enum {
            eHeapType_Fixed,
            eHeapType_System,
            eHeapType_UserDefined = (1 << 4)
        } eHeapType;

        struct HEAP_HANDLE {
        public:
            size_t ptr;
        };

        struct HeapDesc {
        public:
            size_t size;
            size_t blockSize;
            bool_t isDefault;
            eHeapType type;
        };

        struct MemoryManagerDesc {
        public:
            HeapDesc* HeapDesc;
            size_t count;
        };

        struct TYPE_ID {
            TYPE_ID(long_t id) : classId(id) {}
            long_t classId;
        };

        class ISerializer {

        };

        static std::function<vptr_t(IHeap&, size_t)> _TYPE_TABLE_[256];

        #define REGISTER_TYPE_TBL(class, id) _TYPE_TABLE_[id] = TYPE_ ## class ## _CTOR;
        #define REGISTER_TYPE_CTOR(class, id) const # class # * TYPE_ ## class ## _CTOR(IHeap& heap, size_t size) { new (heap.alloc(size)) class(); }
        #define REGISTER_TYPE(class, id) const TYPE_ID IID_ ## class ## = TYPE_ID(id); REGISTER_TYPE_CTOR(name, id); REGISTER_TYPE_TBL(name, id);


        REGISTER_TYPE(MemoryManagerDesc, 1);

        class BinarySerializer : public ISerializer {
        public:
            template<typename T>         
            void write(T& data) {
                _stream.write(&data, sizeof(T));
            }

            virtual void write(std::string string) {
                _stream.write(string.size());
                _stream.write(string.c_str(), string.size());
            }

            template<typename T> 
            virtual void begin() {
                write(RECORD_START);
                _TYPE_TABLE_[IID_ ## T ##](nullptr, sizeof(T));
            }
            
        protected:
            IStream& _stream;

            const uint_t RECORD_START = 0xDEADBEEF;
            const uint_t RECORD_END = 0xDEADF00D;
        };

        class BinaryDeserializer : public IDeserializer {

        };

        class ISerializable {
            virtual TYPE_ID getTypeId();

            virtual void write(ISerializer&) = 0;
            virtual void read(IDeserializer&) = 0;

        };

        class ConfigurationManager {

        };

        class IConfiguration : public ISerializable {

        };

        IConfiguration* _desc = Platform::Configuration().get("eSystemType_MemoryManager");

        IConfiguration.write(IStream*);
        IConfiguration.load(IStream*);

        
        

        Platform::registerSystem(ISystem& system);
        Platform::getSystem(eSystemType_MemoryManager).getGlobalHeap();

        class ISystem : public IPlugin {
            virtual eSystemType getSystemType() = 0;
        };

        class MemoryManager : public ISystem {
        public:
            MemoryManager() {}
            virtual ~MemoryManager() {}

            virtual void init(MemoryManagerDesc& desc);

            virtual IHeap& getGlobalHeap() {}
            virtual void setGlobalHeap(HEAP_HANDLE hHandle) {}

            virtual void getHeap(HEAP_HANDLE hHeap) {}
            virtual HEAP_HANDLE addHeap(IHeap& heap) {}
            virtual void removeHeap(HEAP_HANDLE hHeap) {}

        protected:
            IHeap* _default;
            std::map<size_t, IHeap&> _heaps;
        };        
    }
}