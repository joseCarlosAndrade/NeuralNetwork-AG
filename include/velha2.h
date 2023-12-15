#include "velha.h"
#include <iostream>
#include <string>
#include <vector>

#ifndef _VELHA2_H
#define _VELHA2_H

using namespace std;

class Velha2 {
    private:
        _game game[10];                                     // Vetor de jogos, sendo o décimo o jogo grande
        int mistakes_P1;                                    // Número de jogadas inválidas Player 1
        int mistakes_P2;                                    // Número de jogadas inválidas Player 2
    public:
        Velha2();                                           // Construtor
        int put_piece(_game* games, int game, int pos);     // Adiciona a peça no jogo pequeno obtido pela posição
        int special_move(_game *games, int game, int pos);  // Adiciona a peça no jogo pequeno selecionado
        void print_board(_game* Game);                      // Imprime o tabuleiro
        _game * get_game();                                 // Retorna o vetor de jogos
        int * set_board(int * board);                       // Seta o tabuleiro para um novo jogo
        void play_a_turn(_game *games,int *jogada_anterior);// Realiza uma jogada 
};

// Verifica se a posição está válida
bool checker(_game *games, int game, int pos);              // Verifica se a jogada é válida
bool inside_board(int game, int pos);                       // Verifica se a posição está dentro do tabuleiro
bool check_tictac(_game *games, int game, int pos);         // Verifica se a posição está ocupada

// Funções de vitória 
bool check_victory(_game *games, int board);
int check_row(_game* games, int game);
int check_column(_game* games, int game);
int check_diagonal(_game* games, int game);
int check_tie(_game* games, int game);

// Funções de condições epeciais 
bool check_special(_game* games, int game);                 // Verifica se o jogo pequeno está completo
int check_big_victory(_game* games);                        // Verifica se o jogo grande está completo


#endif