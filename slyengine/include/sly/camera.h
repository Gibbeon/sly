#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "sly/global.h"
#include "sly/gfx.h"
#include "sly/kernel.h"
#include "sly/builders/enginebuilder.h"
#include "sly/resources/resourcesystem.h"

using namespace glm;

namespace sly { 
    class Camera {
    public:
        Camera() {
            _ar = 4.0f / 3.0f;
            #ifdef GLM_FORCE_RADIANS
                _angle = 0.785398f; //45 degrees
            #else
                _angle = 45.0f; //45 degrees
            #endif
            _near = 0.1f;
            _far = 100.0f;
        }
        //Nothing to clean up

        //View settings
        void setCameraPos(const vec3& v) { _pos = v; }
        void setCameraFocus(const vec3& v) { _fp = v; }
        void setCameraUpVec(const vec3& v) { _up = v; }

        //Projection settings
        void setAspectRatio(const real_t ar) { _ar = ar; }
        void setViewAngle(const real_t a) { _angle = a; }
        void setNearClipDist(const real_t d) { _near = d; }
        void setFarClipDist(const real_t d) { _far = d; }

        //Get matrix data
        mat4 view() { return _view; }
        mat4 projection() { return _proj; }

    protected:
        //Create matrices
        void updateViewMatrix()         { _view = glm::lookAt(_pos, _fp, _up); }
        void updateProjectionMatrix()   { _proj = glm::perspective(_angle, _ar, _near, _far); }

        //View matrix variables
        vec3 _pos; ///< position of the camera
        vec3 _fp; ///< focal point of the camera
        vec3 _up; ///< the up direction for the camera

        //Projection matrix variables
        real_t _ar; ///< aspect ratio
        real_t _angle; ///< angle in radians
        real_t _near; ///< near clipping distance
        real_t _far; ///< far clipping distance

        //functional matrices
        mat4 _view; ///< View matrix for OpenGL
        mat4 _proj; ///< Projection matrix for OpenGL
    };
}



