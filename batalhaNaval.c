#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define VALOR_AGUA 0
#define VALOR_NAVIO 3

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa o tabuleiro com água (0)
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = VALOR_AGUA;
        }
    }

    // Coordenadas fixas dos navios
    int linha_h = 2, coluna_h = 4; // Horizontal
    int linha_v = 5, coluna_v = 7; // Vertical
    int linha_d1 = 0, coluna_d1 = 0; // Diagonal ↘
    int linha_d2 = 0, coluna_d2 = 9; // Diagonal ↙

    // Validação de limites
    if (coluna_h + TAMANHO_NAVIO > TAMANHO_TABULEIRO ||
        linha_v + TAMANHO_NAVIO > TAMANHO_TABULEIRO ||
        linha_d1 + TAMANHO_NAVIO > TAMANHO_TABULEIRO ||
        linha_d2 + TAMANHO_NAVIO > TAMANHO_TABULEIRO ||
        coluna_d2 - TAMANHO_NAVIO + 1 < 0) {
        printf("Erro: coordenadas inválidas para posicionar os navios.\n");
        return 1;
    }

    // Verifica sobreposição
    int conflito = 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int posicoes[4][2] = {
            {linha_h, coluna_h + i},
            {linha_v + i, coluna_v},
            {linha_d1 + i, coluna_d1 + i},
            {linha_d2 + i, coluna_d2 - i}
        };

        for (int j = 0; j < 4; j++) {
            int l = posicoes[j][0];
            int c = posicoes[j][1];
            if (tabuleiro[l][c] == VALOR_NAVIO) {
                conflito = 1;
                break;
            }
        }
        if (conflito) break;
    }

    if (conflito) {
        printf("Erro: sobreposição de navios detectada.\n");
        return 1;
    }

    // Posiciona navio horizontal
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha_h][coluna_h + i] = VALOR_NAVIO;
    }

    // Posiciona navio vertical
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha_v + i][coluna_v] = VALOR_NAVIO;
    }

    // Posiciona navio diagonal ↘
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha_d1 + i][coluna_d1 + i] = VALOR_NAVIO;
    }

    // Posiciona navio diagonal ↙
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha_d2 + i][coluna_d2 - i] = VALOR_NAVIO;
    }

    // Exibe o tabuleiro
    printf("Tabuleiro de Batalha Naval:\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}