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

/* int main() {
    srand(time(NULL));

    vector<int> layers = {2, 5, 3};
    DenseNetwork mlp = DenseNetwork(layers);
    DenseNetwork mlp2 = DenseNetwork(layers);

    vector<vector<double>> parameters;

    parameters = mlp.GetParameters();
    print_parameters(parameters);

    parameters = mlp2.GetParameters();
    print_parameters(parameters);

    mlp += mlp2;
    mlp *= 10;
    parameters = mlp.GetParameters();
    print_parameters(parameters);
} */

class Teste : public TwoPlayerGame {
    public:
        bool IsSpaceValid(int input) {
            return true;
        }
        void PutPiece(int input) {

        }
        game_status CheckGameStatus() {
            return TIE;
        }
        void PrintBoard() {

        }
        VectorXd GetGameState() {
            return VectorXd(2);
        }

        Teste() : TwoPlayerGame(0, 0, 3, 3) {
            cout << "teste" << endl;
        }
        ~Teste() {

        }
};

int main() {
    srand(time(NULL));
    
    vector<int> layers = {3, 2, 3};
    Player<Teste>::SetNetStructure(layers);

    vector<int> tet = Player<TicTacToe>::GetNetStructure();
    cout << tet.size() << endl;

    layers = {9, 2, 3, 5, 9};
    Player<TicTacToe>::SetNetStructure(layers);
    cout << Player<TicTacToe>::GetNetStructure().size() << endl;

    cout << Player<Teste>::GetNetStructure().size() << endl;

    T *type = Player<Teste>::GetType();
    Player<Teste> *player1 = new Player<Teste>();
    Player<Teste> *player2 = new Player<Teste>();

    Player<Teste> *player1Copy = (Player<Teste> *) type_getCopyFunction(type)(player1);

    vector<vector<double>> parameters;
    parameters = player1->GetAI()->GetParameters();
    print_parameters(parameters);

    parameters = player2->GetAI()->GetParameters();
    print_parameters(parameters);

    parameters = player1Copy->GetAI()->GetParameters();
    print_parameters(parameters);

    return 0;
}