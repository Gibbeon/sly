#pragma once 

#include "sly/gl4.h"
#include "sly/gl4/rendersystem.h"
#include "sly/gl4/gfx/device.h"

using namespace sly::gfx;


GL4RendererImpl::GL4RendererImpl() {

}

retval<std::unique_ptr<IDevice>> GL4RendererImpl::createDevice(Device& desc) {
    (*pAdapter) = new GL4Device();
}
        


/* #include "sly/gl/renderingengine.h"
#include "te/gl/renderingdevice.h"

using namespace te;

GLRenderingEngine::GLRenderingEngine(vptr_t pInstance) :
    m_pInstance(pInstance)
{

}

bool_t GLRenderingEngine::CreateDevice(IRenderingDevice** pAdapter)
{
    (*pAdapter) = new GL4Device();
    reinterpret_cast<GL4Device*>(*pAdapter)->InitializeExtensions(m_pInstance);
    return true;
}



 */