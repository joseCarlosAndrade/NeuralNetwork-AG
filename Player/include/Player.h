#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <concepts>         // VER PQ O INCLUDE DO CONCEPTS TA DANDO ERRADO (PRA MIM PELO MENOS)
#include <Eigen/Core>
#include "MiniDNN.h"
#include "DenseNetwork.h"
#include "TwoPlayerGame.h"

using namespace std;
using namespace Eigen;
using namespace MiniDNN;

template<class T>
concept Game = is_base_of<TwoPlayerGame, T>::value;

template<Game T>
class Player {
    private:
        DenseNetwork *AI;

        //TODAS AS 8 FUNCOES DOS TYPE, COMO STATICS

        static T *type;
        static T_EVOL *typeEvolvable;
    
    public:
        Player()

        static T * GetType();           // inicializa o type se necessario e retorna
        static T_EVOL * GetTypeEvolvable();      // inicializa o typeEvolvable se necessario e retorna

        DenseNetwork * GetAI();     // retorna o AI, como ponteiro mesmo, para podermos mexer nela por fora caso quisermos

        ~Player();
};

#endif 