#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#define TAM 10

//  Gerar a matriz
void gerar_matriz(char matriz[][TAM]) {
    int i,j;
    for(i = 0;i < TAM; i++ ) {
       for(j = 0;j < TAM; j++ ) {
            matriz[i][j] = ' ';
       }
    }
}

//  Converter caractere em inteiro
int conv_char_int(char indice) {
    switch (indice)
    {
        case 'A' :
        case 'a' :
            return 0;
        break;
        case 'B' :
        case 'b' :
            return 1;
        break;
        case 'C' :
        case 'c' :
            return 2;
        break;
        case 'D' :
        case 'd' :
            return 3;
        break;
        case 'E' :
        case 'e' :
            return 4;
        break;
        case 'F' :
        case 'f' :
            return 5;
        break;
        case 'G' :
        case 'g' :
            return 6;
        break;
        case 'H' :
        case 'h' :
            return 7;
        break;
        case 'I' :
        case 'i' :
            return 8;
        break;
        case 'J' :
        case 'j' :
            return 9;
        break;
    }
}

//  Exibe a matriz
void exibir(char matriz[][TAM]) {
    int i, j, x;
    int vetor_int[TAM];
    char vetor_char[TAM] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

    x = TAM;

    for(i = 0; i < TAM; i++) {
        vetor_int[i] = x ;
        x--;
    }
    printf(" --------------------------------------------\n");
    for(i = 0;i < TAM; i++ ) {
        if(i == 0) {
            printf("| %d", vetor_int[i]);
        } else {
            printf("| 0%d", vetor_int[i]);
        }

        for(j = 0;j < TAM; j++ ) {
            printf(" | %c", matriz[i][j]);
        }

        printf(" |\n --------------------------------------------\n");
    }

    for(i = 0; i < TAM ; i++) {
        if(i == 0) {
            printf("|    |");
        }
        printf(" %c |", vetor_char[i]);

    }
    printf("\n --------------------------------------------");
}

void sementeRand() {
    srand((unsigned)time(NULL));
}

//  Sorteia o bolim
int sorteio(){
    int x, y;
    x = rand() % 10;

    return x;
}

//  Limpa a tela
void limpa_tela() {
    system("cls");
}

// CALCULA COLUNA DA JOGADA
int colunaErro(int coluna) {
    int x, y;

    if (coluna == 9) {
        y = (rand() % 2) - 1;
    } else if (coluna == 0) {
        y = rand() % 2;
    } else {
        y = (rand() % 3) - 1;
    }

    x = coluna + y;
    return x;
}

// CALCULA LINHA DA JOGADA
int linhaErro(int linha) {
    int x, y;

    if (linha == 10) {
        y = (rand() % 3) - 2;
    } else if (linha == 9) {
        y = (rand() % 4) - 2;
    } else if (linha == 1) {
        y = (rand() % 3);
    } else if (linha == 2) {
        y = (rand() % 4) - 1;
    } else {
        y = (rand() % 5) - 2;
    }

    x = linha + y;
    return x;
}

//  STRUCT QUE ARMAZENA OS DADOS DE CADA JOGADOR
typedef struct {
    char nome[51];
    int jogadas, pontos;
} jogador;

//  verifica qual jogador está fazendo a jogada
int verifica_jogador(int jogada, int n_jogadores){
    int j;
    if (n_jogadores == 2) {
        if ((jogada%2) == 0) {
            j = 0;
        } else {
            j = 1;
        }
    } else {
        switch(jogada){
            case 0:
            case 4:
                j = 0;
                break;
            case 1:
            case 5:
                j = 1;
                break;
            case 2:
            case 6:
                j = 2;
                break;
            case 3:
            case 7:
                j = 3;
                break;
        }
    }

    return j;
}

// movimenta as bochas quando ocorre o deslocamento direto
void deslocamento_direto_cima(char matriz[][TAM], int coluna, int linha, int espacos_vazio){
	char nada;
    int move, i, j, desloca;

	nada = ' ';
    j = espacos_vazio + 2;
    if (espacos_vazio == 2) {
    	desloca = 3;
    } else {
    	desloca = 1;
    }

	// verifica se a partir da linha-j existe
	if ((linha - j) >= 0) {
		// verifica se a partir da linha-j existe espaço em branco para mover a bocha
        move = -1;
        for (i = (linha-j); i >= 0; i--){
            if (matriz[i][coluna] == nada) {
                move = i;
            }
        }

        // se pode mover então move uma por uma se não move o que pode de acordo com
        // os espaços vazios que possui
        if (move >= 0) {
            for(i = move; i <= (linha - j); i++){
                // move as bocha uma por uma até o espaço em branco
                matriz[i][coluna] = matriz[i+1][coluna];
            }
            matriz[linha - desloca][coluna] = matriz[linha][coluna];
        } else {
            matriz[linha - espacos_vazio][coluna] = matriz[linha][coluna];
        }
    } else {
        matriz[linha - espacos_vazio][coluna] = matriz[linha][coluna];
    }
}

