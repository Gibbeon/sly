/* #pragma once 

#include "te/gl/global.h"

namespace te {

class GLRenderingEngine : public IRenderingEngine
{
    public:
        GLRenderingEngine(vptr_t);

        virtual bool_t CreateDevice(IRenderingDevice** pAdapter);
    private:
        vptr_t m_pInstance;

};


} */