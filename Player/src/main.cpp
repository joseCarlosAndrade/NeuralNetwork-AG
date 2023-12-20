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

    vector<vector<double>> params = mlp.GetParameters();
    print_parameters(params);

    DenseNetwork mlp2 = DenseNetwork(mlp);
    for(int i=0 ; i<3 ; i++) {
        cout << mlp2.GetLayers()[i] << endl;
    }
    vector<vector<double>> params2 = mlp2.GetParameters();
    print_parameters(params2);

    cout << "end" << endl;

    return 0;
}



/* int main() {
    vector<int> layers = {1, 2, 4};
    Player *player = new Player();
    player->SetNetStructure(layers);
    vector<int> netStr = player->GetNetStructure();
    for(size_t i=0 ; i<netStr.size() ; i++) {
        cout << netStr[i] << endl;
    }

    vector<int> layers2 = {2, 3, 5};
    Player::SetNetStructure(layers2);
    vector<int> netStr2 = player->GetNetStructure();
    for(size_t i=0 ; i<netStr2.size() ; i++) {
        cout << netStr2[i] << endl;
    }
    return 0;
} */



/* class Teste : public TwoPlayerGame {
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

        Teste() : TwoPlayerGame(0, 0, 0, 0) {
            cout << "teste" << endl;
        }
        ~Teste() {

        }
};

class Teste2 : public Teste {
    public:
        Teste2() : Teste() {
            cout << "teste22222" << endl;
        }
        ~Teste2() {

        }
};

int main() {
    T *type = Player::GetType<Teste>();
    type_getPrintFunction(type)(NULL);
    
    type = Player::GetType<Teste2>();
    type_getPrintFunction(type)(NULL);
    return 0;
} */