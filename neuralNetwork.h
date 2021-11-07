#ifndef NNETWORK
#define NNETWORK

#include <vector>

// class neuron{
// public:
//   std::vector< float > weights;
//
// };
//
// class layer{
// public:
//   int size(){ return weights.size(); }
//
// private:
//   layer* prevlayer;
//   std::vector< neuron > neurons;
//   float bias;
// };
//
class neuralNetwork{
// public:
//   neuralNetwork() {}
//   ~neuralNetwork() {}
//
//   // load all layers from the file, intact
//   void loadWeightsFromFile( std::string filename );
//
//   // save all the layer weights + biases
//   void saveWeightsToFile( std::string filename );
//
//   // randomize weights, biases with values in the range [ -bump, bump ]
//   void loadWeightsFromFileAndBump( std::string filename, float bump );
//
//   // generate completely random weights and biases in the range [ -range, range ]
//   void generateRandomWeights( float range );
//
//   // update the input neurons (this is the first layer)
//   void setInput( float minus90, float minus45, float zero, float plus45, float plus90, float speed ) {}
//
// private:
//   std::vector< layer > network;
};

#endif
