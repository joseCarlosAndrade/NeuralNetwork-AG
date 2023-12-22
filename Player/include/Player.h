#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <concepts>
#include <Eigen/Core>
#include "DenseNetwork.h"
#include "TwoPlayerGame.h"
#include "type.h"
#include "typeEvolvable.h"

using namespace std;
using namespace Eigen;
using namespace MiniDNN;

#define WRONG_MOVE_PENALTY 1
#define VICTORY_PRIZE 15
#define LOSS_PENALTY 15

template<class C>
concept Game = is_base_of<TwoPlayerGame, C>::value;

template<Game G>
class Player {
    private:
        static vector<int> netStructure;

        DenseNetwork *AI;
        
        static void * playerCopyFunction(const void *data);
        static comparison playerCompareFunction(const void *data1, const void *data2);
        static void playerPrintFunction(const void *data);
        static void playerEraseFunction(void **data_addr);

        static void * playerInitFunction(void **dataVec, const int vecSize);
        static void playerEvaluateFunction(void **dataVec, const int vecSize, float *out_fitnesses);
        static void * playerCrossoverFunction(const void *data1, const void *data2);
        static void playerMutateFunction(void *data, const float mutation);
    
    public:
        static T * GetType();
        static T_EVOL * GetTypeEvolvable();

        static vector<int> GetNetStructure();
        static void SetNetStructure(vector<int>& netStructure);

        Player();
        Player(DenseNetwork& net);

        DenseNetwork * GetAI();

        ~Player();
};

#include "../src/Player.cpp"    // Player INL

#endif 