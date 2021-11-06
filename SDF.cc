#include "SDF.h"

circle::circle( vector2< float > pos, float r ){
  this->position = pos;
  this->radius = r;
}

float circle::distance( vector2< float > p ){
  vector2< float > pos = this->position - p;
  return sqrt( pos.values[ 0 ] * pos.values[ 0 ] + pos.values[ 1 ] * pos.values[ 1 ] ) - this->scale;
}

lineSegment::lineSegment( vector2< float > p1, vector2< float > p2, float s ){
  this->position = p1;
  position2 = p2;
  this->scale = s;
}

float lineSegment::distance( vector2< float > p ){
  vector2< float > AP = p - this->position;
  vector2< float > AB = position2 - this->position;
  float mm = dot(AP, AB) / dot(AB,AB);
  mm = ( mm > 1.0 ) ? 1.0 : ( mm < 0. ) ? 0.: mm;

  vector2< float > pos = ( this->position + AB * mm ) - p;
  return sqrt( pos.values[ 0 ] * pos.values[ 0 ] + pos.values[ 1 ] * pos.values[ 1 ] ) - this->scale;
}
