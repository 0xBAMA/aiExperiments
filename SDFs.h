#include "vector.h"
#include <cmath>

class SDF {
public:
  virtual float distance( vector2< float > p ) {
    return 1.0f;
  }
};



class circle : public SDF {
public:
  circle( vector2< float > pos, float r ) {
    this->position = pos;
    this->radius = r;
  }

  float distance( vector2< float > p ) {
    vector2< float > pos = this->position - p;
    return sqrt( pos.values[ 0 ] * pos.values[ 0 ] + pos.values[ 1 ] * pos.values[ 1 ] ) - this->scale;
  }

private:
  vector2< float > position;
  float radius;
};



class lineSegment : public SDF {
public:
  lineSegment( vector2< float > pos, vector2< float > pos2, float s ) {
    this->position = pos;
    position2 = pos2;
    this->scale = s;
  }

  float distance( vector2< float > p ) {
    vector2< float > AP = p - this->position;
    vector2< float > AB = position2 - this->position;
    float mm = dot(AP, AB) / dot(AB,AB);
    mm = ( mm > 1.0 ) ? 1.0 : ( mm < 0. ) ? 0.: mm;

    vector2< float > pos = ( this->position + AB * mm ) - p;
    return sqrt( pos.values[ 0 ] * pos.values[ 0 ] + pos.values[ 1 ] * pos.values[ 1 ] ) - this->scale;
  }

private:
  vector2< float > position2;
};
