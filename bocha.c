#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <ctype.h>
#define TAM 10

void gerar_matriz(char matriz[][TAM]) {
    int i,j;
    for(i = 0;i < TAM; i++ ) {
       for(j = 0;j < TAM; j++ ) {
            matriz[i][j] = ' ';
       }
    }
}

char converter_char_int(char indice) {
    char a, letra;
    a = 'A';
    letra = toupper(indice) - a;

    return letra;
}

void exibir(char matriz[][TAM]) {
    int i, j, x;
    int vetor_int[TAM];
    char vetor_char[TAM] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

    x = TAM;

    for(i = 0 ;i < TAM;i++) {
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

int sorteio(){
    int x;
    srand((unsigned)time(NULL));

    x = rand() % 10;
    return x;
}

typedef struct {
    char nome[51];
    int jogadas, pontos;
} jogador;

int main() {
    char matriz[TAM][TAM];
    int n_jogadores, inicia_jogo, i;
    jogador jogadores[4];

    setlocale(LC_ALL, "");

    gerar_matriz(matriz);
    printf("\n          BEM VINDO AO BOCHA SIMULATOR\n\n");
    exibir(matriz);

    printf("\n\n");
    inicia_jogo = 0;
    do {
        printf("Informe o número de joadores\n");
        scanf("%d", &n_jogadores);

        if(n_jogadores == 2 || n_jogadores == 4) {
            inicia_jogo = 1;
        }
    } while(inicia_jogo != 1);

    for (i = 0; i < n_jogadores; i++) {
        printf("Informe o nome do jogador %d\n", i+1);
        scanf("%s", jogadores[i].nome);
    }

    // AQUI É JOGADO O BALIN
    matriz[sorteio()][sorteio()] = 'X';
    // LIMPA A TELA
    system("cls");
    printf("\n\n               BALIN JOGADO\n\n");
    exibir(matriz);
    return 0;
}
