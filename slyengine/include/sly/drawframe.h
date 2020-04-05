#pragma once

#include "sly/global.h"
#include "sly/gfx.h"
#include "sly/entity.h"
#include "sly/drawable.h"

namespace sly { 

    class DrawFrame {
    public:      
        retval<void>    reset();
        retval<void>    commit();

        //Iterator       opaque();
        //Iterator       alpha();

        std::vector<Entity*>&   entities() const;
        std::vector<Drawable>&  drawables() const;
    };

    /*class DrawFrameSegment;
    class DrawFrame {
        retval<void> reset();
        
        retval<void> commit() {
            _drawables.reserve(_entities.size());
            
            for(auto& entity: _entities) {
                _drawables.push_back(entity->drawable());
            }
        }
        
        DrawFrameSegment opaque() {
            DrawFrameSegment result;
            for(auto& drawable : _drawables) {
                if(std::find_if(   drawable.materials().begin(), 
                                    drawable.materials().end(),
                                    [] (const gfx::Material& mat) {
                                        return !mat.isAlphaBlendEnabled(); 
                                    }) != drawable.materials().end()) {
                    result.add(drawable);
                }
            }
            result.sort();
            return result;
        }

        DrawFrameSegment alpha() {
            DrawFrameSegment result;
            for(auto& drawable : _drawables) {
                if(std::find_if(   drawable.materials().begin(), 
                                    drawable.materials().end(),
                                    [] (const gfx::IMaterial& mat) {
                                        return mat.isAlphaBlendEnabled(); 
                                    }) != drawable.materials().end()) {
                    result.add(drawable);
                }
            }
            return result;
        }

        std::vector<Entity*>&   entities() const;
        std::vector<Drawable>&  drawables() const;

    private:
        std::vector<Entity*>    _entities;
        std::vector<Drawable>   _drawables;
    };

    class DrawFrameSegment {
    public:
        DrawFrameSegment() : _compare(&compareImpl), _index(0) {

        }

        gsl::span<Drawable* const> drawables() {
            return _drawables;
        }

        bool_t end() {
            return _index >= _drawables.size();
        }

        gsl::span<Drawable* const> next() {
            size_t start = _index;
            Drawable* begin = &(_drawables.data()[start]);
            Drawable* end   = _drawables.data();

            while(_index++) {
                if(_index >= _drawables.size()) break;
                if(!_compare(begin, &(end[_index])) break;
            }

            return gsl::make_span(begin, &(end[_index]));
        }

        retval<void> sort() {
            std::sort(_drawables.begin(), _drawables.end(), _compare);
        }

    protected:
        size_t _index;
        std::vector<Drawable*>                                          _drawables;
        std::function<bool_t(const Drawable* rhs, const Drawable* lhs)> _compare;

        static bool_t compareImpl(const Drawable* rhs, const Drawable* lhs) {
            if(shadersChange(rhs->materials(), lhs->materials()) return true;
        }

        static bool_t shadersChange(gsl::span<const gfx::Material*>& rhs, gsl::span<const gfx::Material*> lhs) {
            if(rhs.size() == lhs.size()) {
                for(size_t index; index < rhs.size(); index ++) {
                    if(rhs[index] != lhs[index]) return true;
                }
                return false;
            }
            return true
        }
    };*/
}



