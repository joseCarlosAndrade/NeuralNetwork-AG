#include "DenseNetwork.h"

using namespace std;

void print_parameters(vector<vector<Scalar>> parameters){
    for (size_t i = 0; i < parameters.size(); ++i) {
        // Access the parameters of the i-th layer
        // Iterate over parameters within the layer
        for (size_t j = 0; j < parameters[i].size(); ++j) {
                Scalar value = parameters[i][j];
                // Do something with the parameter_value, e.g., print it
                std::cout << "Layer " << i << ", Parameter " << j << ": " << value << std::endl;
        }
    }
}

int main() {
    vector<int> layers = {2, 5, 3};
    DenseNetwork mlp = DenseNetwork(layers);
    DenseNetwork mlp2 = DenseNetwork(layers);\

    DenseNetwork ko = DenseNetwork(DenseNetwork::LoadFrom("hey"));

    vector<vector<double>> parameters;

    parameters = mlp.GetParameters();
    print_parameters(parameters);

    parameters = mlp2.GetParameters();
    print_parameters(parameters);

    parameters = ((mlp + mlp2) * 10).GetParameters();
    print_parameters(parameters);
}