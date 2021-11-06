#ifndef SDF
#define SDF

#include "vector.h"
#include <cmath>

// base class
class SDFBase {
public:
  virtual float distance( vector2< float > p ) { return 1.0f; }
  virtual ~SDFBase() {}
};

// each of the inherited classes will need to do the following:
  // provide a constructor
  // overload the distance query function

class circle : public SDFBase {
public:
  circle( vector2< float > pos, float r, bool n ) : position( pos ), radius( r ), negate( n ) {}
  float distance( vector2< float > p );
private:
  vector2< float > position;
  float radius;
  bool negate;
};

class lineSegment : public SDFBase {
public:
  lineSegment( vector2< float > p1, vector2< float > p2, float r, bool n ) : position1( p1 ), position2( p2 ), radius( r ), negate( n ) {}
  float distance( vector2< float > p );
private:
  vector2< float > position1;
  vector2< float > position2;
  float radius;
  bool negate;
};

#endif
