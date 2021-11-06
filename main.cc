#include "application.h"

int main( int argc, char** argv ){
  app application( argc, argv );

  while( application.mainLoop() ){
    // nothing, yet
  }

  return 0;
}
