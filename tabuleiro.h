QUADRADO * inicializar_tabuleiro(int LINHAS, int COLUNAS);
QUADRADO *elimina_estados_anteriores(QUADRADO *q, pjogadas p);
void mostrar_tabuleiro(QUADRADO *q);
QUADRADO *retomar_jogo_existente(pjogadas lista);
void apagar_tabuleiro(QUADRADO *q);
int possivel_aumentar(JOGADA *jog);
QUADRADO *aumenta_tabuleiro(QUADRADO *q, JOGADA *jog);
