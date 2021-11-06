#ifndef AGENT
#define AGENT

#include "sprite.h"
#include "track.h"

// simple wrapper for now, but will contain more logic
  // neural network graph
  // controls - how the sprite moves

class agent {
public:
  sprite mySprite;
  void setTrack( track* t ) { myTrack = t; }

private:
  track* myTrack = NULL;
};

#endif
