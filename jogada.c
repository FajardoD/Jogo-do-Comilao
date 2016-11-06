#include "includes.h"

int menu(){
    int op;

	do{
        printf("|Bem-vindo ao jogo do comilao|\n");
        printf("------------------------------\n\n");

        printf("Modo de jogo\n\n\n");
        printf("1- Humano vs Humano\n");
        printf("2- Humano vs Computador\n");
        printf("3- Retomar jogo existente\n\n");
        printf("Sua escolha: ");
        scanf(" %d", &op);

        switch(op){
            case 1: return 1;
            case 2: return 2;
            case 3: return 3;
            default : break;
        }
        system("cls");
        fflush(stdin);
    }while(!isdigit(op) || op != 1 || op != 2 || op != 3);
}

void mostrar_comandos_validos_menu(){
    printf(" ---- Comandos validos ----- \n");
    printf("| A/a - Aumentar tabuleiro  |\n");
    printf("| H/h - Historico de jogadas|\n");
    printf("| I/i - Interromper jogo    |\n");
    printf("-----------------------------\n\n\n");
}

void pedir_coordenada(JOGADA *jog, int modo, pjogadas lista){
    int i;
    //modo = 1 se for contra pessoa existente; modo = 2 se for contra o PC
    //se lista estiver vazia é porque nao é um jogo que foi retomado, caso contrario retoma o jogo no jogador que era a jogar
    //if(lista == NULL){
    if(modo == 1 && lista != NULL){
        while(lista != NULL){
            i = lista->njogador;
            lista = lista->prox;
        }
        if(i % 2 == 0){
            mostrar_comandos_validos_menu();
            printf("A sua vez de jogar, Jogador B!\n");
        }else{
            mostrar_comandos_validos_menu();
            printf("A sua vez de jogar, Jogador A!\n");
        }
        printf("Coordenada: ");
        scanf(" %s", &jog->coordenada);
    }else{
        if(modo == 1){
            if((jog->njogador) % 2 == 0){
                mostrar_comandos_validos_menu();
                printf("A sua vez de jogar, Jogador B!\n");
            }else{
                mostrar_comandos_validos_menu();
                printf("A sua vez de jogar, Jogador A!\n");
            }
            printf("Coordenada: ");
            scanf(" %s", &jog->coordenada);
        }else if(modo == 2){
                if((jog->njogador) % 2){
                    mostrar_comandos_validos_menu();
                    printf("A sua vez de jogar, Jogador A!\n");
                    printf("Coordenada: ");
                    scanf(" %s", &jog->coordenada);
                }else{
                    printf("O computador selecionou a seguinte\n");
                    printf("Coordenada: ");
                }
            }
    }
}

void interromper_jogo(QUADRADO *tabuleiro, pjogadas p, int modo){
    char tecla_interromper, opcao;
    int i, nbytes = 0;

    printf("O jogo foi interrompido pelo utilizador!\n\n");
    printf("Deseja guardar o jogo atual [S/N]? ");
    scanf(" %c", &tecla_interromper);

    if(toupper(tecla_interromper) == 'S'){
        //guardar_interrupcao_jogo
        FILE *f;
        if((f=fopen(nome_fich,"wb")) == NULL){
            printf("Erro ao abrir ficheiro binario para escrita!\n");
            return;
        }

        fwrite(&modo, sizeof(int),1,f);
        fwrite(&tabuleiro->nlinhas, sizeof(int),1,f);
        fwrite(&tabuleiro->ncolunas, sizeof(int),1,f);

        while(p != NULL){
            nbytes = fwrite(p, sizeof(JOGADA),1,f);
            p = p->prox;
        }

        if(nbytes != 0)
            printf("Guardado c/ sucesso.\n");
        else printf("Guardado sem sucesso.\n");

        fclose(f);
    }else{
        printf("Jogo nao foi guardado.\n");
    }
}

