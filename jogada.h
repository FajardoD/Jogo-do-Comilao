int menu();
void mostrar_comandos_validos_menu();
void pedir_coordenada(JOGADA *jog, int modo, pjogadas lista);
void interromper_jogo(QUADRADO *tabuleiro, pjogadas p, int modo);
void validar_jogada(QUADRADO *tabuleiro, JOGADA *jog, int modo);
void mostrar_sucessao_estados(pjogadas p);
void anunciar_vencedor(QUADRADO *q, JOGADA *vencedor, pjogadas lista);
