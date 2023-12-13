jogador {
    nome
    rede
}

void jogador_erase(jogador **jog_addr) {
    if(*jog_addr != NULL) {
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

static void * funcaoEscrotaInitFunction(void **dataVec, const int vecSize);
static void funcaoEscrotaEvaluateFunction(void **dataVec, const int vecSize, float *out_fitnesses);
static void * funcaoEscrotaCrossoverFunction(const void *data1, const void *data2);
static void funcaoEscrotaMutateFunction(void *data, const float mutation);



