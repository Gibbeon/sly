#pragma once

#include "sly/global.h"
#include "sly/kernel.h"
#include "sly/runtime/activator.h"
#include "sly/builders/enginebuilder.h"
#include "sly/resources/resourcesystem.h"

//#include "sly/signal.h"
//#include "sly/task.h"
//#include "sly/taskpool.h"
//#include "sly/drawframe.h"

//#include "sly/scene.h"





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
    ENUM_DECL(eEngineState,
        eEngineState_Input,
        eEngineState_Update,
        eEngineState_Notify,
        eEngineState_Render,
        eEngineState_Present,
        eEngineState_Size
    );

    //class Scene;
    class InputController;;
    class RenderController;
    class Engine {
    public:        
        Engine(Kernel& kernel = Kernel::get());
        virtual ~Engine();
        
        Engine( Engine const& )              = delete;
        Engine( Engine && )                  = delete;
        Engine& operator = ( Engine const& ) = delete;
        Engine& operator = ( Engine && )     = delete;

        virtual retval<void> init(const EngineDesc& desc = EngineBuilder().build());
        virtual retval<void> release();

        virtual Kernel& kernel() const;
        virtual ResourceSystem& resources() const;
        //virtual GraphicsSystem& graphics() const;

        virtual InputController&         input() const; 
        virtual RenderController&        graphics() const;   
        virtual Activator&               activator() const;

        retval<void>    update();
        retval<void>    draw();
        bool_t          ready();   

    protected:
        virtual retval<void> setupTasks();
    
    private:
        Kernel&                     _kernel;

        //Task                        _gameCtrl;
        //Task                         _renderCtrl;
        //Semaphore                   isFrameReady; 
        //Signal                      _gfxsignal;
        //Signal                      _signals    [eEngineState_Size];
        //std::vector<Task*>          _stateCtrls [eEngineState_Size];       
        //Task                        _controllers[eEngineTask_Size];
    };
}



