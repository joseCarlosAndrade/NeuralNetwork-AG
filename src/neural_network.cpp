#include <Eigen/Core>
#include "MiniDNN.h"

#include "neural_network.h"

using namespace MiniDNN;
using namespace std;

typedef Eigen::MatrixXd Matrix;
typedef Eigen::VectorXd Vector;

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>

#define WRONG_MOVE_PENALTY 10
#define VICTORY_PREMIUM 15

struct player_st {
    Network net;
    int num_layers = 6;
    std::vector<int> num_neurons = {9,16,16,32,16,16,9};
};


PLAYER * player_create(const Network & net);
static void * playerCopyFunction(const void *data);

/*
static comparison funcaoEscrotaCompareFunction(const void *data1, const void *data2); // nao precisa
static void funcaoEscrotaPrintFunction(const void *data); // nao precisa
*/

static void playerEraseFunction(void **data_addr); 

static void * playerInitFunction(void **dataVec, const int vecSize);
static void playerEvaluateFunction(void **dataVec, const int vecSize, float *out_fitnesses);
static void * playerCrossoverFunction(const void *data1, const void *data2);
static void playerMutateFunction(void *data, const float mutation);


// Neural Network associated functions
void play_round(Game*game, std::unique_ptr<Network>& network);
void serialize_parameters_txt(const std::string& filename, const std::vector<std::vector<Scalar>>& parameters);
void deserialize_parameters_txt(const std::string& filename, std::vector<std::vector<Scalar>>& parameters);
void generate_RNN(Network & net,int num_layers, vector<int> & num_neurons);
vector<std::unique_ptr<Network>> generate_vector_RNN(int num_RNN, int num_layers, vector<int> &num_neurons);
void print_parameters(vector<vector<Scalar>> parameters);
void multiplyMatrixScalar(std::vector<std::vector<Scalar>>& matrix, Scalar scaleFactor);
std::vector<std::vector<Scalar>> sumVectorsElementWise(const std::vector<std::vector<Scalar>>& vec1, const std::vector<std::vector<Scalar>>& vec2);
void scaleAndAdd(std::vector<std::vector<Scalar>>& matrix, Scalar scaleFactor);


PLAYER * player_create(const Network & net) {
    PLAYER * player_created = (PLAYER *) malloc(1*sizeof(PLAYER));    // FREE MEMORY
    auto parameters = net.get_parameters();
    
    if(player_created == NULL) {
        return NULL;
    } // Trata falha no malloc
    
    int num_layers =  net.num_layers(); // Número de camadas ocultas
    auto layers = net.get_layers();
    std::vector<int> num_neurons;
    int i = 0;
    for (i = 0; i < num_layers; ++i) {
        // Access the parameters of the i-th layer
        num_neurons.push_back(layers[i]->in_size());
    }
    num_neurons.push_back(layers[i-1]->out_size());
    generate_RNN(player_created->net, num_layers, num_neurons);
    player_created->net.set_parameters(parameters); // VER SE É NECESSÁRIO
    return player_created;
}

static void * playerCopyFunction(const void *data) { // Ponteiro de struct PLAYER
    if(data == NULL) {
        return NULL;
    }
    PLAYER *player = (PLAYER *) data;
    PLAYER *playerCopy = player_create(player->net);
    //playerCopy->net.set_parameters(player->get_parameters()); // VER SE É NECESSÁRIO
    return playerCopy;
}

void player_erase(PLAYER **player_addr) {
    if(*player_addr != NULL) {
        free(*player_addr);
        *player_addr = NULL;
    }
}


static void * playerInitFunction(void **dataVec, const int vecSize) { 
    Network net;
    PLAYER *playerNew;
    generate_RNN(net, playerNew->num_layers, playerNew->num_neurons);
    if(dataVec == NULL) { //use net as it is
    }
    else {
        auto parameters = net.get_parameters();
        multiplyMatrixScalar(parameters, 0); // put zero the random value
        for(int i=0 ; i < vecSize ; i++) {
            PLAYER *player = (PLAYER *) dataVec[i];
            parameters = sumVectorsElementWise(player->net.get_parameters(), parameters);
        }
        // divide by vecSize
        multiplyMatrixScalar(parameters, vecSize);
        net.set_parameters(parameters);
    }

    playerNew = player_create(net);
    return playerNew;
}


