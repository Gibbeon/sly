#pragma once

#include "sly/global.h"
#include "sly/engine.h"
#include "sly/controller.h"
#include "sly/drawframe.h"



    //eEngineState_NetworkAccept,
    //eEngineState_InputAccept,
    //eEngineState_AI,
    //eEngineState_Game,
    //eEngineState_Physics,
    //eEngineState_NetworkSend,
    //eEngineState_DrawFrame,
    //eEngineState_FrameWait,
    //eEngineState_LoadResource,
    //eEngineState_AnimationUpdate,
    //eEngineState_Render,
    //eEngineState_PostProcess,
    //eEngineState_Swap,
    //

//  [main]
//      [network-accept]    update & process message
//      [input-accept]      update & process message
//      [ai system-update]  process commands, send events
//  waitfor [network-accept], [input-accept], [ai system-update]
//      [game] game logic, send soundfx to mixer, send network events
//      [animation-collission] update animation states, if an animation causes collisions send events, send soundfx to mixer
//      [physics-collission] resolve collissions, send events
//  waitfor [game], [animation-collission], [physics-collission]
//      [network-send] send network output
//      [render] pass a camera through the scenes to find out which entities are visible, submit drawables to the frame, lod values, submit frame to be rendered
//  waitfor [network-send], [render]
//  sleep [main] until frame

//  waitfor [draw] (prior frame swap, new frame available) [every scene submits to same frame]
//      [resources] load resources, garbage collect unref resources, set entity ready when resource loaded (deferred loading means ready now)
//      [animation] for entities that are visible update animations, set entity ready when animation done
//      [draw]  split entities into alpha vs non-alpha
//              bucket entities by expensive renderstate swaps (what about recording render state?), near to far
//              [draw-thread (1-N)] opaque objects
//                  for each render thread pull from buckets
//                  for each render thread record command lists
//                  as a bucket is done, submit it to the draw buffer; if there are more to pull create a new command list
//      [draw]  pull lists from queue
//              waitfor [draw-thread (1-N)]
//              [draw-thread (1-N)] alpha objects
//                  for each render thread pull from buckets
//                  for each render thread record command lists
//                  as a bucket is done, submit it to the commandqueue; if there are more to pull create a new command list
//      [draw]  all lists from queue in order
//              waitfor [draw-thread (1-N)]
//      [draw]  post frame effects
//              swap frame
//              release frame

namespace sly {

    class RenderController : public IController {
    public:
        RenderController(const Engine& engine) : _engine(engine), _frameIndex(0) {}
        virtual ~RenderController() {}

        virtual retval<void> execute() {            
            std::unique_lock lock(_drawMtx);
            /*swap();
            current().commit();
           
            // only 1 thread at the moment...
            auto& frame = current().opaque();
            {
                _tasks.run([&]() {
                    auto list = _device.createCommandList();

                    while(!frame.end()) {
                        auto list = frame.next();

                        for(auto& drawable : list) {
                            draw(list, drawable);
                        }

                        if(shouldSubmit(list)) {
                            submit(list);
                        }
                    }
                    submit(list);                                    
                });
            }        */   
            

           return success();      
        }

        virtual retval<void> draw(DrawFrame& frame) {
            std::unique_lock lock(_submitMtx);
           // next() = frame;

           return success();
        }
        
        virtual retval<void> draw(gfx::ICommandList& list, Drawable& drawable) {
            //drawable.draw(list);          

           return success();  
        }

        virtual retval<void> submit(gfx::ICommandList& list) {
           // _queue.executeCommandLists({list});

           return success();
        }

        bool_t shouldSubmit(gfx::ICommandList& list) {
            // submitting list after every state change
            return true;
        }

        DrawFrame& current() {
            return _frame[_frameIndex];
        }

        DrawFrame& next() {                  
            return _frame[1 - _frameIndex];
        }

        const Engine& engine() {
            return _engine;
        }
    protected:
        void swap() {
            std::unique_lock lock(_submitMtx);
            _frameIndex = 1 - _frameIndex;
        }

        const Engine&           _engine;
        DrawFrame               _frame[2];
        size_t                  _frameIndex;
        //TaskPool                _tasks;
        std::mutex              _submitMtx;
        std::mutex              _drawMtx;

        //gfx::IDevice&            _device;
        //gfx::IRenderContext&     _context;
        //gfx::ICommandQueue&      _queue;
    };
}



