#ifndef PLAYER_INL
#define PLAYER_INL

#include "Player.h"

template<Game G>
vector<int> Player<G>::netStructure;

template<Game G>
void * Player<G>::playerCopyFunction(const void *data) {
    if(data == NULL) {
        return NULL;
    }
    Player<G> *player = (Player<G> *) data;
    Player<G> *playerCopy = new Player<G>(*(player->AI));
    return playerCopy;
}

template<Game G>
comparison Player<G>::playerCompareFunction(const void *data1, const void *data2) {
    G game;
    Player<G> *player1 = (Player<G> *) data1;
    Player<G> *player2 = (Player<G> *) data2;
    int errors1 = 0, errors2 = 0;
    game_status result = game.ComVSCom(player1->AI, player2->AI, &errors1, &errors2, false);

    if(result == P1_VICTORY) {
        return GREATER;
    }
    else if(result == P2_VICTORY) {
        return LOWER;
    }
    else {
        return EQUAL;
    }
}

template<Game G>
void Player<G>::playerPrintFunction(const void *data) {
    Player<G> *player = (Player<G> *) data;
    cout << "Estrutura da rede: { ";
    for(size_t i=0 ; i<player->netStructure.size() ; i++) {
        cout << player->netStructure[i] << " ";
    }
    cout << "}" << endl;
}

template<Game G>
void Player<G>::playerEraseFunction(void **data_addr) {
    delete *((Player<G> **) data_addr);
    *data_addr = NULL;
}

template<Game G>
void * Player<G>::playerInitFunction(void **dataVec, const int vecSize) {
    Player<G> *playerNew;
    if(dataVec == NULL) {
        playerNew = new Player<G>();
    }
    else {
        Player<G> *player = (Player<G> *) dataVec[0];
        DenseNetwork meanNet = DenseNetwork(*(player->AI));
        for(int i=1 ; i<vecSize ; i++) {
            player = (Player<G> *) dataVec[i];
            meanNet += *(player->AI);
        }
        meanNet /= vecSize;
        playerNew = new Player<G>(meanNet);
    }

    return playerNew;
}

template<Game G>
void Player<G>::playerEvaluateFunction(void **dataVec, const int vecSize, float *out_fitnesses) {
    for(int i=0 ; i<vecSize ; i++) {
        out_fitnesses[i] = 0;
    }

    for(int i=0 ; i<vecSize ; i++) {
        Player<G> *player = (Player<G> *) dataVec[i];
        for(int j=0; j<2*vecSize; j++) {
            G game;
            bool isFirst = j < vecSize;
            int errors = 0;
            game_status result = game.ComVSRandom(player->AI, &errors, isFirst, false);

            float points;
            if(result == P1_VICTORY) {
                points = isFirst ? VICTORY_PRIZE : -LOSS_PENALTY;
            }
            else if(result == P2_VICTORY) {
                points = isFirst ? -LOSS_PENALTY : VICTORY_PRIZE;
            }
            else {
                points = 0;
            }
            out_fitnesses[i] += points;
            out_fitnesses[i] -= errors * WRONG_MOVE_PENALTY;
        }
    }
}

/* template<Game G>
void Player<G>::playerEvaluateFunction(void **dataVec, const int vecSize, float *out_fitnesses) {
    for(int i=0 ; i<vecSize ; i++) {
        out_fitnesses[i] = 0;
    }

    for(int i=0 ; i<vecSize ; i++) {
        Player<G> *player1 = (Player<G> *) dataVec[i];
        for(int j=0; j<vecSize; j++) {
            if(i == j) {
                continue;
            }

            G game;
            Player<G> *player2 = (Player<G> *) dataVec[j];
            int errors1 = 0, errors2 = 0;
            game_status result = game.ComVSCom(player1->AI, player2->AI, &errors1, &errors2, false);

            if(result == P1_VICTORY) {
                out_fitnesses[i] += VICTORY_PRIZE;
                out_fitnesses[j] -= LOSS_PENALTY;
            }
            else if(result == P2_VICTORY) {
                out_fitnesses[i] -= LOSS_PENALTY;
                out_fitnesses[j] += VICTORY_PRIZE;
            }

            out_fitnesses[i] -= errors1 * WRONG_MOVE_PENALTY;
            out_fitnesses[j] -= errors2 * WRONG_MOVE_PENALTY;
        }
    }
} */

template<Game G>
void * Player<G>::playerCrossoverFunction(const void *data1, const void *data2) {
    Player<G> *player1 = (Player<G> *) data1;
    Player<G> *player2 = (Player<G> *) data2;
    DenseNetwork meanNet = (*(player1->AI) + *(player2->AI)) / 2;

    Player<G> *playerNew = new Player<G>(meanNet);
    return playerNew;
}

template<Game G>
void Player<G>::playerMutateFunction(void *data, const float mutation) {
    if(data == NULL) {
        return;
    }
    Player<G> *player = (Player<G> *) data;
    vector<vector<double>> parameters = player->AI->GetParameters();

    int chance = rand() % 100;
    int numMutated;
    if(chance < 50) {
        numMutated = 1;
    }
    else if(chance < 80) {
        numMutated = 5;
    }
    else {
        numMutated = 10;
    }

    for(int i=0 ; i<numMutated ; i++) {
        int layer_idx = rand() % (int)parameters.size();
        int param_idx = rand() % (int)parameters[layer_idx].size();
        parameters[layer_idx][param_idx] += PARAMETERS_DOMAIN * mutation;
    }

    player->AI->SetParameters(parameters);
}

template<Game G>
T * Player<G>::GetType() {
    T *playerType = type_create(sizeof(Player), Player<G>::playerCopyFunction, Player<G>::playerCompareFunction, Player<G>::playerPrintFunction, Player<G>::playerEraseFunction);
    return playerType;
}

template<Game G>
T_EVOL * Player<G>::GetTypeEvolvable() {
    T_EVOL *playerTypeEvolvable = typeEvolvable_create(Player<G>::playerInitFunction, Player<G>::playerEvaluateFunction, Player<G>::playerCrossoverFunction, Player<G>::playerMutateFunction);
    return playerTypeEvolvable;
}

template<Game G>
vector<int> Player<G>::GetNetStructure() {
    return Player<G>::netStructure;
}

template<Game G>
void Player<G>::SetNetStructure(vector<int>& netStructure) {
    G game;
    int firstLayer = netStructure[0];
    int lastLayer = netStructure[netStructure.size()-1];
    if(firstLayer != game.GetGameStateLen() || lastLayer != game.GetPlayInputLen()) {
        cerr << "This structure isn't accepted for this type of Player!" << endl;
        return;
    }

    Player<G>::netStructure = netStructure;
}

template<Game G>
Player<G>::Player() {
    this->AI = new DenseNetwork(Player<G>::netStructure);
}

template<Game G>
Player<G>::Player(DenseNetwork& net) {
    G game;
    vector<int> layers = net.GetLayers();
    int firstLayer = layers[0];
    int lastLayer = layers[layers.size()-1];
    if(firstLayer != game.GetGameStateLen() || lastLayer != game.GetPlayInputLen()) {
        cerr << "This network doesn't have an accepted structure for this type of Player!" << endl;
        return;
    }

    this->AI = new DenseNetwork(net);
}

template<Game G>
DenseNetwork * Player<G>::GetAI() {
    return this->AI;
}

template<Game G>
Player<G>::~Player() {
    delete this->AI;
}

#endif