#include <iostream>
#include <string>
#include <vector>
#include "include/velha2.h"

using namespace std;

int main() {
    Velha2 Game;
    Velha2 *game = &Game;
    int jogada_atual, especial, jogada_anterior = 0;
    int *board = game->set_board(board);
    game->print_board(game->get_game());
    cout << endl << "Jogada inicial" << endl << "Digite o jogo e a posição: " << endl;
    cin >> especial;
    cin >> jogada_atual;
    while (checker(game->get_game(), especial, jogada_atual) == false) {
        cin >> especial;
        cin >> jogada_atual;
    }
    game->special_move(game->get_game(), especial, jogada_atual);
    jogada_anterior = jogada_atual;
    while (true) {
        if (check_big_victory(game->get_game()) == 1 || check_big_victory(game->get_game()) == -1 || check_big_victory(game->get_game()) == 2) {
            print_board(game->get_game());
            break;
        }
        else {
            game->print_board(game->get_game());
            game->play_a_turn(game->get_game(), &jogada_anterior);
        }
    }
    return 0;
}