#pragma once

#include <vector>
#include <queue>
#include <functional>

#include "sly/global.h"
#include "sly/gfx.h"
#include <glm/matrix.hpp>
#include <glm/gtc/quaternion.hpp>

namespace sly {
    namespace gfx {

        class IHasSRT {
        public:
            virtual glm::mat4& getGlobalTransform() = 0;
            virtual glm::mat4& getLocalTransform() = 0;

            virtual bool_t isDirty() = 0;

            virtual void scale(glm::vec3 scale) = 0;
            virtual void transform(glm::vec3 transform) = 0;
            virtual void rotate(glm::quat rotate) = 0;
        };

        class LocalSRT : public IHasSRT {
        public:
            virtual glm::mat4& getGlobalTransform() {return _globalSRT; }
            virtual glm::mat4& getLocalTransform() {return _localSRT; }

            virtual bool_t isDirty() { return _isDirty; }

            void scale(glm::vec3 scale) {}
            void transform(glm::vec3 transform) {}
            void rotate(glm::quat rotate) {}

        private:
            glm::mat4 _localSRT;            
            glm::mat4 _globalSRT;
            bool_t _isDirty;
        };

        class Material {
        public:
            IRenderState& _state;
            std::vector<ITexture&> _textures;
        };

        class Mesh {
        public:
            //Mesh() : _srt(LocalSRT()) {}

        private:
            //IVertexBuffer& _vertex;
            //IIndexBuffer& _index;
            //Material& _material;

            //IHasSRT& _srt;
        };

        class Model {
        public:
        private:
            std::vector<Mesh> _meshes;

            IHasSRT& _localSrt;
            glm::mat4 _globalSrt;
        };

        class Entity {
        public:

        private:
            Entity& _parent;
            std::vector<Entity> _children;

            Model _model;

            glm::mat4 _localSrt;
            glm::mat4 _globalSrt;
        };

        class Camera {
        public:

        private:
            sly::gfx::Viewport _viewport;
            glm::mat4 _matrix;
        };

        class GameState : public IState {

        };

        class IState {
        public:
            virtual void init() = 0;
            virtual void update(real_t delta) = 0;
            virtual void draw() = 0;
            virtual void destroy() = 0;
        };

        class StateMachine {
        public:
            void setState(IState& state);
            IState& getState();
        private:
            IState& _current;
        };

        struct Message {
        public:
            size_t id;
            vptr_t data;
        };

        class Scene {
        public:
            virtual void processMessages(std::queue<Message>& messages); // input & network

            virtual void draw(Camera& camera, IRenderTarget& target);
        private:
            std::vector<Entity> _entities;
            std::vector<std::function<void(Scene&, real_t)>> _updateChain;
        };
    }
}