#include "includes.h"

QUADRADO * inicializar_tabuleiro(int LINHAS, int COLUNAS){
    int i, j;
    char abcd;

    QUADRADO *tab = malloc(sizeof(QUADRADO) * (++LINHAS*++COLUNAS));
    if(tab == NULL){
        printf("Erro na alocacao de memoria!\n");
        return tab;
    }else{
        tab->nlinhas = LINHAS;
        tab->ncolunas = COLUNAS;
        for(i=0;i<LINHAS;i++){
            for(j=0, abcd='A';j<COLUNAS;j++){
                if(i==0 && j == 0)
                    (tab + i*COLUNAS + j)->car = ' ';
                else{
                    if(i==0 && j>=1)
                        (tab + i*COLUNAS + j)->car = abcd++;
                    else{
                        if(i >= 1 && j == 0)
                            (tab + i*COLUNAS + j)->car = i + '0';// + '0' p/ converter de int para char
                        else{
                            if(i == LINHAS-1 && j == COLUNAS-1)
                                (tab + i*COLUNAS + j)->car = 'X';
                            else
                                (tab + i*COLUNAS + j)->car = '*';
                        }
                    }
                }
            }
        }
    }
    return tab;
}

QUADRADO *elimina_estados_anteriores(QUADRADO *q, pjogadas p){
    int i, posicao;
    char abcd = 'A';
    char abcedario[10];

    for(i=1;i<q->ncolunas;i++,abcd++){
        abcedario[i] = abcd;
    }

    printf("As seguintes coordenadas tem de ser eliminadas...\n\n");
    while(p != NULL){
        for(i=1;i<q->ncolunas;i++,abcd++){
            if(toupper(p->coordenada[1]) == abcedario[i])
                break;
        }
        //apagar os "*" a partir das posicoes calculadas anteriormente
        int l, j;
        for(l=1;l<=(p->coordenada[0] - '0');l++)
            for(j=1;j<=i;j++)
                (q + l*q->ncolunas + j)->car = ' ';

        //proxima coordenada
        p = p->prox;
    }
    return q;
}

void mostrar_tabuleiro(QUADRADO *q){
    int i, j;
    system("cls");
    for(i=0;i<q->nlinhas;i++){
        for(j=0;j<q->ncolunas;j++)
            printf(" %c ", (q + i*q->ncolunas + j)->car);
        printf("\n");
    }
    printf("\n");
}

QUADRADO *retomar_jogo_existente(pjogadas lista){
    QUADRADO *tabuleiro;
    JOGADA jog;
    int modo, njogador, linhas, colunas;
    FILE *f;

    if((f=fopen(nome_fich,"rb")) == NULL){
        printf("Nao existe nenhum jogo anteriormente guardado!\n");
        exit(0);
    }

    fread(&modo, sizeof(int),1,f);
    fread(&linhas, sizeof(int), 1, f);
    fread(&colunas, sizeof(int), 1, f);

    // -1 para manter o mesmo numero de linhas e colunas em relacao ao jogo anterior
    tabuleiro = inicializar_tabuleiro(linhas-1, colunas-1);
    tabuleiro = elimina_estados_anteriores(tabuleiro, lista);
    mostrar_tabuleiro(tabuleiro);

    fclose(f);
    return tabuleiro;
}

void apagar_tabuleiro(QUADRADO *q){
    int i;
    for(i=1;i<q->nlinhas*q->ncolunas;i++)
        free(q+i);
}

int possivel_aumentar(JOGADA *jog){
    if((jog->njogador)%2 == 0){
        //printf("Jogador B quer aumentar o tabuleiro!\n\n");
        if(jog->aumento[1] == 0){
            jog->aumento[1] = 1;
            return 1;
        }else return 0;
    }else{
        //printf("Jogador A quer aumentar o tabuleiro!\n\n");
        if(jog->aumento[0] == 0){
            jog->aumento[0] = 1;
            return 1;
        }else return 0;
    }
}

QUADRADO *aumenta_tabuleiro(QUADRADO *q, JOGADA *jog){

    QUADRADO *tabuleiro_final;
    int linhas, colunas;

    if(possivel_aumentar(jog)){
        linhas = q->nlinhas;
        colunas = q->ncolunas;

        if(linhas <= 8 && colunas <= 10){    //limite máximo é 8 e 10
            //apagar_tabuleiro(q);
            printf("Tabuleiro aumentado c/ sucesso!\n");
            system("pause");
            tabuleiro_final = inicializar_tabuleiro(linhas, colunas);
            return tabuleiro_final;
        }else{
            printf("Chegou ao limite maximo do tabuleiro!\n");
            system("pause");
            return q;
        }
    }else{
        printf("O Jogador ja utilizou a possibilidade de aumentar o tabuleiro!\n");
        system("pause");
        return q;
    }
}

