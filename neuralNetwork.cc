#include "neuralNetwork.h"

void neuron::computeOutput(){
  float sum = 0.0f; // compute the weighted sum
  for( int i = 0; i < input->size(); i++ )
    sum += input->getOutput( i ) * weights[ i ];

  output = sum + bias; // raw output
  // output = 1. / ( 1 + exp( -1. * ( sum + bias ) ) ); // sigmoid
  // output = std::max( 0.f, sum + bias ); // rectified linear

}

void layer::init( int n ){
  neurons.resize( n );
}

void layer::setPrev( layer* p ){
  for( auto& neuron : neurons){
    neuron.input = p;
    neuron.weights.resize( p == nullptr ? 0 : p->size() );
  }
}

void layer::evaluate(){
  for( auto& neuron : neurons )
    neuron.computeOutput();
}

neuralNetwork::neuralNetwork(){
  layer * inputs = new layer();
  inputs->init( 7 );
  inputs->setPrev( nullptr );
  network.push_back( inputs );

  layer * hidden1 = new layer();
  hidden1->init( 4 );
  hidden1->setPrev( inputs );
  network.push_back( hidden1 );

  layer * hidden2 = new layer();
  hidden2->init( 4 );
  hidden2->setPrev( hidden1 );
  network.push_back( hidden2 );

  // layer * hidden3 = new layer();
  // hidden3->init( 4 );
  // hidden3->setPrev( hidden2 );
  // network.push_back( hidden3 );
  //
  // layer * hidden4 = new layer();
  // hidden4->init( 4 );
  // hidden4->setPrev( hidden3 );
  // network.push_back( hidden4 );

  layer * output = new layer();
  output->init( 2 );
  output->setPrev( hidden2 );
  network.push_back( output );

  generateRandomWeights( 0.05f );
  // visualize();
}

void neuralNetwork::evaluate(){
  // propagate forwards - input to first hidden layer, first to second, etc
  for( unsigned int i = 1; i < network.size(); i++ )
    network[ i ]->evaluate(); // evaluate, in order - start at 1, because 0 contains the input

  // put the output of the final layer into these publicly accessible floats
  // speedAdjust =    std::clamp( network[ network.size() - 1 ]->getOutput( 0 ) - network[ network.size() - 1 ]->getOutput( 2 ), -1.0f * speedAdjustScalar,    1.0f * speedAdjustScalar );
  // rotationAdjust = std::clamp( network[ network.size() - 1 ]->getOutput( 1 ) - network[ network.size() - 1 ]->getOutput( 3 ), -1.0f * rotationAdjustScalar, 1.0f * rotationAdjustScalar );
  speedAdjust =    std::clamp( network[ network.size() - 1 ]->getOutput( 0 ), -1.0f * speedAdjustScalar,    1.0f * speedAdjustScalar );
  rotationAdjust = std::clamp( network[ network.size() - 1 ]->getOutput( 1 ), -1.0f * rotationAdjustScalar, 1.0f * rotationAdjustScalar );
}

void neuralNetwork::generateRandomWeights( float range ){
  // seeding the PRNG
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution< float > d( -range, range );
  for( unsigned int i = 1; i < network.size(); i++ ){
    for( int j = 0; j < network[ i ]->size(); j++ ){
      network[ i ]->neurons[ j ].bias = d( gen );
      for( int k = 0; k < network[ i - 1 ]->size(); k++){
        network[ i ]->neurons[ j ].weights[ k ] = d( gen );
      }
    }
  }
}

void neuralNetwork::visualize(){
  for( unsigned int i = 1; i < network.size(); i++ ){
    for( int j = 0; j < network[ i ]->size(); j++ ){
      std::cout << network[ i ]->neurons[ j ].bias << " : ";
      for( int k = 0; k < network[ i - 1 ]->size(); k++){
        std::cout << network[ i ]->neurons[ j ].weights[ k ] << " ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
  }
}

void neuralNetwork::saveWeightsToFile( std::string filename ){
  // encode as json
}

void neuralNetwork::loadWeightsFromFile( std::string filename ){
  // load from json
}

void neuralNetwork::weightBump( float bump ){
  // take existing weights and add a random quantity in the range [ -bump, bump ]
}

void neuralNetwork::setInput( float minus90, float minus45, float zero, float plus45, float plus90, float speed, float rotation ){
  // store these 7 values in the output fields of the 7 neurons in the input layer
  network[ 0 ] -> neurons[ 0 ].output = minus90;
  network[ 0 ] -> neurons[ 1 ].output = minus45;
  network[ 0 ] -> neurons[ 2 ].output = zero;
  network[ 0 ] -> neurons[ 3 ].output = plus45;
  network[ 0 ] -> neurons[ 4 ].output = plus90;
  network[ 0 ] -> neurons[ 5 ].output = speed;
  network[ 0 ] -> neurons[ 6 ].output = rotation;
}
