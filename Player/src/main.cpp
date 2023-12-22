#include "DenseNetwork.h"
#include "Player.h"
#include "TwoPlayerGame.h"
#include "TicTacToe.h"
#include <stdlib.h> 

using namespace std;

void print_parameters(vector<vector<Scalar>> parameters){
    cout << parameters.size() << endl;
    for (size_t i = 0; i < parameters.size(); ++i) {
        cout << parameters[i].size() << endl;
        for (size_t j = 0; j < parameters[i].size(); ++j) {
                Scalar value = parameters[i][j];
                cout << "Layer " << i << ", Parameter " << j << ": " << value << endl;
        }
    }
}

int main() {
    srand(time(NULL));

    vector<int> layers = {2, 5, 3};
    DenseNetwork mlp = DenseNetwork(layers);
    DenseNetwork mlp2 = DenseNetwork(layers);

    vector<vector<double>> parameters;

    parameters = mlp.GetParameters();
    print_parameters(parameters);

    parameters = mlp2.GetParameters();
    print_parameters(parameters);

    parameters = ((mlp + mlp2) * 10).GetParameters();
    print_parameters(parameters);
}