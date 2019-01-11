/* #pragma once

// read header
// read descriptor
// create object
// pass

#define GET_IID(className) IID_ ## className
#define GET_TYPE_CTOR(className) className* className ## _ctor_(IHeap& heap) { (new (heap.alloc(sizeof(className))()); }

namespace sly {
    namespace io {



            class ActivationTable {
    public:
        IActiavtor* getActivator(u32 typeId) {

        }

        IActiavtor* getActivator(std::string typeName) {

        }

        void ActivationTable(Typeriptor<> descriptor) {
            _byName.assign_or_insert(typeName, activator);
            _byId[descriptor.id] = activator;
        }

    protected:
        std::map<std::string, IActivator&> _byName;
        std::vector<IActivator&> _byId;
    };
        

        typedef enum {
            eSerializationType_Binary,
            eSerializationType_String
        } eSerializationType;

        typedef enum {
            eSerializationScope_System,
            eSerializationScope_UserDefined = (1 << 4),
        } eSerializationScope;

        class BinaryDeserializer : public IDeserializer {
        public:
            BinaryDeserializer() {
                // load in system scope table from static
            }

            virtual ~BinaryDeserializer() {}
            ISerializable* read(IStream& stream, IHeap& heap) {
                BinaryReader reader(stream);
                
                eSerializationType type = (eSerializationType)reader.read<u32>();
                eSerializationScope scope = (eSerializationType)reader.read<u32>();

                IActiavtor* activator = nullptr;
                ActivationTable table = _tables(scope);

                switch(headerType) {
                    case eSerializationHeaderType_Binary:
                        size_t typeId = reader.read<u32>();
                        activator = table.getActivator(typeId);
                        break;
                    case eSerializationHeaderType_String:
                        std::string title;
                        reader.read(&title);
                        activator = table.getActivator(title);
                        break;
                } 
            }
        protected:
            std::map<u32, ActivationTable&> _tables;
        };
    }
} */