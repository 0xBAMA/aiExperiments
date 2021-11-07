#ifndef NNETWORK
#define NNETWORK

#include <vector>

class edge; // forward declare

class node{
public:
  node() {}
  ~node() {}

  void setValue( float v ) { value = v; }
  float getValue()         { return value; }

private:
  float value;
};

class edge{
public:
  edge() {}
  ~edge() {}

  void setWeight( float w ) { weight = w; }
  float getWeight( )        { return weight; }

private:
  float weight;
  node* sourceNode;  // source of directed link
  node* targetNode; // destination of link
};

class neuralNetwork{
public:
  neuralNetwork() {}
  ~neuralNetwork() {}

  void setInput( float minus90, float minus45, float zero, float plus45, float plus90 ) { /* to do - this is updating the input neuron */ }

private:
  std::vector< node > neurons;
  std::vector< edge > connections;
};

#endif