void deslocamento_direto_baixo(char matriz[][TAM], int linha, int coluna, char letra) {
    int i, j, move;
    char nada;

	nada = ' ';
    // procura por uma posição vazia
    move = -1;
    for (i = (linha + 1); i < TAM; i++){
        if (matriz[i][coluna] == nada) {
            move = i;
        }
    }

	if (move <= 9) {
        for(i = move; i >= (linha + 2); i--){
            // move as bocha uma por uma até o espaço em branco
            matriz[i][coluna] = matriz[i-1][coluna];
        }
        matriz[linha + 1][coluna] = matriz[linha][coluna];
    } else {
        matriz[linha + 1][coluna] = matriz[linha][coluna];
    }
}

void deslocamento_direto(char matriz[][TAM], int coluna, int linha, char letra) {
    char nada;
    int espacos_vazio, move, i;

    nada = ' ';
    espacos_vazio = 0;
    if (matriz[linha][coluna] != nada) {
    	// verifica quantas linhas vazias tem depois da posição que a bocha foi lançada
        for (i = (linha -1); i >= 0; i--){
            if (matriz[i][coluna] == nada) {
                espacos_vazio++;
            } else {
                break;
            }
        }

        // se linha menor que 3 vai avançar de acordo com as casas disponiveis
        if (linha >= 3) {
            if (espacos_vazio == 0) {
                deslocamento_direto_cima(matriz, coluna, linha, espacos_vazio);
            } else if(espacos_vazio == 1) {
                deslocamento_direto_cima(matriz, coluna, linha, espacos_vazio);
            } else if(espacos_vazio == 2) {
            	deslocamento_direto_cima(matriz, coluna, linha, espacos_vazio);
            } else if(espacos_vazio >= 3) {
                // se tiver 3 ou mais espaços em branco a bocha que estava na linha simplismente avança os 3 espaços
                matriz[linha - 3][coluna] = matriz[linha][coluna];
            }
        } else if (linha == 2) {
			if (espacos_vazio == 0) {
                deslocamento_direto_baixo(matriz, linha, coluna, letra);
            } else if(espacos_vazio == 1) {
                move = -1;
                for (i = (linha-1); i >= 0; i--){
                    if (matriz[i][coluna] == nada) {
                        move = i;
                    }
                }

                if (move >= 0) {
                    for(i = move; i <= (linha - 1); i++){
                        // move as bocha uma por uma até o espaço em branco
                        matriz[i][coluna] = matriz[i+1][coluna];
                    }
                } else {
                    matriz[linha][coluna] = matriz[linha][coluna];
                }
            } else if(espacos_vazio == 2) {
                matriz[linha - 1][coluna] = matriz[linha][coluna];
            }
        } else if (linha == 1) {
			if (espacos_vazio == 0) {
                deslocamento_direto_baixo(matriz, linha, coluna, letra);
            } else if(espacos_vazio == 1) {
                matriz[linha - 1][coluna] = matriz[linha][coluna];
            }
        } else if (linha == 0) {
			deslocamento_direto_baixo(matriz, linha, coluna, letra);
        }
    }

    matriz[linha][coluna] = letra;
}



// Pede para que o jogador faça uma jogada
void solicita_jogada(char matriz[][TAM], int jogada, int n_jogadores, jogador jogadores[2]){
    char coluna, letra, a;
    int linha, j, linha_desviada, l, coluna_convertida, c;

    j = verifica_jogador(jogada, n_jogadores);

    printf("\n\n");
    printf("%s em qual linha pretende jogar a bocha?  ", jogadores[j].nome);
    scanf("%d", &linha);
    printf("%s em qual coluna pretende jogar a bocha?  ", jogadores[j].nome);
    scanf(" %c", &coluna);

//  desvia a bocha da linha conforme a regra (-2, -1, 0, 1 e 2)
    linha_desviada = linhaErro(linha);
    l = 10 - linha_desviada;

//  desvia a bocha da coluna conforme a regra (-1, 0 e 1)
    coluna_convertida = conv_char_int(coluna);
    c = colunaErro(coluna_convertida);

    a = 'a';
//  adiciona a letra corespondente ao jogador na matriz
    letra = a + j;

    deslocamento_direto(matriz, c, l, letra);
}

