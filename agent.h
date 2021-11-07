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
  agent( std::string filename, track* t, SDL_Renderer* r, float scale, float rot, vector2< int >location );

  void update();
  void draw();
  void setTrack( track* t ) { myTrack = t; }

  float getRotation(){ return mySprite.getRotation(); }
  void setRotation( float set ){ mySprite.setRotation( set ); }
  void rotationAdjust( float adj ){ mySprite.setRotation( getRotation() + adj ); }


  void setPosition( vector2< float >newPos ){ mySprite.setPosition( { int( newPos.values[ 0 ] ), int( newPos.values[ 1 ] ) } ); }
  vector2< float > getPosition(){ return vector2< float >( mySprite.getPosition().values[ 0 ], mySprite.getPosition().values[ 1 ] ); }

  std::string getTag(){ return tag; }
  bool isDead(){ return dead; }

  void raymarchDistances();

  void toggleSelected(){ selected = !selected; }

private:
  float raymarchVector( vector2< float > origin, vector2< float > direction );
  float m90, m45, zero, p45, p90;
  float myD, speed;

  sprite mySprite;
  track* myTrack = NULL;
  neuralNetwork brain;
  std::string tag;

  bool selected       = false;
  bool dead           = false;
  int updatesSurvived = 0;
};

#endif
