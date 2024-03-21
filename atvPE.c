#include <stdio.h>
#include <stdlib.h>


int* preencherVetor(int tamanho) {
    int* vetor = (int*)malloc(tamanho * sizeof(int));
    printf("Digite os elementos do vetor:\n");
    for (int i = 0; i < tamanho; i++) {
        int elemento;
        do {
            int repetido = 0;
            printf("Digite o elemento %d: ", i+1);
            scanf("%d", &elemento);
            for (int j = 0; j < i; j++) {
                if (vetor[j] == elemento) {
                    repetido = 1;
                    printf("Este elemento já foi inserido. Por favor, insira outro.\n");
                    break;
                }
            }
      
            if (!repetido) {
                vetor[i] = elemento;
                break;
            }
        } while (1); 
    }
    return vetor;
}

int* calcularUniao(int* vetor1, int tamanho1, int* vetor2, int tamanho2, int* tamanhoUniao) {
    int* uniao = (int*)malloc((tamanho1 + tamanho2) * sizeof(int));
    int i, j, k;


    for (i = 0; i < tamanho1; i++) {
        uniao[i] = vetor1[i];
    }

   
    for (j = 0; j < tamanho2; j++) {
        int existe = 0;
        for (k = 0; k < tamanho1; k++) {
            if (vetor2[j] == vetor1[k]) {
                existe = 1;
                break;
            }
        }
        if (!existe) {
            uniao[i++] = vetor2[j];
        }
    }
    *tamanhoUniao = i;
    return uniao;
}

int* calcularIntersecao(int* vetor1, int tamanho1, int* vetor2, int tamanho2, int* tamanhoIntersecao) {
    int* intersecao = (int*)malloc(tamanho1 * sizeof(int));
    int i, j, k = 0;

    for (i = 0; i < tamanho1; i++) {
        for (j = 0; j < tamanho2; j++) {
            if (vetor1[i] == vetor2[j]) {
                intersecao[k++] = vetor1[i];
                break;
            }
        }
    }
    *tamanhoIntersecao = k;
    return intersecao;
}

int* calcularDiferenca(int* vetor1, int tamanho1, int* vetor2, int tamanho2, int* tamanho_diferenca) {
    int* diferenca = (int*)malloc(tamanho1 * sizeof(int));
    int i, j, k = 0;

    for (i = 0; i < tamanho1; i++) {
        int existe = 0;
        for (j = 0; j < tamanho2; j++) {
            if (vetor1[i] == vetor2[j]) {
                existe = 1;
                break;
            }
        }
        if (!existe) {
            diferenca[k++] = vetor1[i];
        }
    }
    *tamanho_diferenca = k;
    return diferenca;
}

int main() {
    int tamanho1, tamanho2;

    printf("Digite o tamanho do primeiro vetor: ");
    scanf("%d", &tamanho1);
    int* vetor1 = preencherVetor(tamanho1);

    printf("Digite o tamanho do segundo vetor: ");
    scanf("%d", &tamanho2);
    int* vetor2 = preencherVetor(tamanho2);

    int tamanho_uniao, tamanho_intersecao, tamanho_diferenca_A_B, tamanho_diferenca_B_A;

    int* uniao = calcularUniao(vetor1, tamanho1, vetor2, tamanho2, &tamanho_uniao);
    int* intersecao = calcularIntersecao(vetor1, tamanho1, vetor2, tamanho2, &tamanho_intersecao);
    int* diferenca_A_B = calcularDiferenca(vetor1, tamanho1, vetor2, tamanho2, &tamanho_diferenca_A_B);
    int* diferenca_B_A = calcularDiferenca(vetor2, tamanho2, vetor1, tamanho1, &tamanho_diferenca_B_A);

    printf("\nUniao dos dois conjuntos:\n");
    for (int i = 0; i < tamanho_uniao; i++) {
        printf("%d ", uniao[i]);
    }
    printf("\n");

    printf("\nIntersecao dos dois conjuntos:\n");
    for (int i = 0; i < tamanho_intersecao; i++) {
        printf("%d ", intersecao[i]);
    }
    printf("\n");

    printf("\nDiferenca A - B:\n");
    for (int i = 0; i < tamanho_diferenca_A_B; i++) {
        printf("%d ", diferenca_A_B[i]);
    }
    printf("\n");

    printf("\nDiferenca B - A:\n");
    for (int i = 0; i < tamanho_diferenca_B_A; i++) {
        printf("%d ", diferenca_B_A[i]);
    }
    printf("\n");

    free(vetor1);
    free(vetor2);
    free(uniao);
    free(intersecao);
    free(diferenca_A_B);
    free(diferenca_B_A);

    return 0;
}