void validar_jogada(QUADRADO *tabuleiro, JOGADA *jog, int modo){
    int i, posicao;
    char abcd = 'A';
    char abcedario[10];
    srand(time(NULL));

    if(strlen(jog->coordenada) == 1){
        //Interrompe o jogo
        if(toupper(jog->coordenada[0]) == 'I'){
            jog->valido = 3;
            return;
        }

        //Dá sucessao de estados (tipo hint)
        if(toupper(jog->coordenada[0]) == 'H'){
            jog->valido = 4;
            return;
        }

        //Possibilidade de aumentar tabuleiro
        if(toupper(jog->coordenada[0]) == 'A'){
            jog->valido = 5;
            return;
        }
    }

    for(i=1;i<tabuleiro->ncolunas;i++,abcd++){
        abcedario[i] = abcd;
    }

    //é porque esta a jogar contra o PC
    if((jog->njogador)%2 == 0 && modo == 2){
        //sorteia coordenadas random para o jogador PC enquanto for diferente do caracter '*'
        do{
            jog->coordenada[0] = (rand() % (tabuleiro->nlinhas-1) + 1) + '0';
            i = rand() % (tabuleiro->ncolunas-1) + 1;
            jog->coordenada[1] = abcedario[i];
            posicao = atoi(&jog->coordenada[0]) * tabuleiro->ncolunas + i;
        }while((tabuleiro + posicao)->car != '*');
        printf("%s\n", jog->coordenada);
        system("pause");
    }

    //controlar se as coordenadas do utilizador estao dentro dos limites do tabuleiro
    if(jog->coordenada[0] >= '1' && jog->coordenada[0] <= (tabuleiro->nlinhas)-1 + '0'){
        for(i=1,jog->valido=1;i<tabuleiro->ncolunas && jog->valido != 0;i++){
            if(toupper(jog->coordenada[1]) == abcedario[i]){
                //ver se há comida no quadrado
                posicao = (jog->coordenada[0] - '0') * tabuleiro->ncolunas + i;    //posicao para onde o utilizador aponta, e come a comida se houver
                if((tabuleiro + posicao)->car == '*'){
                    //(tabuleiro + posicao)->car = ' ';

                        int l, j;
                        for(l=1;l<=(jog->coordenada[0] - '0');l++)
                            for(j=1;j<=i;j++)
                                (tabuleiro + l*tabuleiro->ncolunas + j)->car = ' ';


                    jog->valido = 0;
                    jog->njogador++;
                    mostrar_tabuleiro(tabuleiro);
                }else{
                    if((tabuleiro + posicao)->car == 'X'){
                        jog->valido = 0;
                        jog->ganho = 1;
                        return;
                    }else{
                        jog->valido = 2;
                        return;
                    }
                }
            }else{
                //Coordenada nao reconhecida
                jog->valido = 1;
            }
        }
    }else{
        //Coordenada nao reconhecida
        jog->valido = 1;
    }
}

void mostrar_sucessao_estados(pjogadas p){
    int i=0;
    if(p == NULL){
        printf("Ainda nao foram guardadas coordenadas!\n");
    }else{
        printf("\n\nSucessao de estados:\n\n");
        while(p != NULL){
            if(i%2 == 0)
                printf("%d.Jogada\t Jogador A-> Coordenada: %s\n", ++i, p->coordenada);
            else printf("%d.Jogada\t Jogador B-> Coordenada: %s\n", ++i, p->coordenada);
            p = p->prox;
        }
    }
}

void anunciar_vencedor(QUADRADO *q, JOGADA *vencedor, pjogadas lista){
    int i, j;
    int contador=0;

    for(i=0;i<q->nlinhas;i++){
        for(j=0;j<q->ncolunas;j++)
            if((q + i*q->ncolunas + j)->car == '*')
                contador++;
    }

    if(vencedor->ganho == 1 || contador == 0){
        vencedor->ganho = 1;
        if(vencedor->njogador % 2)
            printf("Perdeu Jogador A!\n");
        else printf("Perdeu Jogador B!\n");
    }else vencedor->ganho = 0;
}