// VERIFICA A pONTUAÇÃO TOTAL
void verifica_pontuacao(char matriz[][TAM],jogador jogadores[2]) {
    int i, j, z, y, bolin_lin, bolin_col, form_euclidiana, booleano;

    booleano = 0;

    // PROCURA A LOCALIZAÇÃO DO BALIN
    for (i = 0; i < TAM && !booleano; i++) {
        for (j = 0; j < TAM && !booleano; j++) {
            if (matriz[i][j] == 'X') {
                bolin_lin = i;
                bolin_col = j;
                booleano = 1;
            }
        }
    }

    // CALCULA A PONTUAÇÃO TOTAL
    for(z = 0; z < TAM; z++) {
        for(y = 0; y < TAM; y++) {
            if(matriz[z][y] == 'a') {
                form_euclidiana = sqrt(pow(z - bolin_lin, 2) + pow(y - bolin_col, 2));
                if (form_euclidiana == 1) {
                    jogadores[0].pontos += 2;
                } else {
                    jogadores[0].pontos++;
                }
            }

            if(matriz[z][y] == 'b') {
                form_euclidiana = sqrt(pow(z - bolin_lin, 2) + pow(y - bolin_col, 2));
                if (form_euclidiana == 1) {
                    jogadores[1].pontos += 2;
                } else {
                    jogadores[1].pontos++;
                }
            }
        }
    }
}

void inicia_game(char matriz[][TAM]){
    char coluna;
    int n_jogadores, inicia_jogo, i, j, k, linha;
    jogador jogadores[2];

    sementeRand();
    n_jogadores = 2;

    gerar_matriz(matriz);
    printf("\n          BEM VINDO AO BOCHA SIMULATOR\n\n");
    exibir(matriz);
    printf("\n\n");

//  Informar nome do jogador
    for (i = 0; i < n_jogadores; i++) {
        printf("Informe o nome do jogador %d : ", i+1);
        gets(jogadores[i].nome);
        jogadores[i].pontos = 0;
        jogadores[i].jogadas = 0;
        printf("\n");
    }

//  Joga-se o bolim
    matriz[sorteio()][sorteio()] = 'X';
    limpa_tela();
    printf("\n\n--------->>> BOLIM JOGADO COM SUCESSO\n\n");
    exibir(matriz);

//  Solicita que sejam feitas as jogadas
    for(i = 0; i < 8; i++) {
        solicita_jogada(matriz, i, n_jogadores, jogadores);
        j = verifica_jogador(i, n_jogadores);
        // aumenta em um o numero de jogadas
        jogadores[j].jogadas += 1;

        limpa_tela();
        exibir(matriz);
        printf("\n");

        // exibe o numero de jogadas de cada jogador
        for(k = 0; k < n_jogadores; k++){
            printf("\nO jogador %s já fez %d jogadas", jogadores[k].nome, jogadores[k].jogadas);
        }
    }

    // Verifica a pontuação
    verifica_pontuacao(matriz,jogadores);

    int houve_ven = 0, venc_a_b;

    limpa_tela();
    exibir(matriz);

    // Verifica o vencedor ou se houve empate
    if (jogadores[0].pontos > jogadores[1].pontos) {
        houve_ven = 1;
        venc_a_b = 0;
    } else if(jogadores[0].pontos < jogadores[1].pontos) {
        houve_ven = 1;
        venc_a_b = 1;
    }

    //DECLARAÇÃO FINAL
    printf("\n====================================================\n\n\n");
    printf("                  PONTUACAO FINAL                         ");
    for(k = 0; k < n_jogadores; k++) {
        printf("\n\nJogador %s :  %d pontos \n", jogadores[k].nome,jogadores[k].pontos);
    }

    if (houve_ven == 0) {
        printf("\n\nO BOCHA SIMULATOR TERMINOU EMPATADO !! ");
    } else if (houve_ven == 1 && venc_a_b == 0) {
        printf("\n\nO GRANDE VENCEDOR DE BOCHA SIMULATOR FOI  %s !!!!", jogadores[0].nome);
    } else if (houve_ven == 1 && venc_a_b == 1){
        printf("\n\nO GRANDE VENCEDOR DE BOCHA SIMULATOR FOI  %s !!!!", jogadores[1].nome);
    }
    printf("\n====================================================\n\n\n");
}

int main() {
    char matriz[TAM][TAM], coluna;
    int fazer, fim;
    setlocale(LC_ALL, "");

    for(;;){
        //  Início do jogo
        inicia_game(matriz);

        printf("Presione 1 para reiniciar o jogo ou qualquer outra tecla para sair\n");
        scanf("%d", &fazer);

        if (fazer == 1) {
            limpa_tela();
        } else {
            break;
        }
    }

    return 0;
}
