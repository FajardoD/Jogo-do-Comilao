#include "includes.h"

guardar_tabuleiro_inicial(QUADRADO *tabuleiro){
    FILE *f;
    int i, j;

    f=fopen(nome_fich_txt,"a");
    if(f == NULL){
        printf("Erro ao escrever p/ o ficheiro de texto!");
        return;
    }

    fprintf(f,"Tabuleiro inicial: L= %d & C= %d\n", (tabuleiro->nlinhas)-1, (tabuleiro->ncolunas)-1);
    for(i=0;i<tabuleiro->nlinhas;i++){
        for(j=0;j<tabuleiro->ncolunas;j++)
            fprintf(f," %c ", (tabuleiro + i*tabuleiro->ncolunas + j)->car);
        fprintf(f,"\n");
    }
    fprintf(f,"             ||         \n");
    fprintf(f,"             ||         \n");
    fprintf(f,"             \\/         \n\n");


    fclose(f);
}

void guardar_sucessao(QUADRADO *tabuleiro, JOGADA *jog){
    FILE *f;
    int i, j;

    f=fopen(nome_fich_txt,"a");
    if(f == NULL){
        printf("Erro ao escrever p/ o ficheiro de texto!");
        return;
    }

    fprintf(f,"Jogador %d -> ", (jog->njogador % 2)+1);
    for(i=0;i<2;i++)
        fprintf(f,"%c",jog->coordenada[i]);
    fprintf(f,"\n");
    for(i=0;i<tabuleiro->nlinhas;i++){
        for(j=0;j<tabuleiro->ncolunas;j++)
            fprintf(f," %c ", (tabuleiro + i*tabuleiro->ncolunas + j)->car);
        fprintf(f,"\n");
    }
    fprintf(f,"             ||         \n");
    fprintf(f,"             ||         \n");
    fprintf(f,"             \\/         \n\n");


    fclose(f);
}

int indicar_modo_de_jogo_anterior(){
    FILE *f;
    int modo;

    if((f=fopen(nome_fich,"rb")) == NULL){
        printf("Nao existe nenhum jogo anteriormente guardado!\n");
        exit(0);
    }

    fread(&modo, sizeof(int),1,f);

    fclose(f);
    return modo;
}
