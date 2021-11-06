#include "application.h"

int main( int argc, char** argv ){
  // initialize the application
  app application( argc, argv );

  // run the main loop, until the function returns false
  while( application.mainLoop() );

  // end
  return 0;
}
