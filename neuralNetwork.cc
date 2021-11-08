#include "neuralNetwork.h"

void neuron::computeOutput(){
  float sum = 0.0f; // compute the weighted sum
  for( int i = 0; i < input->size(); i++ )
    sum += input->getOutput( i ) * weights[ i ];
  output = sum + bias; // add bias + store output
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

  layer * hidden3 = new layer();
  hidden3->init( 4 );
  hidden3->setPrev( hidden2 );
  network.push_back( hidden3 );

  layer * hidden4 = new layer();
  hidden4->init( 4 );
  hidden4->setPrev( hidden3 );
  network.push_back( hidden4 );

  layer * output = new layer();
  output->init( 2 );
  output->setPrev( hidden4 );
  network.push_back( output );

  generateRandomWeights( 0.1 );
  // visualize();
}

void neuralNetwork::evaluate(){
  // propagate forwards - input to first hidden layer, first to second, etc
  for( int i = 1; i < 6; i++ )
    network[ i ]->evaluate(); // evaluate, in order - start at 1, because 0 contains the input

  // put the output of the final layer into these publicly accessible floats
  speedAdjust =    std::clamp( network[ 5 ]->getOutput( 0 ), -1.0f * adjustScalar, 1.0f * adjustScalar );
  rotationAdjust = std::clamp( network[ 5 ]->getOutput( 1 ), -1.0f * adjustScalar, 1.0f * adjustScalar );
}

void neuralNetwork::generateRandomWeights( float range ){
  // seeding the PRNG
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution< float > d( -range, range );
  for( int i = 1; i < 6; i++ ){
    for( int j = 0; j < network[ i ]->size(); j++ ){
      network[ i ]->neurons[ j ].bias = d( gen );
      for( int k = 0; k < network[ i - 1 ]->size(); k++){
        network[ i ]->neurons[ j ].weights[ k ] = d( gen );
      }
    }
  }
}

void neuralNetwork::visualize(){
  for( int i = 1; i < 6; i++ ){
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

void saveWeightsToFile( std::string filename ){
  // encode as json
}

void loadWeightsFromFile( std::string filename ){
  // load from json
}

void weightBump( float bump ){
  // take existing weights and add a random quantity in the range [ -bump, bump ]
}

void setInput( float minus90, float minus45, float zero, float plus45, float plus90, float speed, float rotation ){
  // store these 7 values in the output fields of the 7 neurons in the input layer
}
