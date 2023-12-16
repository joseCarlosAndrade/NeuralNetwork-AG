#include "TwoPlayerGame.h"


int* TwoPlayerGame::GetPlaysInputs(Eigen::VectorXd *playsProbs) {
    Eigen::VectorXi indices = Eigen::VectorXi::LinSpaced(playsProbs->rows(), 0, playsProbs->rows() - 1);
    std::sort(indices.data(), indices.data() + indices.size(), [&playsProbs](int i, int j) { return (*playsProbs)(i, 0) < (*playsProbs)(j, 0); });
    return indices.data();
}

void TwoPlayerGame::SwitchPlayer() {
   this->turn_player = 3 - this->turn_player;
   for(int i=0 ; i<this->boardRows ; i++) {
       for(int j=0 ; j<this->boardCols ; j++) {
           this->board[i][j] *= -1;
       }
   }
}


TwoPlayerGame::TwoPlayerGame(int boardRows, int boardCols, int gameStateLen, int playInputLen) {
    this->boardRows = boardRows;
    this->boardCols = boardCols;
    this->gameStateLen = gameStateLen;
    this->playInputLen = playInputLen;

    this->board = new int*[boardRows];
    for(int i=0 ; i<boardRows ; i++) {
        this->board[i] = new int[boardCols];
        for(int j=0 ; j<boardCols ; j++) {
            this->board[i][j] = 0;
        }
    }

    this->turn_player = 1;
}

int TwoPlayerGame::GetGameStateLen() {
    return this->gameStateLen;
}

int TwoPlayerGame::GetPlayInputLen() {
    return this->playInputLen;
}

game_status TwoPlayerGame::PlayerVSPlayer() {

    return ONGOING;
}

game_status TwoPlayerGame::PlayerVSCom(Network *com, int *out_errors) {

    return ONGOING;
}

game_status TwoPlayerGame::ComVSCom(Network *com1, Network *com2, int *out_errors1, int *out_errors2) {
    return ONGOING;
}

TwoPlayerGame::~TwoPlayerGame() {
    for(int i=0 ; i<this->boardRows ; i++) {
        delete this->board[i];
    }
    delete this->board;
}