#include "sly/metal/gfx/shader.h"

#include "mtlpp/mtlpp.hpp"
#include <stdio.h>

using namespace sly::gfx;

void METALShaderImpl::init(ShaderDesc& desc) {
    _library = getMETALDevice().NewLibrary(reinterpret_cast<const char*>(desc.data), mtlpp::CompileOptions(), nullptr);
    _data = _library.NewFunction(desc.entry.c_str());
}

