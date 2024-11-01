#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>


#define MAX_PALAVRAS 100 // Número máximo de palavras
#define TAM_PALAVRA 100   // Tamanho máximo de cada palavra
#define MAX_COMBINACOES 1000000 // Limitar o número total de combinações

char* ler_proxima_palavra (FILE *pont_dados) { 
    static char palavra[TAM_PALAVRA];
    if (fscanf(pont_dados, "%s", palavra) == 1) {
        return palavra;
    } else {
        return NULL;
    }
}

void imprimir_vetor(char vet[][TAM_PALAVRA], int n) {
    for (int i = 0; i < n; i++) {
        printf(" %s\n", vet[i]);
    }
}

int main(void) {
    FILE *palavras;
    palavras = fopen("palavras.txt", "r");
    
    if (palavras == NULL) {
        printf("Ocorreu um erro ao abrir o arquivo!\n");
        return 1;
    }

    char vetor_palavras[MAX_PALAVRAS][TAM_PALAVRA];
    int n = 0; // Contador real de palavras lidas

    // Ler palavras do arquivo
    while (n < MAX_PALAVRAS) {
        char *palavra = ler_proxima_palavra(palavras);
        if (palavra != NULL) {
            strcpy(vetor_palavras[n], palavra);
            n++;
        } else {
            break; // Sair se não houver mais palavras
        }
    }
    fclose(palavras);

    // Criar todas as possibilidades
    char todas_possibilidades_palavras[MAX_COMBINACOES][TAM_PALAVRA * 5]; // 5 palavras no máximo
    int cont = 0;

    // Testando combinações de 1 a 5 palavras
    for (int i = 1; i <= 5; i++) {
        for (int b = 0; b < n; b++) {
            if (i == 1) {
                sprintf(todas_possibilidades_palavras[cont], "%s", vetor_palavras[b]);
                cont++;
            } else {
                // Gerar combinações de i palavras
                for (int c = 0; c < n; c++) {
                    if (i == 2) {
                        sprintf(todas_possibilidades_palavras[cont], "%s %s", vetor_palavras[b], vetor_palavras[c]);
                        cont++;
                    } else {
                        for (int d = 0; d < n; d++) {
                            if (i == 3) {
                                sprintf(todas_possibilidades_palavras[cont], "%s %s %s", vetor_palavras[b], vetor_palavras[c], vetor_palavras[d]);
                                cont++;
                            } else {
                                for (int e = 0; e < n; e++) {
                                    if (i == 4) {
                                        sprintf(todas_possibilidades_palavras[cont], "%s %s %s %s", vetor_palavras[b], vetor_palavras[c], vetor_palavras[d], vetor_palavras[e]);
                                        cont++;
                                    } else {
                                        for (int f = 0; f < n; f++) {
                                            sprintf(todas_possibilidades_palavras[cont], "%s %s %s %s %s", vetor_palavras[b], vetor_palavras[c], vetor_palavras[d], vetor_palavras[e], vetor_palavras[f]);
                                            cont++;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}