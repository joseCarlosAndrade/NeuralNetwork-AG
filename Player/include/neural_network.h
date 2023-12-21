#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include <string>
#include <vector>
#include <memory>
#include <Eigen/Core> 
#include "MiniDNN.h" 


#include "util.h"
#include "type.h"
#include "typeEvolvable.h"
#include "TicTacToe.h"
#include "TwoPlayerGame.h"


typedef Eigen::MatrixXd Matrix;
typedef Eigen::VectorXd Vector;
using namespace MiniDNN;


// Function to serialize parameters and save to a text file
void serialize_parameters_txt(const std::string& filename, const std::vector<std::vector<Scalar>>& parameters);

// Function to deserialize parameters from a text file
void deserialize_parameters_txt(const std::string& filename, std::vector<std::vector<Scalar>>& parameters);

// Function to generate a neural network
void generate_RNN(Network & net, int num_layers, std::vector<int> & num_neurons);

// Function responsible for creating a vector of n neural networks 
std::vector<std::unique_ptr<Network>> generate_vector_RNN(int num_RNN, int num_layers, std::vector<int> &num_neurons);

// Function to print neural_network parameters 
void print_parameters(std::vector<std::vector<Scalar>> parameters);


typedef struct player_st PLAYER;

T * player_getType();
T_EVOL* player_getTypeEvolvable();

void player_erase(PLAYER **player_addr);


Network player_getElement(const PLAYER *player); // getX


// delete after
void * playerInitFunction(void **dataVec, const int vecSize);

#endif 
