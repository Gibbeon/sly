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

retval<void> Engine::setupControllers() {
    _controllers[eEngineState_StartFrame].init([&](){

    }, FALSE);

    _controllers[eEngineState_ProcessMessages].init([&](){

    }, FALSE);

    _controllers[eEngineState_GameMain].init([&](){

    }, FALSE);

    _controllers[eEngineState_SendMessages].init([&](){

    }, FALSE);

    _controllers[eEngineState_DrawFrame].init([&](){

    }, FALSE);

    _controllers[eEngineState_Wait].init([&](){

    }, FALSE);

    _controllers[eEngineState_LoadResource].init([&](){

    }, FALSE);

    _controllers[eEngineState_DrawOpaque].init([&](){

    }, FALSE);

    _controllers[eEngineState_DrawAlpha].init([&](){

    }, FALSE);

    _controllers[eEngineState_PostProcess].init([&](){

    }, FALSE);

    _controllers[eEngineState_Swap].init([&](){

    }, FALSE);

    for(size_t state = 0; state < eEngineState_Size; ++state) {
        _signals[state].connect(_controllers[state].receiver());
    }

    _gameCtrl.init([&](){      
        std::cout << "_gameCtrl" << std::flush;
        printf("test2");
        /*_signals    [eEngineState_StartFrame].emit(SIGNAL_START);
        _controllers[eEngineState_StartFrame].wait();

        _signals    [eEngineState_ProcessMessages].emit(SIGNAL_START);
        _controllers[eEngineState_ProcessMessages].wait();

        _signals    [eEngineState_GameMain].emit(SIGNAL_START);
        _controllers[eEngineState_GameMain].wait();

        _signals    [eEngineState_SendMessages].emit(SIGNAL_START);
        _signals    [eEngineState_DrawFrame].emit(SIGNAL_START);
        _controllers[eEngineState_SendMessages].wait();    
        */ 
    });  

    _renderCtrl.init([&](){        
        /*_signals    [eEngineState_Wait].emit(SIGNAL_START);
        _controllers[eEngineState_Wait].wait();

        _signals    [eEngineState_LoadResource].emit(SIGNAL_START);
        _signals    [eEngineState_DrawOpaque].emit(SIGNAL_START);
        
        _controllers[eEngineState_DrawOpaque].wait();

        _signals    [eEngineState_DrawAlpha].emit(SIGNAL_START);
        _controllers[eEngineState_DrawAlpha].wait();

        _signals    [eEngineState_DrawAlpha].emit(SIGNAL_START);
        _controllers[eEngineState_DrawAlpha].wait();

        _signals    [eEngineState_Swap].emit(SIGNAL_START);
        _controllers[eEngineState_Swap].wait();  */   
    });

    Signal start;
    //Controller gameCtrl;
    //gameCtrl.init([]() {});

    start.connect(_gameCtrl.receiver());
    //start.connect(_renderCtrl.receiver());

    start.emit(SIGNAL_START);

    return success();
}
