#include <iostream>

#include "sly/engine.h"
#include "sly/kernel.h"

using namespace sly;

Engine::Engine(Kernel& kernel) :
    _kernel(kernel) {

}

Engine::~Engine() {

}

retval<void> Engine::init(const EngineDesc& desc) { 
    resources().init();
    setupControllers();
    return success();
}

retval<void> Engine::release() {
    return success();
}

Kernel& Engine::kernel() const {
    return _kernel;
}

ResourceSystem& Engine::resources() const {
    static ResourceSystem instance(*this);
    return instance;
}

uint32_t randx() { return -1; }

retval<void> Engine::setupControllers() {
    _controllers[eEngineState_StartFrame].init([&](){
        LOG_VERBOSE("main:01 - eEngineState_StartFrame");
    }, FALSE);

    _controllers[eEngineState_ProcessMessages].init([&](){
        LOG_VERBOSE("main:02 - eEngineState_ProcessMessages");
        
    }, FALSE);

    _controllers[eEngineState_GameMain].init([&](){
        LOG_VERBOSE("main:03 - eEngineState_GameMain");
        
    }, FALSE);

    _controllers[eEngineState_SendMessages].init([&](){
        LOG_VERBOSE("main:04 - eEngineState_SendMessages");
        
    }, FALSE);

    _controllers[eEngineState_DrawFrame].init([&](){
        LOG_VERBOSE("main:04 - eEngineState_DrawFrame");
       
    }, FALSE);

/*
    _controllers[eEngineState_Wait].init([&](){
        LOG_VERBOSE("gfx:01 - eEngineState_Wait");
        std::this_thread::sleep_for(std::chrono::milliseconds(randx() % 1024));

    }, FALSE);

    _controllers[eEngineState_LoadResource].init([&](){
        LOG_VERBOSE("gfx:02 - eEngineState_LoadResource");
        std::this_thread::sleep_for(std::chrono::milliseconds(randx() % 1024));

    }, FALSE);

    _controllers[eEngineState_DrawOpaque].init([&](){
        LOG_VERBOSE("gfx:02 - eEngineState_DrawOpaque");
        std::this_thread::sleep_for(std::chrono::milliseconds(randx() % 1024));

    }, FALSE);

    _controllers[eEngineState_DrawAlpha].init([&](){
        LOG_VERBOSE("gfx:03 - eEngineState_DrawAlpha");
        std::this_thread::sleep_for(std::chrono::milliseconds(randx() % 1024));

    }, FALSE);

    _controllers[eEngineState_PostProcess].init([&](){
        LOG_VERBOSE("gfx:04 - eEngineState_PostProcess");
        std::this_thread::sleep_for(std::chrono::milliseconds(randx() % 1024));

    }, FALSE);

    _controllers[eEngineState_Swap].init([&](){
        LOG_VERBOSE("gfx:05 - eEngineState_Swap");
        std::this_thread::sleep_for(std::chrono::milliseconds(randx() % 1024));

    }, FALSE);

    */

    for(size_t state = 0; state < eEngineState_Size; ++state) {
        _signals[state].connect(_controllers[state].receiver());
    }

    _gameCtrl.init([&](){      
        LOG_VERBOSE("start game update loop");

        _signals    [eEngineState_StartFrame].emit(SIGNAL_START);
        _controllers[eEngineState_StartFrame].wait();        

        _signals    [eEngineState_ProcessMessages].emit(SIGNAL_START);
        _controllers[eEngineState_ProcessMessages].wait(); 

        _signals    [eEngineState_GameMain].emit(SIGNAL_START);
        _controllers[eEngineState_GameMain].wait(); 

        _signals    [eEngineState_SendMessages].emit(SIGNAL_START);
        _signals    [eEngineState_DrawFrame].emit(SIGNAL_START);

        _controllers[eEngineState_SendMessages].wait();
        _controllers[eEngineState_DrawFrame].wait();  

        LOG_VERBOSE("end game update loop");
    }, TRUE);  

    _renderCtrl.init([&](){      
        _signals    [eEngineState_Wait].emit(SIGNAL_START);
        _controllers[eEngineState_Wait].wait();

        _signals    [eEngineState_LoadResource].emit(SIGNAL_START);
        _signals    [eEngineState_DrawOpaque].emit(SIGNAL_START);
        
        _controllers[eEngineState_DrawOpaque].wait();

        _signals    [eEngineState_DrawAlpha].emit(SIGNAL_START);
        _controllers[eEngineState_DrawAlpha].wait();

        _signals    [eEngineState_DrawAlpha].emit(SIGNAL_START);
        _controllers[eEngineState_DrawAlpha].wait();

        _signals    [eEngineState_Swap].emit(SIGNAL_START);
        _controllers[eEngineState_Swap].wait();   
    }, TRUE);

    Signal start;

    start.connect(_gameCtrl.receiver());
    //start.connect(_renderCtrl.receiver());

    start.emit(SIGNAL_START);

    return success();
}
