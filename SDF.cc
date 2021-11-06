#include "SDF.h"

float circle::distance( vector2< float > p ){
  return ( negate ? -1.0f : 1.0f ) * ( len( p - position ) - radius );
}

float lineSegment::distance( vector2< float > p ){
  vector2< float > AP = p - position1;
  vector2< float > AB = position2 - position1;
  float mm = dot(AP, AB) / dot(AB,AB);
  mm = ( mm > 1.0 ) ? 1.0 : ( mm < 0. ) ? 0.: mm;

  vector2< float > pos = ( position1 + AB * mm ) - p;
  return sqrt( pos.values[ 0 ] * pos.values[ 0 ] + pos.values[ 1 ] * pos.values[ 1 ] ) - radius;
}
