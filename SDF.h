#ifndef SDF
#define SDF

#include "vector.h"
#include <cmath>

// base class
class SDF {
public:
  virtual float distance( vector2< float > p ) { return 1.0f; }
};

// each of the inherited classes will need to do the following:
  // provide a constructor
  // overload the distance query function

class circle : public SDF {
public:
  circle( vector2< float > pos, float r );
  float distance( vector2< float > p );
private:
  vector2< float > position;
  float radius;
};

class lineSegment : public SDF {
public:
  lineSegment( vector2< float > pos, vector2< float > pos2, float s );
  float distance( vector2< float > p );
private:
  vector2< float > position2;
  float scale;
};

#endif
