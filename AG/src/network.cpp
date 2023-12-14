struct sla
{
    /* data */
};


jogador {
    nome
    rede
}

jogadro * jogador_create_random() {

}

jogador * jogador_create(rede) {

}



void jogador_erase(jogador **jog_addr) {
    if(*jog_addr != NULL) {
        string_free(name)
        rede_erase((*jog_addr)->rede);
        free(*jog_addr);
        *jog_addr = NULL;
    }
}

static void * funcaoEscrotaCopyFunction(const void *data) {
    jogador *jog = (jogador *) data
    return novojog = jogador_create(jog->rede)
}

static comparison funcaoEscrotaCompareFunction(const void *data1, const void *data2); // nao precisa

static void funcaoEscrotaPrintFunction(const void *data); // nao precisa

static void funcaoEscrotaEraseFunction(void **data_addr) {
    jogador_erase((jogador **) data_addr);
}

static void * funcaoEscrotaInitFunction(void **dataVec, const int vecSize) {
    if(dataVec == NULL) {
        return jogador_create_random()
    }
    else {
        rede_media = Rede()
        for(vecSize) {
            rede_media += jogador->rede
        }
        rede_media /= vecSize
        return jogador_create(rede_media)
    }
}

static void funcaoEscrotaEvaluateFunction(void **dataVec, const int vecSize, float *out_fitnesses) {
    for(vecSize) {
        out_fitnesses[0] = 0;
    }
    for(vecSize) {
        jogador *jog1 = (jogador *) dataVec[i]
        for(vecSize) {
            if (j == i) {
                continue;
            }
            jogador *jog2 = (jogador *) dataVec[j]
            while(jogo nao acabou) {
                while(!turno1) {
                    out_fitnesses[i] += erro
                }
                while(!turno2) {
                    out_fitnesses[j] += erro
                }
                quem venceu
            }
            out_fitnesses[i] += venceu ? 10 : -10
            out_fitnesses[j] += venceu ? 10 : -10
        }
        out_fitnesses[i] += penalidade pelo numero de neuronios
    }
}

static void * funcaoEscrotaCrossoverFunction(const void *data1, const void *data2) {

}

static void funcaoEscrotaMutateFunction(void *data, const float mutation) {
    
}




