#include "./include/velha2.h"

using namespace std;

Velha2::Velha2() {
    // Inicializa o jogo grande
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 10; j++) {
            game[j].board[i] = 0;
            game[j].player = P_1;
        }
    }
}

int Velha2::put_piece(_game* games, int game, int pos) {
    games[game].board[pos] = games->player;
    for (int i = 0; i < 10; i++) {
        games[i].player *= -1;
    }
    return pos;
}

int Velha2::special_move(_game *games, int game, int pos) {
    games[game].board[pos] = games->player;
    for (int i = 0; i < 10; i++) {
        games[i].player *= -1;
    }
    return pos;  
}

void Velha2::print_board(_game* game) {
    cout << endl;
    int i = 0;
    int j = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++){
            if (game[i].board[j] == 0) {
                cout << i << j << "  |  ";
            }
            else if (game[i].board[j] == 1) {
                cout << " X  |  ";
            }
            else if (game[i].board[j] == -1) {
                cout << " O  |  ";
            }
            else {
                cout << "*  |  ";
            }
            if ((j == 2 || j == 5 || j == 8) && (i != 2 && i != 5 && i != 8)) {
                j = j - 3;
                i = i + 1;
            }
            else if ((j == 2 || j == 5) && (i == 2 || i == 5 || i == 8)) {
                i = i - 2;
                cout << endl << "-------------------------------------------------------------------" << endl;
            }
            else if (j == 8 && (i == 2 || i == 5)) {
                i = i + 1;
                j = -1;
                cout << endl << "-------------------------------------------------------------------" << endl;
            }
        }
    }
    cout << endl << endl;
    cout << "big game:" << endl;
    for (int i = 0; i < 9; i++) {
        if (game[9].board[i] == 0) {
            cout << i << "  |  ";
        }
        else if (game[9].board[i] == 1) {
            cout << " X  |  ";
        }
        else if (game[9].board[i] == -1) {
            cout << "O  |  ";
        }
        else {
            cout << "*  |  ";
        }
        if (i == 2 || i == 5) {
            cout << endl << "-------------------" << endl;
        }
    }
    cout << endl << endl;
}

_game * Velha2::get_game() {
    return game;
}

int * Velha2::set_board(int * board) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 10; j++) {
            game[j].board[i] = 0;
            game[j].player = P_1;
        }
    }
    return board;
}

void Velha2::play_a_turn(_game *games, int *jogada_anterior) {
    int jogada_atual, special;
    if (check_special(games, jogada_anterior[0])) {
        cout << "Jogada especial" << endl << "Digite o jogo e a posição: " << endl;
        cin >> special;
        cin >> jogada_atual;
        if (checker(games, special, jogada_atual)) {
            special_move(games, special, jogada_atual);
            check_victory(games, special);
            jogada_anterior[0] = jogada_atual;
        }
        else {
            Velha2::play_a_turn(games, jogada_anterior);
        }
    }
    else {
        cout << "Jogada normal" << endl << "Digite a posição: " << endl;
        cin >> jogada_atual;
        if (checker(games, jogada_anterior[0], jogada_atual)) {
            put_piece(games, jogada_anterior[0], jogada_atual);
            check_victory(games, jogada_anterior[0]);
            jogada_anterior[0] = jogada_atual;
        }
        else {
            Velha2::play_a_turn(games, jogada_anterior);
        }
    }
    return;
}

bool checker(_game *games, int game, int pos) { 
    if (inside_board(game, pos) && check_tictac(games, game, pos)) {
        return true;
    }
    else {
        cout << "Jogada inválida" << endl;
        return false;
    }
}

bool inside_board(int board, int pos){
    if ((board >= 0 && board < 9) && (pos >= 0 && pos < 9)) {
        cout << "No campo" << endl;
        return true;
    }
    else {
        cout << "Fora do campo" << endl;
        return false;
    }
}

bool check_tictac(_game *games, int game, int pos) {
    if (games[game].board[pos] == 0) {
        cout << "Posição livre" << endl;
        return true;
    }
    else {
        cout << "Posição ocupada" << endl;
        return false;
    }
}

bool check_victory(_game *games, int board){
    if ((check_row(games, board) == 1 
            || check_column(games, board) == 1 
            || check_diagonal(games, board) == 1) 
            && games[9].board[board] == 0) {
        games[9].board[board] = 1;
        return true;
    }
    else if ((check_row(games, board) == -1 
            || check_column(games, board) == -1 
            || check_diagonal(games, board) == -1)
            && games[9].board[board] == 0) {
        games[9].board[board] = -1;
        return true;
    }
    else if (check_tie(games, board) == 2 && games[9].board[board] == 0) {
        games[9].board[board] = 2;
        for (int j = 0; j < 9; j++) {
            games[board].board[j] = 2;
        }
        return false;
    }
    else {
        return false;
    }
}

int check_row(_game* games, int game){
    for (int i = 0; i < 9; i = i + 3) {
        if (games[game].board[i] == games[game].board[i + 1] && games[game].board[i + 1] == games[game].board[i + 2] && games[game].board[i] != 0) {
            for (int j = 0; j < 9; j++) {
                games[game].board[j] = games[game].player * -1;
            }
            return  games[game].player * -1;
        }
    }
    return 0;

} 

int check_column(_game* games, int game){ 
    for (int i = 0; i < 3; i++) {
        if (games[game].board[i] == games[game].board[i + 3] && games[game].board[i + 3] == games[game].board[i + 6] && games[game].board[i] != 0) {
            for (int j = 0; j < 9; j++) {
                games[game].board[j] = games[game].player * -1;
            }
            return  games[game].player * -1;
        }
    }
    return 0;
}

int check_diagonal(_game* games, int game){ 
    if (games[game].board[0] == games[game].board[4] && games[game].board[4] == games[game].board[8] && games[game].board[0] != 0) {
        for (int j = 0; j < 9; j++) {
            games[game].board[j] = games[game].player * -1;
        };
        return  games[game].player * -1;
    }
    else if (games[game].board[2] == games[game].board[4] && games[game].board[4] == games[game].board[6] && games[game].board[2] != 0) {
        for (int j = 0; j < 9; j++) {
            games[game].board[j] = games[game].player * -1;
        }
        return  games[game].player * -1;
    }
    else {
        return 0;
    }
}

int check_tie(_game* games, int game){ 
    for (int i = 0; i < 9; i++) {
        if (games[game].board[i] == 0) {
            return 0;
        }
    }
    return 2;
}

bool check_special(_game* games, int game) {
    for (int i = 0; i < 9; i++) {
        if (games[game].board[i] == 0) {
            return false;
        }
    }
    return true;
}

int check_big_victory(_game* games) {
    if (check_row(games, 9) == 1 || check_column(games, 9) == 1 || check_diagonal(games, 9) == 1) {
        games[9].game_status = 1;
        cout << "Jogo finalizado" << endl << "Jogador 1 venceu" << endl;
        print_board(games);
        return 1;
    }
    else if (check_row(games, 9) == -1 || check_column(games, 9) == -1 || check_diagonal(games, 9) == -1) {
        games[9].game_status = -1;
        cout << "Jogo finalizado" << endl << "Jogador 2 venceu" << endl;
        return -1;
    }
    else if (check_tie(games, 9) == 2) {
        games[9].game_status = 2;
        cout << "Jogo finalizado" << endl << "Empate" << endl;
        return 2;
    }
    else {
        return 0;
    }
}
