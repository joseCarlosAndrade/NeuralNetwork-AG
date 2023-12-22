#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"../include/velha.h"
#include"../include/matrix_operations.h"

/* PLANO 1 - mais simples ( 2 redes por rodada):
1) duas redes neurais iniciais aleatorias

2) pegar a melhor das duas:
- criar duas redes a partir dessa
- mutar levemente uma das duas (para manter melhor individuo)

3) repetir processo

obs: fazer com que todas as redes neurais pensem que sao o X (1)
ou seja, quando forem O (-1) multiplicar a lista por *-1

*/

#define EULER 2.71828
#define VERBOSE 1

struct _2layer_neural_network
{
    Matrix2Df *_input; // maybe this input/output is useless?
    Matrix2Df *_output;

    Matrix2Df * _weight_1;
    Matrix2Df * _weight_2;

    Matrix2Df * _bias_1;
    Matrix2Df * _bias_2;

    unsigned int generation;
};

typedef struct _2layer_neural_network NeuralNetwork2L;

NeuralNetwork2L * initialize_networks(int n);
Matrix2Df* calculate_output(NeuralNetwork2L * network, float vec_input[9], Matrix2Df*input);

void play_round(Game*game, NeuralNetwork2L*network);
void get_max_index(Matrix2Df*output, int indexes[9]);

int main(int argc, char ** argv) {

    NeuralNetwork2L * network_1 = initialize_networks(1);
    NeuralNetwork2L * network_2 = initialize_networks(2);

    // print_matrix(network_1->_weight_1);
    // print_matrix(network_2->_bias_1);

    // float input [9] = {0, 0, 0, 1, 0, 0, 0 ,0 ,0};

    // Matrix2Df*output = calculate_output(network_1, input, NULL);
    // print_matrix(output);

    Game * game = initialize_game();
    print_board(game);

    while (game->game_status == ON) {
        int pos;
        if (game->player==P_1) play_round(game, network_1);
        if (game->player==P_2) play_round(game, network_2);
        // else {
        //     scanf(" %d", &pos);
        //     while( !put_piece(game, pos) ) {
        //         printf("Position not valid. Try again. \n\n");
        //         scanf(" %d", &pos); 
        // }    
        // }

        check_game_state(game);
        if (VERBOSE)
        print_board(game);
    }

    char * p = "O X";
    printf("\nFinished! Game status: %d.\nCurrent player: %c\n", game->game_status, p[game->player*-1 + 1]);
    
}

NeuralNetwork2L* initialize_networks(int n) {
    NeuralNetwork2L *network = NULL;
    network = (NeuralNetwork2L*) calloc(1, sizeof(NeuralNetwork2L*));
    network->generation = 0;
    network->_input = create_matrix(9, 1);

    network->_weight_1 = create_matrix(9, 9);
    network->_weight_2 = create_matrix(9, 9);
    network->_bias_1 = create_matrix(9, 1);
    network->_bias_2 = create_matrix(9, 1);

    network->_output = create_matrix(9, 1);

    // if i you know a better way of doing this pls tell me i hate this
    if (n == 1) { 
        fill_matrix_from_file(network->_weight_1, "data/1_w1.txt");
        fill_matrix_from_file(network->_weight_2, "data/1_w2.txt");
        fill_matrix_from_file(network->_bias_1, "data/1_b1.txt");
        fill_matrix_from_file(network->_bias_1, "data/1_b2.txt");
    }
    else if (n==2) {
        fill_matrix_from_file(network->_weight_1, "data/2_w1.txt");
        fill_matrix_from_file(network->_weight_2, "data/2_w2.txt");
        fill_matrix_from_file(network->_bias_1, "data/2_b1.txt");
        fill_matrix_from_file(network->_bias_1, "data/2_b2.txt");
    }
    return network;

}

Matrix2Df* calculate_output(NeuralNetwork2L * network, float vec_input[9], Matrix2Df*mat_input) {
    Matrix2Df * layer1 = create_matrix(9, 1);
    // Z1 = w1*A0 + b1
    if (vec_input != NULL) {
        Matrix2Df*input = create_matrix(9, 1);
        fill_matrix(input, vec_input);
        layer1 = mult_matrix(network->_weight_1, input);
    } else {
        layer1 = mult_matrix(network->_weight_1, mat_input);
    }

    
    layer1 = add_matrix(layer1, network->_bias_1);

    // 1st activation function if x<=0 -> x=0
    for (int i = 0; i < 9; i++) {
        if (layer1->_base_ptr[i][0] <= 0) layer1->_base_ptr[i][0] = 0;
    }

    Matrix2Df * layer2 = create_matrix(9,1);
    // Z2 = w2*A1 + b2
    layer2 = mult_matrix(network->_weight_2, layer1);
    layer2 = add_matrix(layer2, network->_bias_2);

    // 2nd activation function
    Matrix2Df * output = create_matrix(9,1);
    float sum = 0;

    for (int i = 0; i < 9; i++) {
        sum += pow(EULER, layer2->_base_ptr[i][0]);
    }
    for (int i = 0; i < 9; i ++) {
        output->_base_ptr[i][0] = pow(EULER,layer2->_base_ptr[i][0]) / sum;
    }

    return output;
}


void play_round(Game*game, NeuralNetwork2L*network) {
    // float input [9] = get_board(game, 'f');

    //implement on game library a way of returning floats
    float input[9];
    for ( int i = 0; i < 9; i++) {
        input[i] = (float)game->board[i];
    }

    if (game->player == P_2) { // neural network will always play as X (player 1)
        for (int i = 0; i < 9; i ++) {
            input[i] *= -1;
        }
    }

    Matrix2Df*output = calculate_output(network, input, NULL);

    // gets the best options (sorts)
    int index_list[9] = {0, 0, 0, 0 ,0, 0 ,0 ,0 ,0};
    int choose = 0;
    // print_matrix(output);

    get_max_index(get_transposed(output), index_list);

    printf("\nplaying: %d \n", index_list[0]);

    while (!put_piece(game, index_list[choose++]))
    {
        printf("\nInvalid insertion.. \n");
    }
    printf("Piece inserted: %d\n,", index_list[choose-1]);
    
}

void get_max_index(Matrix2Df*output, int indexes[9]) {
    // int indexes[9];
    print_matrix(output);

    for (int i = 0; i < 9; i ++) {
        float max = 0;

        for (int j = 0; j < 9; j++) {
            if (output->_base_ptr[0][j] > max) {
                // printf("\ni %d ; j %d %f  %f\n", i, j, output->_base_ptr[0][j] , max);
                max = output->_base_ptr[0][j];
                indexes[i] = j;
                
            }
        }
        output->_base_ptr[0][indexes[i]] = 0;

        printf(" %d ", indexes[i]);
    }

    // return indexes;
}