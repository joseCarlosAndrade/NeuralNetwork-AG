#include "TwoPlayerGame.h"

int * TwoPlayerGame::GetPlaysInputs(VectorXd& playsProbs) {
    VectorXi indices = VectorXi::LinSpaced(playsProbs.rows(), 0, playsProbs.rows() - 1);
    sort(indices.data(), indices.data() + indices.size(), [&playsProbs](int i, int j) { return playsProbs(i, 0) > playsProbs(j, 0); });

    int *playsInputs = new int[indices.size()];
    for(int i=0 ; i<indices.size() ; i++) {
        playsInputs[i] = indices[i];
    }
    return playsInputs;
}

void TwoPlayerGame::SwitchPlayer() {
   this->turnPlayer = 3 - this->turnPlayer;
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

    this->turnPlayer = 1;
}

int TwoPlayerGame::GetGameStateLen() {
    return this->gameStateLen;
}

int TwoPlayerGame::GetPlayInputLen() {
    return this->playInputLen;
}

game_status TwoPlayerGame::PlayerVSPlayer() {
    this->PrintBoard();
    
    while(this->CheckGameStatus() == ONGOING) {
        int input;
        do {
            cout << "Jogador " << this->turnPlayer << ", faça sua jogada: ";
            cin >> input;
        } while(!this->IsSpaceValid(input));

        this->PutPiece(input);
        this->PrintBoard();
        this->SwitchPlayer();
    }
    
    return this->CheckGameStatus();
}

game_status TwoPlayerGame::PlayerVSCom(Network *com, int *out_errors, bool verbose) {
    if(verbose || this->turnPlayer == 1) this->PrintBoard();

    while(this->CheckGameStatus() == ONGOING) {
        int input;
        if(this->turnPlayer == 1) {
            do {
                cout << "Jogador 1, faça sua jogada: ";
                cin >> input;
            } while(!this->IsSpaceValid(input));
        }
        else {
            VectorXd gameState = this->GetGameState();
            VectorXd plays = com->predict(gameState);
            int *inputs = this->GetPlaysInputs(plays);

            int i = 0;
            while(!this->IsSpaceValid(inputs[i])) {
                i++;
                *out_errors += 1;
            }
            input = inputs[i];
            delete[] inputs;
        }

        this->PutPiece(input);
        if(verbose || this->turnPlayer == 1) this->PrintBoard();
        this->SwitchPlayer();
    }

    return this->CheckGameStatus();
}

game_status TwoPlayerGame::ComVSCom(Network *com1, Network *com2, int *out_errors1, int *out_errors2, bool verbose) {
    if(verbose) this->PrintBoard();

    while(this->CheckGameStatus() == ONGOING) {
        Network *com = (this->turnPlayer == 1) ? com1 : com2;
        int *out_errors = (this->turnPlayer == 1) ? out_errors1 : out_errors2;

        VectorXd gameState = this->GetGameState();
        VectorXd plays = com->predict(gameState);
        int *inputs = this->GetPlaysInputs(plays);

        int i = 0;
        while(!this->IsSpaceValid(inputs[i])) {
            i++;
            *out_errors += 1;
        }
        int input = inputs[i];
        delete[] inputs;

        this->PutPiece(input);
        if(verbose) this->PrintBoard();
        this->SwitchPlayer();
    }

    return this->CheckGameStatus();
}

TwoPlayerGame::~TwoPlayerGame() {
    for(int i=0 ; i<this->boardRows ; i++) {
        delete[] this->board[i];
    }
    delete[] this->board;
}