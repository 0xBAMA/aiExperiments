#include "vector.h"
#include <cmath>

template <class T>
class SDF {
public:
    vector2<T> position;
    T scale;
   
    virtual T distance(vector2<T> p) {
        //....
        return 1.0f;
    }

};
template <class T>
class circle : public SDF<T> {
    using SDF<T>::distance;
public:
    circle<T>(vector2<T> pos, T s) {
        this->position = pos;
        this->scale = s;
    }

    T distance(vector2<T> p) {
        vector2<T> pos = this->position - p;
        return sqrt(pos.values[0] * pos.values[0] + pos.values[1] * pos.values[1]) - this->scale;
    }

};

template <class T>
class lineSegment : public SDF<T> {
    using SDF<T>::distance;
public:
    lineSegment<T>(vector2<T> pos, vector2<T> pos2, T s) {
        this->position = pos;
        position2 = pos2;
        this->scale = s;
    }

    T distance(vector2<T> p) {
        vector2<T> AP = p - this->position;
        vector2<T> AB = position2 - this->position;
        T mm = dot(AP, AB) / dot(AB,AB);
        mm = (mm > 1.0) ? 1.0 : (mm < 0.) ? 0.: mm;
        
        vector2<T> pos = (this->position + AB*mm) - p;

        return sqrt(pos.values[0] * pos.values[0] + pos.values[1] * pos.values[1]) - this->scale;
    }

private:
    vector2<T> position2;
};

