#ifndef PLAYER_INL
#define PLAYER_INL

#include "Player.h"

template<Game G>
void * Player::playerCopyFunction(const void *data) {
    return NULL;
}

template<Game G>
comparison Player::playerCompareFunction(const void *data1, const void *data2) {
    return EQUAL;
}

template<Game G>
void Player::playerPrintFunction(const void *data) {
    cout << "test" << endl;
    G *a = new G();
    delete a;
}

template<Game G>
void Player::playerEraseFunction(void **data_addr) {

}

template<Game G>
void * Player::playerInitFunction(void **dataVec, const int vecSize) {
    return NULL;
}

template<Game G>
void Player::playerEvaluateFunction(void **dataVec, const int vecSize, float *out_fitnesses) {

}

template<Game G>
void * Player::playerCrossoverFunction(const void *data1, const void *data2) {
    return NULL;
}

template<Game G>
void Player::playerMutateFunction(void *data, const float mutation) {

}

template<Game G>
T * Player::GetType() {
    T *playerType = type_create(sizeof(Player), playerCopyFunction<G>, playerCompareFunction<G>, playerPrintFunction<G>, playerEraseFunction<G>);
    return playerType;
}

template<Game G>
T_EVOL * Player::GetTypeEvolvable() {
    T_EVOL *playerTypeEvolvable = typeEvolvable_create(playerInitFunction<G>, playerEvaluateFunction<G>, playerCrossoverFunction<G>, playerMutateFunction<G>);
    return playerTypeEvolvable;
}

#endif