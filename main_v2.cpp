//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//#include<math.h>
// #include"../include/velha.h"
#include "velha.h"
// #include"../include/matrix_operations.h"

// C++ libraries

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <fstream>
#include <vector>
#include <memory>

// Required libraries for neural network manipulation
// #include "../include/neural_network.h"
#include "neural_network.h"
// Acho que não precisaria incluir
#include <Eigen/Core>
#include "MiniDNN.h"


typedef Eigen::MatrixXd Matrix;
typedef Eigen::VectorXd Vector;

using namespace MiniDNN;
using namespace std;


/* Versão 2 - Utilizar biblioteca específica de redes neurais para c++ (manter restante da ideia original):

1) duas redes neurais iniciais aleatorias

2) pegar a melhor das duas:
- criar duas redes a partir dessa
- mutar levemente uma das duas (para manter melhor individuo)

3) repetir processo

obs: fazer com que todas as redes neurais pensem que sao o X (1)
ou seja, quando forem O (-1) multiplicar a lista por *-1

*/


void load_params(std::vector<std::unique_ptr<Network>>& vec_net);
void play_round(Game*game, std::unique_ptr<Network>& network);
// void get_max_index(Matrix2Df*output, int indexes[9]);

int * PlaysInputs(Eigen::VectorXd *playsProbs) {
    Eigen::VectorXi indices = Eigen::VectorXi::LinSpaced(playsProbs->rows(), 0, playsProbs->rows() - 1);
    std::sort(indices.data(), indices.data() + indices.size(), [&playsProbs](int i, int j) { return (*playsProbs)(i, 0) < (*playsProbs)(j, 0); });
    return indices.data();
}

int main(int argc, char ** argv) {
    Eigen::VectorXd a = {2, 9, 4, -2, 0};
    int *order = PlaysInputs(&a);
    std::cout << a.rows() << endl;
    for(int i=0 ; i<a.rows() ; i++) {
        std::cout << order[i] << endl;
    }
}


void load_params(std::vector<std::unique_ptr<Network>>& vec_net) {

    std::string filenames[] = { "data/rnn_parameters_1.txt", "data/rnn_parameters_2.txt" };

    for (size_t i = 0; i < std::size(filenames); ++i) {
        std::ifstream file(filenames[i]);
        if (file.is_open()) {
            if (file.peek() != std::ifstream::traits_type::eof()) {
                std::vector<std::vector<Scalar>> loaded_parameters;
                deserialize_parameters_txt(filenames[i], loaded_parameters);
                if (i < vec_net.size()) {
                    // Carrega os parâmetros apenas se houver uma rede neural correspondente no vec_net
                    vec_net[i]->set_parameters(loaded_parameters);
                    std::cout << "Parâmetros carregados do arquivo '" << filenames[i] << "' para vec_net[" << i << "]." << std::endl;
                } else {
                    std::cerr << "Índice fora do alcance de vec_net" << std::endl;
                }
            } else {
                std::cerr << "O arquivo '" << filenames[i] << "' está vazio, não foi possível carregar os parametros" << std::endl;
            }
            file.close();

        } else {
            std::cerr << "Erro ao abrir o arquivo '" << filenames[i] << std::endl;
        }
    }
}



void play_round(Game*game, std::unique_ptr<Network>& network) {
    // float input [9] = get_board(game, 'f');

    //implement on game library a way of returning floats
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
    auto output =  network->predict(input);

    // gets the best options (sorts)
    int choose = 0;
    // print_matrix(output);

    // get_max_index(get_transposed(output), index_list);

    // Get the indices of the sorted elements
    Eigen::VectorXi indices = Eigen::VectorXi::LinSpaced(output.rows(), 0, output.rows() - 1);
    std::sort(indices.data(), indices.data() + indices.size(), [&output](int i, int j) {
        return output(i, 0) < output(j, 0);});

    // Print the results
    std::cout << "Matrix:\n" << output << "\n";
    std::cout << "Indices of Sorted Elements:\n" << indices << "\n";

    while (!put_piece(game, indices[choose++]))
    {
        printf("\nInvalid insertion.. \n");
    }
    printf("Piece inserted: %d\n,", indices[choose-1]);
    
}

// void get_max_index(Matrix2Df*output, int indexes[9]) {
//     // int indexes[9];
//     print_matrix(output);

//     for (int i = 0; i < 9; i ++) {
//         float max = 0;

//         for (int j = 0; j < 9; j++) {
//             if (output->_base_ptr[0][j] > max) {
//                 // printf("\ni %d ; j %d %f  %f\n", i, j, output->_base_ptr[0][j] , max);
//                 max = output->_base_ptr[0][j];
//                 indexes[i] = j;
                
//             }
//         }
//         output->_base_ptr[0][indexes[i]] = 0;

//         printf(" %d ", indexes[i]);
//     }

//     // return indexes;
// }