#ifndef SDF
#define SDF

#include "vector.h"
#include <cmath>

// base class
class SDFBase {
public:
  virtual float distance( vector2< float > p ) { return 1.0f; }
};

// each of the inherited classes will need to do the following:
  // provide a constructor
  // overload the distance query function

class circle : public SDFBase {
public:
  circle( vector2< float > pos, float r ) : position( pos ), radius( r ) {}
  float distance( vector2< float > p );
private:
  vector2< float > position;
  float radius;
};

class lineSegment : public SDFBase {
public:
  lineSegment( vector2< float > p1, vector2< float > p2, float r ) : position1( p1 ), position2( p2 ), radius( r ) {}
  float distance( vector2< float > p );
private:
  vector2< float > position1;
  vector2< float > position2;
  float radius;
};

#endif
