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

bool TwoPlayerGame::CheckComStructure(DenseNetwork *com) {
    vector<int> layers = com->GetLayers();
    int firstLayer = layers[0];
    int lastLayer = layers[layers.size()-1];
    return firstLayer == this->gameStateLen && lastLayer == this->playInputLen;
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

game_status TwoPlayerGame::PlayerVSRandom(bool playerFirst, bool verbose) {
    int playerTurn = playerFirst ? 1 : 2;

    if(verbose || this->turnPlayer == playerTurn) this->PrintBoard();

    while(this->CheckGameStatus() == ONGOING) {
        int input;
        if(this->turnPlayer == playerTurn) {
            do {
                cout << "Jogador " << this->turnPlayer << ", faça sua jogada: ";
                cin >> input;
            } while(!this->IsSpaceValid(input));
        }
        else {
            VectorXd gameState = this->GetGameState();
            input = this->GetRandomValidInput(gameState);
        }

        this->PutPiece(input);
        if(verbose || this->turnPlayer == playerTurn) this->PrintBoard();
        this->SwitchPlayer();
    }

    return this->CheckGameStatus();
}

game_status TwoPlayerGame::PlayerVSCom(DenseNetwork *com, int *out_errors, bool playerFirst, bool verbose) {
    if(!this->CheckComStructure(com)) {
        cerr << "This AI's structure isn't suited for this Game!" << endl;
        return TIE;
    }

    int playerTurn = playerFirst ? 1 : 2;

    if(verbose || this->turnPlayer == playerTurn) this->PrintBoard();

    while(this->CheckGameStatus() == ONGOING) {
        int input;
        if(this->turnPlayer == playerTurn) {
            do {
                cout << "Jogador " << this->turnPlayer << ", faça sua jogada: ";
                cin >> input;
            } while(!this->IsSpaceValid(input));
        }
        else {
            VectorXd gameState = this->GetGameState();
            VectorXd plays = com->Predict(gameState);
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
        if(verbose || this->turnPlayer == playerTurn) this->PrintBoard();
        this->SwitchPlayer();
    }

    return this->CheckGameStatus();
}

game_status TwoPlayerGame::ComVSRandom(DenseNetwork *com, int *out_errors, bool comFirst, bool verbose) {
    if(!this->CheckComStructure(com)) {
        cerr << "This AI's structure isn't suited for this Game!" << endl;
        return TIE;
    }

    int comTurn = comFirst ? 1 : 2;

    if(verbose) this->PrintBoard();

    while(this->CheckGameStatus() == ONGOING) {
        int input;
        if(this->turnPlayer == comTurn) {
            VectorXd gameState = this->GetGameState();
            VectorXd plays = com->Predict(gameState);
            int *inputs = this->GetPlaysInputs(plays);

            int i = 0;
            while(!this->IsSpaceValid(inputs[i])) {
                i++;
                *out_errors += 1;
            }
            input = inputs[i];
            delete[] inputs;
        }
        else {
            VectorXd gameState = this->GetGameState();
            input = this->GetRandomValidInput(gameState);
        }

        this->PutPiece(input);
        if(verbose) this->PrintBoard();
        this->SwitchPlayer();
    }

    return this->CheckGameStatus();
}

game_status TwoPlayerGame::ComVSCom(DenseNetwork *com1, DenseNetwork *com2, int *out_errors1, int *out_errors2, bool verbose) {
    if(!this->CheckComStructure(com1) || !this->CheckComStructure(com2)) {
        cerr << "This AI's structure isn't suited for this Game!" << endl;
        return TIE;
    }

    if(verbose) this->PrintBoard();

    while(this->CheckGameStatus() == ONGOING) {
        DenseNetwork *com = (this->turnPlayer == 1) ? com1 : com2;
        int *out_errors = (this->turnPlayer == 1) ? out_errors1 : out_errors2;

        VectorXd gameState = this->GetGameState();
        VectorXd plays = com->Predict(gameState);
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