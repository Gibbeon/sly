#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include "sly/global.h"

using namespace glm;

namespace sly { 
    
    class Spatial {
    public:
        Spatial() : Spatial(vec3(0.0), vec3(1.0), quat(vec3(0.0))) {

        }

        Spatial(mat4& matrix) {
            glm::mat4 transformation; // your transformation matrix.
            glm::vec3 scale;
            glm::quat rotation;
            glm::vec3 translation;
            glm::vec3 skew;
            glm::vec4 perspective;
            glm::decompose(transformation, scale, rotation, translation, skew, perspective);

            setPosition(translation);
            setRotation(rotation);
            setScale(scale);
        }

        Spatial(vec3 position, vec3 scale, quat rotation) : _position(position), _scale(scale), _rotation(rotation), _updated(TRUE) {
            
        }

        vec3 position() const {
            return _position;
        }

        vec3 scale() const {
            return _scale;
        }

        quat rotation() const {
            return _rotation;
        }

        Spatial& translate(const vec3 vector) {
            _position += vector; _updated = TRUE; return *this;
        }

        Spatial& scale(const vec3 vector){
            _scale *= vector; _updated = TRUE; return *this;
        }

        Spatial& scale(const real_t value){
            _scale *= value; _updated = TRUE; return *this;
        }

        Spatial& rotate(const quat rotation){
            _rotation *= rotation; _updated = TRUE; return *this;
        }

        Spatial& setPosition(const vec3 vector){
            _position += vector; _updated = TRUE; return *this;
        }

        Spatial& setScale(const vec3 vector){
            _scale = vector; _updated = TRUE; return *this;
        }

        Spatial& setScale(const float value){
            _scale = vec3(value); _updated = TRUE; return *this;
        }

        Spatial& setRotation(const quat rotation){
            _rotation = rotation; _updated = TRUE; return *this;
        }

        const real_t* ptr() {
            return glm::value_ptr(latest());
        }

        mat4& matrix() {
            return latest();
        }

        bool_t updated() const {
            return _updated;
        }

        operator mat4&() { return latest(); }
        operator const real_t*() { return ptr(); }

    protected:
        mat4 _local;
        vec3 _position;
        vec3 _scale;
        quat _rotation;

        bool_t _updated;

        mat4& latest() {
            if(_updated) {    
                _local = glm::translate(mat4(1.0), _position) * glm::mat4_cast(_rotation) * glm::scale(mat4(1.0), _scale);
                _updated = false;
            }
            return _local;
        }
    };
}



