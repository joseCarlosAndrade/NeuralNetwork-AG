#include "ConnectFour.h"

bool ConnectFour::IsSpaceValid(int input) {
    // Check if the input is within the range of 0 to 6 and the top of the column is empty
    return input >= 0 && input <= 6 && this->board[0][input] == 0;
}

void ConnectFour::PutPiece(int input) {
    // Iterate from the bottom of the column
    for(int row=5 ; row>=0 ; row--) {
        // Check if the space is empty
        if(this->board[row][input] == 0) {
            // Place the piece in the first empty space found
            this->board[row][input] = 1;
            return;
        }
    }
}

game_status ConnectFour::CheckGameStatus() {
    // Horizontal Check for Winner
    for(int row=0 ; row<6 ; row++) {
        for(int col=0 ; col<4 ; col++) {
            if(this->board[row][col] != 0 && 
               this->board[row][col + 1] == this->board[row][col] &&
               this->board[row][col + 2] == this->board[row][col] &&
               this->board[row][col + 3] == this->board[row][col]) {
                if(this->board[row][col] == 1) {
                    return (game_status) (this->turnPlayer);
                }
                else {
                    return (game_status) (3 - this->turnPlayer);
                }
            }
        }
    }

    // Vertical Check for Winner
    for(int col=0 ; col<7 ; col++) {
        for(int row=0 ; row<3 ; row++) {
            if(this->board[row][col] != 0 &&
               this->board[row + 1][col] == this->board[row][col] &&
               this->board[row + 2][col] == this->board[row][col] &&
               this->board[row + 3][col] == this->board[row][col]) {
                if(this->board[row][col] == 1) {
                    return (game_status) (this->turnPlayer);
                }
                else {
                    return (game_status) (3 - this->turnPlayer);
                }
            }
        }
    }

    // Diagonal Check for Winner (down-right)
    for(int col=0 ; col<4 ; col++) {
        for(int row=0 ; row<3 ; row++) {
            if(this->board[row][col] != 0 &&
               this->board[row + 1][col + 1] == this->board[row][col] &&
               this->board[row + 2][col + 2] == this->board[row][col] &&
               this->board[row + 3][col + 3] == this->board[row][col]) {
                if(this->board[row][col] == 1) {
                    return (game_status) (this->turnPlayer);
                }
                else {
                    return (game_status) (3 - this->turnPlayer);
                }
            }
        }
    }
    for(int col=3 ; col<7 ; col++) {
        for(int row=0 ; row<3 ; row++) {
            if(this->board[row][col] != 0 &&
               this->board[row + 1][col - 1] == this->board[row][col] &&
               this->board[row + 2][col - 2] == this->board[row][col] &&
               this->board[row + 3][col - 3] == this->board[row][col]) {
                if(this->board[row][col] == 1) {
                    return (game_status) (this->turnPlayer);
                }
                else {
                    return (game_status) (3 - this->turnPlayer);
                }
            }
        }
    }

    // Check for a Draw
    for(int row=0 ; row<6 ; row++) {
        for(int col=0 ; col<7 ; col++) {
            if(this->board[row][col] == 0) {
                return ONGOING; // Found an empty spot, game is still ongoing
            }
        }
    }

    return TIE; // No empty spots and no winner, hence a draw
}

void ConnectFour::PrintBoard() {
    const char *p = (this->turnPlayer == 1) ? "O X" : "X O";

    // Print the board from top to bottom (row 5 to row 0)
    for(int row=0 ; row<6 ; row++) {
        for(int col=0; col<7; col++) {
            cout << " " << p[this->board[row][col]+1] << " |";
        }
        cout << endl;
        cout << "-----------------------------" << endl;
    }

    // Print column numbers at the bottom
    cout << " 0 | 1 | 2 | 3 | 4 | 5 | 6 " << endl;
    cout << endl;
}

Eigen::VectorXd ConnectFour::GetGameState() {
    Eigen::VectorXd gameState(42); // Create a vector of size 42 for the 7x6 board

    for(int i=0 ; i<42 ; i++) {
        int row = i / 7; // Calculate the row for the 7-column board
        int col = i % 7; // Calculate the column for the 7-column board
        gameState[i] = this->board[row][col]; // Assign the board value to the gameState vector
    }

    return gameState;
}

int ConnectFour::GetRandomValidInput(VectorXd& gameState) {
    vector<int> validInputs;
    for(int i=35 ; i<42 ; i++) {
        if(gameState[i] == 0) {
            validInputs.push_back(i % 7);
        }
    }
    int idx = rand() % (int)validInputs.size();
    return validInputs[idx];
}

ConnectFour::ConnectFour() : TwoPlayerGame(6, 7, 42, 7) {

}

ConnectFour::~ConnectFour() {

}
