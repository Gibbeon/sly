#pragma once

#include <glm/glm.hpp>

#include "sly/global.h"

using namespace glm;

namespace sly {

    template<typename T = int_t>
    class point_t : vec<2, T> {
    public:
        T x_value() const {
            return x;
        }

        T y_value() const {
            return y;
        }
        
        T distance_squared(point_t<T> other) const {
            return
            (x_value() - other->x_value()) * (x_value() - other->x_value()) +
            (y_value() - other->y_value()) * (y_value() - other->y_value());          
        }
        
        T distance(point_t<T> other) const {
            return ::sqrt(distance_squared());         
        }
    };
    template<typename T>
    class rect_t;


    template<typename T = real_t>
    class circle_t : vec<1, T> {
    public:
        bool_t contains(point_t<T> pt) {
            return (_center.distance_squared(pt) <= (radius_squared()));        
        }

        bool_t contains(circle_t<T> circle) {
            return (_center.distance_squared(circle.center()) <= (radius_squared() + circle.radius_squared()));        
        }

        bool_t contains(rect_t<T> rect) {
            return  (this->left() <= rect->left() &&
                     this->top() <= rect->top() &&
                     this->right() >= rect->right() &&
                     this->bottom() >= rect->bottom());
        }

        T radius() const {
            return x;
        }

        T radius_squared() const {
            return x * x;
        }

        point_t<T> center() const {
            return _center;
        }
        
        point_t<T> top() const {
            return point_t<T>(_center.x_value(), _center.y_value() + radius);
        }

        point_t<T> bottom() const {
            return point_t<T>(_center.x_value(), _center.y_value() - radius);
        }

        point_t<T> left() const {
            return point_t<T>(_center.x_value() - radius, _center.y_value());
        }

        point_t<T> right() const {
            return point_t<T>(_center.x_value() + radius, _center.y_value());
        }

    protected:
        point_t<T> _center;
    };

    template<typename T = real_t>
    class rect_t : vec<4, T>, public sly::ISerializable {
    public:
        SLY_TYPEINFO;

        virtual sly::retval<void> serialize(sly::ISerializer& archive) {
            return success(); 
        }

        virtual sly::retval<void> deserialize(sly::IDeserializer& archive) { 
            DESERIALIZE("left", x, 0);
            DESERIALIZE("top", y, 0);
            DESERIALIZE("width", z, 0);
            DESERIALIZE("height", w, 0);
            return success();            
        }
        rect_t() {}
        
        rect_t(T left,T top,T width,T height) {
            x = left;
            y = top;
            z = width;
            w = height;
        }

        bool_t contains(point_t<T> pt) {
            return  left() <= pt.x_value() && 
                    right() >= pt.x_value() && 
                    top() <= pt.y_value() && 
                    bottom() >= pt.y_value(); 
        }

        bool_t contains(rect_t<T> rect) {
            return  (this->left() <= rect->left() &&
                     this->top() <= rect->top() &&
                     this->right() >= rect->right() &&
                     this->bottom() >= rect->bottom());
        }

        bool_t contains(circle_t<T> circle) {
            return  (this->left() <= circle->left() &&
                     this->top() <= circle->top() &&
                     this->right() >= circle->right() &&
                     this->bottom() >= circle->bottom());
        }

        bool_t intersect(rect_t<T> rect) {
            return  contains(rect.top_left()) || 
                    contains(rect.top_right()) || 
                    contains(rect.bottom_left()) || 
                    contains(rect.bottom_right()) ||  
                    contains(rect) ||
                    rect.contains(*this);                  
        }

        bool_t intersect(circle_t<T> circle) {
            return                  
        }

        point_t<T> top_left() const {
            return point_t<T>(left(), top());
        }

        point_t<T> top_right() const {
            return point_t<T>(right(), top());
        }

        point_t<T> bottom_left() const {
            return point_t<T>(left(), bottom());
        }

        point_t<T> bottom_right() const {
            return point_t<T>(right(), bottom());
        }

        point_t<T> center() const {
            return point_t<T>(right() - left(), bottom() - top());
        }

        T left() const {
            return x;
        }

        T top() const {
            return y;
        }

        T width() const {
            return z;
        }

        T height() const {
            return w;
        }

        T right() const {
            return left() + width();
        }

        T bottom() const {
            return top() + height();
        }
    };
}
