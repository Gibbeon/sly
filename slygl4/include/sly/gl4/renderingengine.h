#pragma once 

#include "te/gl/global.h"

namespace te {

class GLRenderingEngine : public IRenderingEngine
{
    public:
        GLRenderingEngine(void*);

        virtual bool_t CreateDevice(IRenderingDevice** pAdapter);
    private:
        void* m_pInstance;

};


}