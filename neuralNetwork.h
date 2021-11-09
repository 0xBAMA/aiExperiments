#ifndef NNETWORK
#define NNETWORK

#include <vector>
#include <random>
#include <algorithm>
#include <iostream>

class layer;

class neuron{
public:
  float output = 0.;
  void computeOutput();

  layer* input;

  std::vector< float > weights;
  float bias;
};



class layer{
public:
  int size()      { return neurons.size(); }
  void init( int n );
  void setPrev( layer* p );

  void evaluate();
  float getOutput( int n ){ return neurons[ n ].output; }

  std::vector< neuron > neurons;
};



class neuralNetwork{
public:
  neuralNetwork();
  ~neuralNetwork(){}

  // visualize layer biases and weights
  void visualize();

  // load all layers from the file, intact
  void loadWeightsFromFile( std::string filename );

  // save all the layer weights + biases
  void saveWeightsToFile( std::string filename );

  // generate completely random weights and biases in the range [ -range, range ]
  void generateRandomWeights( float range );

  // adjust weights
  void weightBump( float bump );

  // update the input neurons (this is the first layer)
  void setInput( float minus90, float minus45, float zero, float plus45, float plus90, float speed, float rotation );

  // feed forward from the input, through the hidden layers, and produce an output
  void evaluate();

  // outputs
  float speedAdjust;
  float rotationAdjust;

  float speedAdjustScalar    = 0.5;
  float rotationAdjustScalar = 0.1;

private:
  std::vector< layer* > network;
};

#endif
