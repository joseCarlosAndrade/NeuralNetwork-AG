#include "TicTacToe.h"

bool TicTacToe::IsSpaceValid(int input) {
    if (input < 0 || input > 8) return false;
    int row = input % 3;
    int col = (int) input / 3;
    return this->board[row][col] == 0;
}

void TicTacToe::PutPiece(int input) {
    int row = input % 3;
    int col = (int) input / 3;
    this->board[row][col] = 1;
}

game_status TicTacToe::CheckGameStatus() {
    // check rows 0 1 2 | 3 4 5 | 6 7 8
    for(int i=0 ; i<3 ; i++) {
        if(this->board[i][0] != 0 && this->board[i][0] == this->board[i][1] && this->board[i][0] == this->board[i][2]) {
            if(this->board[i][0] == 1) {
                return (game_status) (this->turnPlayer);
            }
            else {
                return (game_status) (3 - this->turnPlayer);
            }
        }
    }

    // check columns 0 3 6 | 1 4 7 | 2 5 8
    for(int i=0 ; i<3 ; i++) {
        if(this->board[0][i] != 0 && this->board[0][i] == this->board[1][i] && this->board[0][i] == this->board[2][i]) {
            if(this->board[0][i] == 1) {
                return (game_status) (this->turnPlayer);
            }
            else {
                return (game_status) (3 - this->turnPlayer);
            }
        }
    }

    // check diagonals
    if(this->board[0][0] != 0 && this->board[0][0] == this->board[1][1] && this->board[0][0] == this->board[2][2]) {
        if(this->board[0][0] == 1) {
            return (game_status) (this->turnPlayer);
        }
        else {
            return (game_status) (3 - this->turnPlayer);
        }
    }

    if(this->board[0][2] != 0 && this->board[0][2] == this->board[1][1] && this->board[0][2] == this->board[2][0]) {
        if(this->board[0][2] == 1) {
            return (game_status) (this->turnPlayer);
        }
        else {
            return (game_status) (3 - this->turnPlayer);
        }
    }

    // check tie
    for(int i=0; i<3; i++) {
        for(int j=0 ; j<3 ; j++) {
            if(this->board[i][j] == 0) {
                return ONGOING; 
            }
        }
    }

    return TIE;
}

void TicTacToe::PrintBoard() {
    char * p = "O X";
    printf(
    "\n %c | %c | %c   |   0 | 1 | 2 \n___________  |\n %c | %c | %c   |   3 | 4 | 5 \n___________  |\n %c | %c | %c   |   6 | 7 | 8 \n",
    p[this->board[0][0]+1],
    p[this->board[0][1]+1],
    p[this->board[0][2]+1],
    p[this->board[1][0]+1],
    p[this->board[1][1]+1],
    p[this->board[1][2]+1],
    p[this->board[2][0]+1],
    p[this->board[2][1]+1],
    p[this->board[2][2]+1]
    );
}

Eigen::VectorXd TicTacToe::GetGameState() {
   Eigen::VectorXd gameState(9);
   for(int i=0 ; i<9 ; i++) {
        int row = i % 3;
        int col = (int) i / 3;
        gameState[i] = this->board[row][col];
   }
   return gameState;
}



TicTacToe::TicTacToe() : TwoPlayerGame(3, 3, 9, 9) {

}

TicTacToe::~TicTacToe() {

}