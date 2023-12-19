#include "DenseNetwork.h"
#include <stdlib.h> 

using namespace std;

void print_parameters(vector<vector<Scalar>> parameters){
    for (size_t i = 0; i < parameters.size(); ++i) {
        // Access the parameters of the i-th layer
        // Iterate over parameters within the layer
        for (size_t j = 0; j < parameters[i].size(); ++j) {
                Scalar value = parameters[i][j];
                // Do something with the parameter_value, e.g., print it
                cout << "Layer " << i << ", Parameter " << j << ": " << value << endl;
        }
    }
}

int main() {
    srand(time(NULL));

    vector<int> layers = {2, 5, 3};
    DenseNetwork mlp = DenseNetwork(layers);
    DenseNetwork mlp2 = DenseNetwork(layers);

    VectorXd a(5);
    mlp.Predict(a); // COMO DAR O CAST?

    vector<vector<double>> parameters;

    parameters = mlp.GetParameters();
    print_parameters(parameters);

    parameters = mlp2.GetParameters();
    print_parameters(parameters);

    parameters = ((mlp + mlp2) * 10).GetParameters();
    print_parameters(parameters);
}