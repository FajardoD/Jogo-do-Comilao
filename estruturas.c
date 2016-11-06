#include "includes.h"

pjogadas manutencao_jogadas(pjogadas p, JOGADA *jog){
    pjogadas novo, aux;
    novo=malloc(sizeof(JOGADA));
    if(novo == NULL){
        printf("Erro ao alocar espaco.\n");
        return p;
    }

    novo->njogador = jog->njogador;
    novo->aumento[0] = jog->aumento[0];
    novo->aumento[1] = jog->aumento[1];
    strcpy(novo->coordenada, jog->coordenada);
    novo->prox = NULL;

    if(p == NULL){
        p = novo;
    }else{
        aux = p;
        while(aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novo;
    }
    return p;
}

pjogadas criar_lista_sucessao_estados(pjogadas lista, JOGADA *jog){
    //se ao retomar um jogo, as succesoes de estados serem aproveitadas
    FILE *f;
    JOGADA jogador;
    QUADRADO *tabuleiro;
    int modo, njogador, linhas, colunas;

    if((f=fopen(nome_fich,"rb")) == NULL){
        printf("Nao existe nenhum jogo anteriormente guardado!\n");
        exit(0);
    }

    fread(&modo, sizeof(int),1,f);
    fread(&linhas, sizeof(int), 1, f);
    fread(&colunas, sizeof(int), 1, f);

    while(fread(&jogador, sizeof(JOGADA), 1, f) == 1){
        jog->njogador = jogador.njogador;
        //inicializa a variavel aumento, para ver se um dos jogadores já aumentou antes de retomar o jogo
        if(jogador.aumento[0] == 1)
            jog->aumento[0] = 1;

        if(jogador.aumento[1] == 1)
            jog->aumento[1] = 1;
        lista = manutencao_jogadas(lista, &jogador);
    }
    fclose(f);
    return lista;
}

void apagar_lista(pjogadas lista){
   while(lista != NULL){
        free(lista);
        lista = lista->prox;
    }
}
