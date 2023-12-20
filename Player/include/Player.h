#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <concepts>
#include <Eigen/Core>
#include "MiniDNN.h"
#include "DenseNetwork.h"
#include "TwoPlayerGame.h"
#include "type.h"
#include "typeEvolvable.h"

using namespace std;
using namespace Eigen;
using namespace MiniDNN;

template<class C>
concept Game = is_base_of<TwoPlayerGame, C>::value;

class Player {
    private:
        static vector<int> netStructure;

        DenseNetwork *AI;
        
        template<Game G> static void * playerCopyFunction(const void *data);
        template<Game G> static comparison playerCompareFunction(const void *data1, const void *data2);
        template<Game G> static void playerPrintFunction(const void *data);
        template<Game G> static void playerEraseFunction(void **data_addr);

        template<Game G> static void * playerInitFunction(void **dataVec, const int vecSize);
        template<Game G> static void playerEvaluateFunction(void **dataVec, const int vecSize, float *out_fitnesses);
        template<Game G> static void * playerCrossoverFunction(const void *data1, const void *data2);
        template<Game G> static void playerMutateFunction(void *data, const float mutation);
    
    public:
        template<Game G> static T * GetType();
        template<Game G> static T_EVOL * GetTypeEvolvable();

        static vector<int> GetNetStructure();
        static void SetNetStructure(vector<int>& netStructure);

        Player();
        Player(DenseNetwork& net);

        DenseNetwork * GetAI();

        ~Player();
};

#include "Player-inl.cpp"

#endif 