#include "includes.h"

int main(){

	int linhas, colunas, opcao;
	QUADRADO *tabuleiro;
	JOGADA jogador;

	//Inicializacao de aumentação de tabuleiro para ambos os jogadores
    jogador.aumento[0] = 0;
    jogador.aumento[1] = 0;

	//0 para avisar que se trata ainda de um jogo sem vencedor
	jogador.ganho = 0;

	//lista ligada para manutenção das jogadas
	pjogadas lista = NULL;

	opcao = menu();

	if(opcao !=3){
        do{
            do{
                fflush(stdin);
                printf("Introduza o numero de linhas: ");
                scanf("%d", &linhas);
            } while (isdigit(linhas) || linhas < 4 || linhas > 8);

            do{
                fflush(stdin);
                printf("Introduza o numero de colunas: ");
                scanf("%d", &colunas);
            } while (isdigit(colunas) || colunas < 6 || colunas > 10);
        } while (linhas >= colunas && printf("Nr de linhas tem de ser superior ao nr de linhas!\n\n"));
        //eliminar o conteúdo do ficheiro de texto
        remove(nome_fich_txt);
        //Inicializacao para ser o jogador A a comecar
        jogador.njogador = 1;
        //Limites do tabuleiro aceites + inicialização do tabuleiro
        tabuleiro = inicializar_tabuleiro(linhas, colunas);
        //para guardar o tabuleiro inicial no ficheiro de texto
        guardar_tabuleiro_inicial(tabuleiro);
        mostrar_tabuleiro(tabuleiro);
	}else{
	    lista = criar_lista_sucessao_estados(lista, &jogador);
        tabuleiro = retomar_jogo_existente(lista);
        opcao = indicar_modo_de_jogo_anterior();
	}

    do{
        pedir_coordenada(&jogador, opcao, lista);
        validar_jogada(tabuleiro, &jogador, opcao);
        if(jogador.valido == 1)
            printf("Coordenada nao reconhecida!\n");
        else{
            if(jogador.valido == 2)
                printf("Nao existe comida nesse campo!\n");
            else{
                if(jogador.valido == 3){
                    interromper_jogo(tabuleiro, lista, opcao);
                    break;
                }else{
                    if(jogador.valido == 4){
                        mostrar_sucessao_estados(lista);
                        system("pause");
                        mostrar_tabuleiro(tabuleiro);
                    }else{
                        if(jogador.valido == 5){
                            tabuleiro = aumenta_tabuleiro(tabuleiro, &jogador);
                            tabuleiro = elimina_estados_anteriores(tabuleiro, lista);
                            mostrar_tabuleiro(tabuleiro);
                        }else{
                            guardar_sucessao(tabuleiro, &jogador);
                            lista = manutencao_jogadas(lista, &jogador);
                            anunciar_vencedor(tabuleiro, &jogador, lista);
                        }
                    }
                }
            }
        }
    }while(jogador.ganho == 0);

    //apagar_tabuleiro(tabuleiro);
    apagar_lista(lista);
	return 0;
}
