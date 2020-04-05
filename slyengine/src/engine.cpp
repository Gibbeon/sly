#include <iostream>

#include "sly/engine.h"
#include "sly/kernel.h"
#include "sly/scene.h"
#include "sly/runtime/activator.h"
#include "sly/controllers/inputcontroller.h"
#include "sly/controllers/rendercontroller.h"

using namespace sly;

Engine::Engine(Kernel& kernel) :
    _kernel(kernel) {

}

Engine::~Engine() {

}

retval<void> Engine::init(const EngineDesc& desc) { 
    resources().init();
    setupTasks();
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

InputController& Engine::input() const {
    static InputController instance(*this);
    return instance;
}

RenderController& Engine::graphics() const {
    static RenderController instance(*this);
    return instance;
}

Activator& Engine::activator() const {
    static Activator instance;
    return instance;
}

retval<void>    Engine::update() {
    input().execute();
    //game().execute();
    return success();
}

retval<void>    Engine::draw() {
    graphics().execute();
    return success();
}

bool_t          Engine::ready() {
    return true;
}



retval<void> Engine::setupTasks() {
    /*
    _controllers[eEngineTask_NetworkRead].init("Eng_NetworkRead", [](){}, FALSE, TRUE);
    _controllers[eEngineTask_InputRead].init("Eng_InputRead", [](){}, FALSE, TRUE);
    _controllers[eEngineTask_Update].init("Eng_Update", [&]() {
        TaskPool tasks;
        static size_t frameCount = 0;

        for(auto& scene: this->scenes()) {
            tasks.doTask([&]() {
                    scene.update();
                }
            );
        }
        tasks.wait();

        
        //LOG_VERBOSE("Update %i", frameCount++);

    }
    , FALSE, TRUE);

    _controllers[eEngineTask_NetworkSend].init("Eng_NetworkSend", [&]() {}, FALSE, TRUE);
    _controllers[eEngineTask_SubmitFrame].init("Eng_SubmitFrame", [&]() {
        DrawFrame frame;

         //TaskPool tasks;

        //for(auto scene: _engine.scenes()) {
        //  tasks.doTask([&]() {
        //           scene.drawTo(frame);
        //       }
        //    );
        //}
        //tasks.wait();
        
        _gfxsignal.emit(eEngineSingal_RenderFrame, &frame);
        _controllers[eEngineTask_WaitForFrame].wait();
    }
    , FALSE, TRUE);

    _controllers[eEngineTask_WaitForFrame].init("Gfx_WaitForFrame", [&]() {
        static bool_t init = false;
        if(!init) {
            _controllers[eEngineTask_WaitForFrame].receiver().init(
                [&](SignalReceiver& self, SignalValue value, va_list args) {
                    switch(value) {
                        case SIGNAL_START:
                            self.parent<Task>().start();
                            break;
                        case eEngineSingal_RenderFrame:
                            isFrameReady.notifyOne();  
                            break;     
                        default:
                            LOG_ERROR("Invalid signal. %i", value);
                            break;
                    }
                }
            );
            init = true; 
        }
        isFrameReady.wait();
    }
    , FALSE, TRUE);

    _controllers[eEngineTask_LoadResources].init("Gfx_LoadResource", &EmptyUpdate/*[&]() {
        DrawFrame* frame;

        static bool_t init = false;
        if(!init) {
            _controllers[eEngineTask_LoadResources].receiver().init(
                [&](SignalReceiver& self, SignalValue value, va_list args) {
                    switch(value) {
                        case SIGNAL_START:
                            self.parent<Task>().start();
                            break;
                        case eEngineSingal_RenderFrame:
                            frame = va_arg(args, DrawFrame*);
                            Expects(frame);
                            break;          
                        default:
                            break;
                    }
                }
            );
            init = true;
        }

        //TaskPool tasks;
        //auto iter = frame.begin();

        //while(iter != frame.end()) {
        //    tasks.doTask([]() {
        //            iter.load();
        //        }
        //    );
        //    ++iter;
       // }

        //tasks.wait();
    }
    , FALSE, TRUE);

    _controllers[eEngineTask_UpdateAnimations].init("Gfx_UpdateAnimations", &EmptyUpdate/*[&]() {
        DrawFrame* frame;

        static bool_t init = false;
        if(!init) {
            _controllers[eEngineTask_UpdateAnimations].receiver().init(
                [&](SignalReceiver& self, SignalValue value, va_list args) {
                    switch(value) {
                        case SIGNAL_START:
                            self.parent<Task>().start();
                            break;
                        case eEngineSingal_RenderFrame:
                            frame = va_arg(args, DrawFrame*);
                            Expects(frame); 
                            break;         
                        default:
                            break;
                    }
                }
            );
            init = true;
        }

        /*TaskPool tasks;
        auto iter = frame.begin();

        while(iter != frame.end()) {
            tasks.doTask([]() {
                    iter.update();
                }
            );
            ++iter;
        }

        tasks.wait();
    }
    , FALSE, TRUE);

    _controllers[eEngineTask_Render].init("Gfx_Render", &EmptyUpdate/*[&]() {
        DrawFrame* frame;
        static bool_t init = false;
        if(!init) {
            _controllers[eEngineTask_Render].receiver().init(
                [&](SignalReceiver& self, SignalValue value, va_list args) {
                    switch(value) {
                        case SIGNAL_START:
                            self.parent<Task>().start();
                            break;
                        case eEngineSingal_RenderFrame:
                            frame = va_arg(args, DrawFrame*);
                            Expects(frame);  
                            break;        
                        default:
                            break;
                    }
                }
            );       
            init = true;
        } 


        TaskPool tasks;
        auto iter = frame.begin();

        while(iter != frame.end()) {
            tasks.doTask([]() {
                    iter.draw();
                }
            );
            ++iter;
        }

        tasks.wait();
    }
    , FALSE, TRUE);

    _controllers[eEngineTask_PostProcess].init("Gfx_PostProcess", [&]() {
        DrawFrame* frame;
        static bool_t init = false;

        if(!init) {
            auto fn = [&](SignalReceiver& self, SignalValue value, va_list args) {
                        switch(value) {
                            case SIGNAL_START:
                                self.parent<Task>().start();
                                break;
                            case eEngineSingal_RenderFrame:
                                frame = va_arg(args, DrawFrame*);
                                Expects(frame);  
                                break;        
                            default:
                                break;
                        }
                    };
            
            _controllers[eEngineTask_PostProcess].receiver().init(fn);
                
            init = true;
        }    
        static size_t frameCount = 0;
        if((frameCount++ % 2048) == 0)
            LOG_VERBOSE("Draw %i", frameCount);
        //frame.present();
    }
    , FALSE, TRUE);

    _controllers[eEngineTask_Present].init("Gfx_Present", &EmptyUpdate/*[&]() {
        DrawFrame* frame;
        static size_t frameCount = 0;
        static bool_t init = false;
        if(!init) {
            _controllers[eEngineTask_Present].receiver().init(
                [&](SignalReceiver& self, SignalValue value, va_list args) {
                    switch(value) {
                        case SIGNAL_START:
                            self.parent<Task>().start();
                            break;
                        case eEngineSingal_RenderFrame:
                            frame = va_arg(args, DrawFrame*);
                            Expects(frame);  
                            break;        
                        default:
                            break;
                    }
                }
            );
            init = true; 
        }
//printf("Draw %i\n", frameCount++);
        LOG_VERBOSE("Draw %i", frameCount++);

        //frame.present();
    }
    , FALSE, TRUE);

    _stateCtrls[eEngineState_PrepareUpdate].push_back(&_controllers[eEngineTask_NetworkRead]);
    _stateCtrls[eEngineState_PrepareUpdate].push_back(&_controllers[eEngineTask_InputRead]); 
    _stateCtrls[eEngineState_Update].push_back(&_controllers[eEngineTask_Update]);      
    _stateCtrls[eEngineState_Notify].push_back(&_controllers[eEngineTask_NetworkSend]);      
    _stateCtrls[eEngineState_Notify].push_back(&_controllers[eEngineTask_SubmitFrame]);

    _stateCtrls[eEngineState_Ready].push_back(&_controllers[eEngineTask_WaitForFrame]);
    _stateCtrls[eEngineState_PrepareRender].push_back(&_controllers[eEngineTask_LoadResources]); 
    _stateCtrls[eEngineState_PrepareRender].push_back(&_controllers[eEngineTask_UpdateAnimations]); 
    _stateCtrls[eEngineState_Render].push_back(&_controllers[eEngineTask_Render]);  
    _stateCtrls[eEngineState_Render].push_back(&_controllers[eEngineTask_PostProcess]);      
    _stateCtrls[eEngineState_Present].push_back(&_controllers[eEngineTask_Present]);  

    // hook up signals
    for(size_t n = 0; n < eEngineState_Size; n++) {
        for(auto ctrl : _stateCtrls[n]) {
            _signals[n].connect(ctrl->receiver());
        }
    }   
    


    _gameCtrl.init("GameCtrl", [&](){      

        //LOG_VERBOSE("[[ GAME UPDATE BEGIN ]]");
        DrawFrame frame;

        _signals    [eEngineState_PrepareUpdate].emit(SIGNAL_START);
        waitFor(_stateCtrls[eEngineState_PrepareUpdate]);

        _signals    [eEngineState_Update].emit(SIGNAL_START);
        waitFor(_stateCtrls[eEngineState_Update]);

        _signals    [eEngineState_Notify].emit(eEngineSingal_RenderFrame, &frame);
        _signals    [eEngineState_Notify].emit(SIGNAL_START);
        waitFor(_stateCtrls[eEngineState_Notify]);
    }, TRUE, TRUE); 

    _renderCtrl.init("GfxCtrl", [&](){ 
        
        //LOG_VERBOSE("-= RENDER FRAME BEGIN -=");
        DrawFrame frame;
        DrawFrame* frameptr;

        static bool_t init = false;
        if(!init) {
            _renderCtrl.receiver().init(
                [&](SignalReceiver& self, SignalValue value, va_list args) {
                    switch(value) {
                        case SIGNAL_START:
                            self.parent<Task>().start();
                            break;
                        case eEngineSingal_RenderFrame:             
                            frameptr = va_arg(args, DrawFrame*);
                            Expects(frameptr);                          
                            break;  
                    }
                }
            );
            init = true; 
        }
        
        _signals    [eEngineState_Ready].emit(SIGNAL_START); 
        waitFor(_stateCtrls[eEngineState_Ready]);

        //frame = *frameptr; 

        _signals    [eEngineState_PrepareRender].emit(eEngineSingal_RenderFrame, &frame);
        _signals    [eEngineState_PrepareRender].emit(SIGNAL_START); 
        waitFor(_stateCtrls[eEngineState_PrepareRender]);

        _signals    [eEngineState_Render].emit(eEngineSingal_RenderFrame, &frame);
        _signals    [eEngineState_Render].emit(SIGNAL_START);   

        waitFor(_stateCtrls[eEngineState_Render]);

        _signals    [eEngineState_Present].emit(eEngineSingal_RenderFrame, &frame);
        _signals    [eEngineState_Present].emit(SIGNAL_START);   

        waitFor(_stateCtrls[eEngineState_Present]);
    
    }, TRUE, TRUE);

    _gfxsignal.connect(_renderCtrl.receiver());
    _gfxsignal.connect(_controllers[eEngineTask_WaitForFrame].receiver());

    Signal start;

    start.connect(_gameCtrl.receiver());
    start.connect(_renderCtrl.receiver());

    start.emit(SIGNAL_START);
    */

    return success();
}
