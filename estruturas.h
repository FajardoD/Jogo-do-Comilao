typedef struct{
    int nlinhas;
    int ncolunas;
	//int lin;
	//int col;
	char car;
}QUADRADO;

typedef struct jogador JOGADA, *pjogadas;
struct jogador{
    int njogador;
    char coordenada[2];
    int valido; //0 valido; 1 nao reconhecido; 2 nao existe comida; 3 interrompe jogo; 4 mostra jogadas; 5 aumenta tabuleiro
    int ganho;  //0 ainda nao ganharam; 1 há vencedor
    int aumento[2]; //0 jogador A; 1 jogador B
    pjogadas prox;
};

pjogadas manutencao_jogadas(pjogadas p, JOGADA *jog);
pjogadas criar_lista_sucessao_estados(pjogadas lista, JOGADA *jog);
void apagar_lista(pjogadas lista);
