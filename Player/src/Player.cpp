#include "Player.h"

vector<int> Player::GetNetStructure() {
    return vector<int>(); // So para teste? talvez exclua depois, mas acho que da pra deixar como acesso
}

void Player::SetNetStructure(vector<int>& netStructure) {
    // vai virar template

    // LEMBRAR DE FAZER A FUNCAO DO GAME QUE CHECA TAMANHO DA REDE PARA USAR QND REEBER OS COM
    // (NADA A VER COM O PLAYER EM SI, MAS TA DE LEMBRETE)
}

Player::Player() {
    // constroi com rede aleatoria
}

Player::Player(DenseNetwork& net) {
    // constroi com rede que recebeu do arg
}

DenseNetwork * Player::GetAI() {
    return this->AI;
}

Player::~Player() {
    delete this->AI;
}