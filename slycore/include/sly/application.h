#pragma once

#include "sly/global.h"
#include "sly/builder.h"

namespace sly {
    struct Application {
    public:
    };

    class ApplicationBuilder : public Builder<Application> {
    public:
        ApplicationBuilder() : Builder() {}
    };

    class IApplication {
    public:
        virtual bool_t isRunning() = 0;
        virtual bool_t processMessages() = 0;
    };

    class SlyApplication : public IApplication {
    public:
        virtual bool_t isRunning();
        virtual bool_t processMessages();
    };
}

/* template<class TType>
class Builder {
public:
    TType& Build() { return _desc; }

protected:
    TType _desc;
};

class IDestroyable {
public:
    //  virtual bool_t Destroy();
};


class Viewport {

};

class Camera {

};


class IGfxVertexBuffer : public IDestroyable {
public:
    virtual bool_t Write(vptr_t data, ulong_t offset, ulong_t size)  = 0;
};

struct GfxSystem {
public:
    vptr_t<> hInstance;
};

class GfxSystemBuilder : public Builder<GfxSystem> {
public:
    GfxSystemBuilder() {
        _desc.hInstance = nullptr;
    } 

    vptr_t<GfxSystemBuilder> SetInstance(vptr_t<> instance) { _desc.hInstance = instance; }
};

struct GfxDevice {

};

class GfxDeviceBuilder : public Builder<GfxDevice> {
public:

};

class IGfxWindow;
class IGfxCommandList : public IDestroyable {
public:
    virtual bool_t Begin()  = 0;
    virtual bool_t End()  = 0;
    

    virtual bool_t Draw(vptr_t<IGfxVertexBuffer> buffer, vptr_t<IGfxWindow> window) = 0;
};

class IGfxCommandQueue : public IDestroyable {
public:
    virtual bool_t ExecuteCommandList(vptr_t<IGfxCommandList> buffer) = 0;
    virtual bool_t Flush() = 0;
};


class IGfxDevice;
class IGfxWindow : public IDestroyable {
public:
    virtual bool_t SetVisible(bool_t show) = 0;

    virtual bool_t SwapBuffers() = 0;

    virtual bool_t ProcessMessages() = 0;

    virtual IGfxCommandQueue* GetCommandQueue() = 0;

private:
};



struct GfxCommandList {

};

class GfxCommandListBuilder : public Builder<GfxCommandList> {
public:

};

struct GfxCommandQueue {

};

class GfxCommandQueueBuilder : public Builder<GfxCommandQueue> {
public:

};

struct RECT {
    RECT() = default;
    RECT(int_t left, int_t top, int_t width, int_t height) :
        l(left),
        t(top),
        w(width),
        h(height) {
    }
    union {
        struct {
            int_t l, t, w, h;
        };
        int_t array[4];
    };
};

struct Window {
public:
    RECT bounds;
    std::string title;
    int_t colorDepth;
    int_t bufferCount;
    vptr_t<> hInstance;
};


struct GfxVertexBuffer {
public:
    ulong_t size;
};


class IGfxDevice : public IDestroyable {
public:
    virtual bool_t CreateGfxCommandQueue(IGfxCommandQueue** queue, GfxCommandQueue& desc) = 0;
    virtual bool_t CreateGfxCommandList(IGfxCommandList** list, GfxCommandList& desc) = 0;
    virtual bool_t CreateGfxWindow(IGfxWindow**, Window& desc) = 0;
    virtual bool_t CreateVertexBuffer(IGfxVertexBuffer** buffer, GfxVertexBuffer& desc) = 0;
};






class RenderContextBuilder : public Builder<Window> {
public:
    RenderContextBuilder& SetBounds(RECT rect) { _desc.bounds = rect; return *this; }
    RenderContextBuilder& SetTitle(std::string title) { _desc.title = title; return *this; }
    RenderContextBuilder& SetColorDepth(int_t colorDepth) { _desc.colorDepth = colorDepth; return *this; }
    RenderContextBuilder& SetBufferCount(int_t bufferCount) { _desc.bufferCount = bufferCount;  return *this;}

protected:

};




class GfxVertexBufferBuilder : public Builder<GfxVertexBuffer> {
public:
    GfxVertexBufferBuilder() {
        _desc.size = 1024 * 1024;
    }
    
    vptr_t<GfxVertexBufferBuilder> SetSize(ulong_t size) { _desc.size = size; return this; }

};

class IGfxSystem : public IDestroyable {
public:
    virtual bool_t CreateDevice(IGfxDevice**, GfxDevice& desc) = 0;
};

class Application {
public:
    bool_t Init(vptr_t<> pInstance, std::string pszArgs);
    bool_t CreateGfxSystem(IGfxSystem** system, GfxSystem& desc);
    bool_t IsRunning();

private:
    vptr_t<> _instance;
};

extern bool_t _CreateGfxSystemImpl(IGfxSystem** system, GfxSystem& desc); */
