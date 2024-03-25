#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define LINHAS 10
#define COLUNAS 10

void imprimirMatriz(int matriz[][COLUNAS], int linhas, int colunas);
void preencherMatriz(int matriz[][COLUNAS], int linhas, int colunas);
void preencherMatrizAleatoria(int matriz[][COLUNAS], int linhas, int colunas);
void calcularSubtotaisColunas(int matriz[][COLUNAS], int linhas, int colunas, int subtotais[]);

int main() {
  int linhas, colunas;
  int matriz[LINHAS][COLUNAS];
  int subtotais[COLUNAS] = {0};

  srand(time(NULL));

  do {
    printf("Qual a quantidade de linhas? (valor entre 1 e %d): ", LINHAS);
    scanf("%d", &linhas);
  } while (linhas < 1 || linhas > LINHAS);

  do {
    printf("Qual a quantidade de colunas? (valor entre 1 e %d): ", COLUNAS);
    scanf("%d", &colunas);
  } while (colunas < 1 || colunas > COLUNAS);

  preencherMatriz(matriz, linhas, colunas);
  calcularSubtotaisColunas(matriz, linhas, colunas, subtotais);
  imprimirMatriz(matriz, linhas, colunas);

  printf("\nSubtotais de cada coluna:\n");
  for (int i = 0; i < colunas; ++i) {
    printf("Coluna %d: %d\n", i + 1, subtotais[i]);
  }

  return 0;
}

void imprimirMatriz(int matriz[][COLUNAS], int linhas, int colunas) {
  for (int i = 0; i < linhas; ++i) {
    for (int j = 0; j < colunas; ++j) {
      printf("%4d ", matriz[i][j]);
    }
    printf("\n");
  }
}

void preencherMatriz(int matriz[][COLUNAS], int linhas, int colunas) {
  printf("Digite os valores para preencher a matriz\n");
  for (int i = 0; i < linhas; ++i) {
    for (int j = 0; j < colunas; ++j) {
      printf("matriz[%d][%d] = ", i + 1, j + 1);
      scanf("%d", &matriz[i][j]);
    }
  }
}

void preencherMatrizAleatoria(int matriz[][COLUNAS], int linhas, int colunas) {
  for (int i = 0; i < linhas; ++i) {
    for (int j = 0; j < colunas; ++j) {
      matriz[i][j] = rand() % (2 * linhas * colunas) + 1;
    }
  }
}

void calcularSubtotaisColunas(int matriz[][COLUNAS], int linhas, int colunas, int subtotais[]) {
  for (int j = 0; j < colunas; ++j) {
    subtotais[j] = 0;
    for (int i = 0; i < linhas; ++i) {
      subtotais[j] += matriz[i][j];
    }
  }
}
