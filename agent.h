#ifndef AGENT
#define AGENT

#include "sprite.h"
#include "track.h"
#include "neuralNetwork.h"

// simple wrapper for now, but will contain more logic
  // neural network graph
  // controls - how the sprite moves

class agent {
public:
  sprite mySprite;

  void update();
  void draw();
  void setTrack( track* t ) { myTrack = t; }

  float getRotation(){ return mySprite.getRotation(); }
  void setRotation( float set ){ mySprite.setRotation( set ); }
  void rotationAdjust( float adj ){ mySprite.setRotation( getRotation() + adj ); }


  void setPosition( vector2< float >newPos ){ mySprite.setPosition( { int( newPos.values[ 0 ] ), int( newPos.values[ 1 ] ) } ); }
  vector2< float > getPosition(){ return vector2< float >( mySprite.getPosition().values[ 0 ], mySprite.getPosition().values[ 1 ] ); }

  void raymarchDistances();

  void toggleSelected(){ selected = !selected; }

private:
  float raymarchVector( vector2< float > origin, vector2< float > direction );
  float m90, m45, zero, p45, p90;
  float myD, speed;

  track* myTrack = NULL;
  neuralNetwork brain;

  bool selected = false;
};

#endif
