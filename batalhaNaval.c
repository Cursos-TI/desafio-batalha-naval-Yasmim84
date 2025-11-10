#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define VALOR_AGUA 0
#define VALOR_NAVIO 3
#define VALOR_HABILIDADE 5
#define TAMANHO_HABILIDADE 5

// Função para aplicar uma matriz de habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                       int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
                       int origem_linha, int origem_coluna) {
    int offset = TAMANHO_HABILIDADE / 2;

    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int linha_tab = origem_linha - offset + i;
            int coluna_tab = origem_coluna - offset + j;

            // Verifica se está dentro dos limites do tabuleiro
            if (linha_tab >= 0 && linha_tab < TAMANHO_TABULEIRO &&
                coluna_tab >= 0 && coluna_tab < TAMANHO_TABULEIRO) {
                if (habilidade[i][j] == 1 && tabuleiro[linha_tab][coluna_tab] == VALOR_AGUA) {
                    tabuleiro[linha_tab][coluna_tab] = VALOR_HABILIDADE;
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa o tabuleiro com água
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = VALOR_AGUA;
        }
    }

    // Posiciona dois navios horizontais/verticais
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[2][4 + i] = VALOR_NAVIO; // Horizontal
        tabuleiro[5 + i][7] = VALOR_NAVIO; // Vertical
    }

    // Posiciona dois navios diagonais
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[i][i] = VALOR_NAVIO; // Diagonal ↘
        tabuleiro[i][TAMANHO_TABULEIRO - 1 - i] = VALOR_NAVIO; // Diagonal ↙
    }

    // Matrizes de habilidades
    int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE] = {0};
    int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE] = {0};
    int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE] = {0};

    // Construção da matriz Cone (forma triangular apontando para baixo)
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (j >= TAMANHO_HABILIDADE / 2 - i && j <= TAMANHO_HABILIDADE / 2 + i) {
                cone[i][j] = 1;
            }
        }
    }

    // Construção da matriz Cruz (linha e coluna central)
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        cruz[i][TAMANHO_HABILIDADE / 2] = 1;
        cruz[TAMANHO_HABILIDADE / 2][i] = 1;
    }

    // Construção da matriz Octaedro (losango)
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (abs(i - TAMANHO_HABILIDADE / 2) + abs(j - TAMANHO_HABILIDADE / 2) <= TAMANHO_HABILIDADE / 2) {
                octaedro[i][j] = 1;
            }
        }
    }

    // Pontos de origem das habilidades no tabuleiro
    int origem_cone_linha = 6, origem_cone_coluna = 2;
    int origem_cruz_linha = 4, origem_cruz_coluna = 4;
    int origem_octa_linha = 7, origem_octa_coluna = 7;

    // Aplica habilidades ao tabuleiro
    aplicarHabilidade(tabuleiro, cone, origem_cone_linha, origem_cone_coluna);
    aplicarHabilidade(tabuleiro, cruz, origem_cruz_linha, origem_cruz_coluna);
    aplicarHabilidade(tabuleiro, octaedro, origem_octa_linha, origem_octa_coluna);

    // Exibe o tabuleiro final
    printf("Tabuleiro com Navios e Habilidades Especiais:\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == VALOR_AGUA) {
                printf("0 ");
            } else if (tabuleiro[i][j] == VALOR_NAVIO) {
                printf("3 ");
            } else if (tabuleiro[i][j] == VALOR_HABILIDADE) {
                printf("5 ");
            }
        }
        printf("\n");
    }

    return 0;
}