static void playerEvaluateFunction(void **dataVec, const int vecSize, float *out_fitnesses){
    for(int i = 0; i < vecSize; i++){
        out_fitnesses[i] = 0;
    }
    for(int i=0 ; i<vecSize ; i++) {
        PLAYER *player1 = (PLAYER *) dataVec[i];
        for(int j = 0; j < vecSize; j++){
            PLAYER *player2 = (PLAYER *) dataVec[j];
            if(i != j){
                Game * game = initialize_game();
                print_board(game);
                int wrong_moves1 = 0;
                int wrong_moves2 = 0;
                while (game->game_status == ON) {
                    int pos;
                    if (game->player==P_1) wrong_moves1 += play_round(game, player1->net);
                    if (game->player==P_2) wrong_moves2 += play_round(game, player2->net);
                    check_game_state(game);
                    print_board(game);
                }
                char * p = "O X";
                printf("\nFinished! Game status: %d.\nCurrent player: %c\n", game->game_status, p[game->player*-1 + 1]);
                // OUTFITNESS ESTA INICIALIZADO?
                if(player1 == victory){
                    out_fitnesses[i] += VICTORY_PREMIUM;
                }else if (player1 == victory)
                {
                    out_fitnesses[j] += VICTORY_PREMIUM;
                }
                out_fitnesses[i] -= WRONG_MOVE_PENALTY * wrong_moves1;
                out_fitnesses[j] -= WRONG_MOVE_PENALTY * wrong_moves2;
            }
        }
    }
}




static void playerMutateFunction(void *data, const float mutation) {
    if(data == NULL) {
        return;
    }
    PLAYER *player = (PLAYER *) data;
    auto parameters = player->net.get_parameters();
    scaleAndAdd(parameters, mutation);
    player->net.set_parameters(parameters);
}


static void * playerCrossoverFunction(const void *data1, const void *data2) { // REVISAR TEORIA CROSS OVER
    PLAYER *player1 = (PLAYER *) data1;
    PLAYER *player2 = (PLAYER *) data2;
    Network sum_net = (player1->net + player2->net);
    auto parameters = sum_net.get_parameters();
    // divide by 2
    multiplyMatrixScalar(parameters, 0.5);
    sum_net.set_parameters(parameters);
    PLAYER *playerNew = player_create(sum_net);
    return playerNew;
    // Outra opção pegar 1 camada de um e 2 de outra
}


int play_round(Game*game, Network & network) {
    int nb_wrong_moves = 0;
    // get the inputs (board)
    Matrix input(9,1);
    for ( int i = 0; i < 9; i++) {
        input(i,0) = (float)game->board[i];
    }

    if (game->player == P_2) { // neural network will always play as X (player 1)
        for (int i = 0; i < 9; i ++) {
            input(i,0) *= -1;
        }
    }

    // *** Calcular output da rede para o input
    auto output =  network.predict(input);

    // gets the best options (sorts)
    int choose = 0;

    // Get the indices of the sorted elements
    Eigen::VectorXi indices = Eigen::VectorXi::LinSpaced(output.rows(), 0, output.rows() - 1);
    std::sort(indices.data(), indices.data() + indices.size(), [&output](int i, int j) {
        return output(i, 0) < output(j, 0);});

    // Print the results
    std::cout << "\n Player:" << game->player <<" just played \n";
    std::cout << "Indices of Sorted Elements:\n" << indices << "\n";

    while (!put_piece(game, indices[choose++]))
    {
        printf("\nInvalid insertion.. \n");
        nb_wrong_moves++;
    }
    printf("Piece inserted: %d\n,", indices[choose-1]);
    return nb_wrong_moves;
}


// Function to serialize parameters and save to a text file
void serialize_parameters_txt(const std::string& filename, const std::vector<std::vector<Scalar>>& parameters) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    // Write each layer's parameters
    for (const auto& layer : parameters) {
        // Write each parameter in the layer
        for (const auto& param : layer) {
            file << param << ' ';
        }
        file << '\n'; // Newline to separate layers
    }
    file.close();
}

// Function to deserialize parameters from a text file
void deserialize_parameters_txt(const std::string& filename, std::vector<std::vector<Scalar>>& parameters) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return;
    }
    // Read each layer's parameters
    parameters.clear();
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Scalar value;
        std::vector<Scalar> layer_params;
        while (iss >> value) {
            layer_params.push_back(value);
        }
        parameters.push_back(std::move(layer_params));
    }

    file.close();
}

// Function to generate a neural network
void generate_RNN(Network & net,int num_layers, vector<int> & num_neurons){
    int i = 0;
    for(i; i < num_layers - 1; i++){
        net.add_layer(new FullyConnected<ReLU>(num_neurons[i], num_neurons[i+1]));
    }
    net.add_layer(new FullyConnected<Softmax>(num_neurons[i], num_neurons[i+1]));
    net.init();
}

