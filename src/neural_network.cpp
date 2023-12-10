#include <Eigen/Core>
#include "MiniDNN.h"

using namespace MiniDNN;
using namespace std;

typedef Eigen::MatrixXd Matrix;
typedef Eigen::VectorXd Vector;

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>

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