// vector<Network> generate_vector_RNN(int num_RNN, int num_layers, vector<int> & num_neurons){
//     vector<Network> vec_RNN;
//     for(int i = 0; i < num_RNN; i++){
//         Network net;
//         vec_RNN.push_back(net);
//         generate_RNN(vec_RNN.back(), num_layers, num_neurons);
//     }    
//     return vec_RNN;
// }


// Function responsible for creating a vector of n neural networks 
vector<std::unique_ptr<Network>> generate_vector_RNN(int num_RNN, int num_layers, vector<int> &num_neurons) {
    vector<std::unique_ptr<Network>> vec_RNN; 
    for (int i = 0; i < num_RNN; i++) {
        auto net = std::make_unique<Network>();
        vec_RNN.push_back(std::move(net));
        generate_RNN(*vec_RNN.back(), num_layers, num_neurons);
    }
    return vec_RNN;
}

// Function to print neural_network parameters 
void print_parameters(vector<vector<Scalar>> parameters){
    for (size_t i = 0; i < parameters.size(); ++i) {
        // Access the parameters of the i-th layer
        vector<Scalar>& layer_parameters = parameters[i];
        // Iterate over parameters within the layer
        for (size_t j = 0; j < layer_parameters.size(); ++j) {
                Scalar parameter_value = layer_parameters[j];
                // Do something with the parameter_value, e.g., print it
                std::cout << "Layer " << i << ", Parameter " << j << ": " << parameter_value << std::endl;
        }
    }
}




void scaleAndAdd(std::vector<std::vector<Scalar>>& matrix, Scalar scaleFactor) {
    for (auto& row : matrix) {
        for (auto& element : row) {
            element += element * scaleFactor;
        }
    }
}

void multiplyMatrixScalar(std::vector<std::vector<Scalar>>& matrix, Scalar scaleFactor) {
    for (auto& row : matrix) {
        for (auto& element : row) {
            element = element * scaleFactor;
        }
    }
}

// Function to sum two vectors of vectors element-wise
std::vector<std::vector<Scalar>> sumVectorsElementWise(const std::vector<std::vector<Scalar>>& vec1,
                                                      const std::vector<std::vector<Scalar>>& vec2) {
    // Check if the vectors have the same size
    if (vec1.size() != vec2.size() || (vec1.size() > 0 && vec1[0].size() != vec2[0].size())) {
        std::cerr << "Vectors must have the same size for element-wise addition." << std::endl;
        return {};
    }

    // Initialize the result vector with the same size as the input vectors
    std::vector<std::vector<Scalar>> result(vec1.size(), std::vector<Scalar>(vec1[0].size(), 0.0));

    // Perform element-wise addition
    for (std::size_t i = 0; i < vec1.size(); ++i) {
        for (std::size_t j = 0; j < vec1[0].size(); ++j) {
            result[i][j] = vec1[i][j] + vec2[i][j];
        }
    }

    return result;
}






// int main()
// {
//     // Set random seed and generate some data
//     std::srand(123);
//     // Predictors -- each column is an observation
//     Matrix x = Matrix::Random(400, 100);
//     // Response variables -- each column is an observation
//     Matrix y = Matrix::Random(2, 100);
//     // Construct a network object
//     Network net;
//     // (Optional) set callback function object
//     // VerboseCallback callback;
//     // net.set_callback(callback);
//     // Obtain prediction -- each column is an observation
//     // Matrix pred = net.predict(x);
//     vector<int> num_neurons = {1,2,1};
//     int num_layers = num_neurons.size() - 1;
//     int num_networks = 3;
//     // generate_RNN(net, 2, num_neurons);
//     auto vec_net = generate_vector_RNN(3, 2, num_neurons);
    
//     auto parameters1 = vec_net[0]->get_parameters();
//     auto parameters2 = vec_net[1]->get_parameters();
//     auto parameters3 = vec_net[2]->get_parameters();
//     cout<<"RNN1:"<<endl;
//     print_parameters(parameters1);
//     cout<<"RNN2:"<<endl;
//     print_parameters(parameters2);
//     cout<<"RNN3:"<<endl;
//         print_parameters(parameters3);

//     // Example: Save parameters to a text file
//     // serialize_parameters_txt("rnn_parameters.txt", parameters);

//     // // Example: Load parameters from a text file
//     // std::vector<std::vector<Scalar>> loaded_parameters;
//     // deserialize_parameters_txt("rnn_parameters.txt", loaded_parameters);
//     // net.set_parameters(loaded_parameters);

//     // parameters = net.get_parameters();
//     // print_parameters(parameters);

//     return 0;
// }

