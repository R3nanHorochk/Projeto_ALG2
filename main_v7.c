#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

#define MAXIMO_PALAVRAS 15
#define MAXIMO_COMBINACOES 759375
#define TAMANHO_PALAVRAS 58

char* ler_proxima_palavra(FILE *pont_dados) { 
    static char palavra[100];
    if (fscanf(pont_dados, "%s", palavra) == 1) {
        return palavra;
    } else {
        return NULL;
    }
}

void guardar_possibilidades(char name1[], char name2[], char name3[], char name4[], char name5[]) {
    FILE *possibilidades = fopen("todas_possibilidades.txt", "a");
    if (possibilidades == NULL) {
        printf("Erro ao abrir o arquivo para gravação de possibilidades!\n");
    } else {
        fprintf(possibilidades, "%s %s %s %s %s\n", name1, name2, name3, name4, name5);
        fclose(possibilidades);
    }
}

void guardar_hash(char hash_hex[]) {
    FILE *hashes = fopen("hashes.txt", "a");
    if (hashes == NULL) {
        printf("Erro ao abrir o arquivo para gravação de hashes!\n");
    } else {
        fprintf(hashes, "%s\n", hash_hex);
        fclose(hashes);
    }
}

void gerar_combinacoes (char vetor_palavras[][TAMANHO_PALAVRAS], int n) {
    int cont = 0;
    bool parar = false;
  
    for (int b = 0; b < n && !parar; b++) {
        for (int c = 0; c < n && !parar; c++) {
            for (int d = 0; d < n && !parar; d++) {
                for (int e = 0; e < n && !parar; e++) {
                    for (int f = 0; f < n && !parar; f++) {
                        if (cont < MAXIMO_COMBINACOES) {
                            cont++;
                            guardar_possibilidades(vetor_palavras[b], vetor_palavras[c], vetor_palavras[d], vetor_palavras[e], vetor_palavras[f]);
                        } else {
                            parar = true;
                            break;
                        }
                    }
                }
            }
        }
    }

}

void gerar_hashes() {
  
}

int main(void) {
  FILE *words = fopen("palavras.txt", "r");

  if (words == NULL) {
    printf("Erro ao abrir o arquivo de palavras!\n");
      return 1;
  } 

  char vetor_palavras[MAXIMO_PALAVRAS][TAMANHO_PALAVRAS] = {{""}};
  int contador_palavras = 0;
  char *palavra;

  // Lendo as palavras do arquivo para o vetor
  for (int i = 0; i < MAXIMO_PALAVRAS; i++) {
    palavra = ler_proxima_palavra(words);
    if (palavra != NULL) {
      strcpy(vetor_palavras[i], palavra);
    } else {
      break;
    }
  }
  fclose(words);

  int n = MAXIMO_PALAVRAS;

  gerar_combinacoes(vetor_palavras, n);

    // Gerando hash para cada linha do arquivo de combinações
    FILE *possibilidades_senhas = fopen("todas_possibilidades.txt", "r");
    if (possibilidades_senhas == NULL) {
        printf("Erro ao abrir o arquivo de possibilidades para leitura!\n");
        return 1;
    }

    SHA512_CTX ctx;
    unsigned char hash[SHA512_DIGEST_LENGTH];
    char hash_hex[SHA512_DIGEST_LENGTH * 2 + 1];

    // Calcula a hash SHA512 de cada linha do arquivo
    while ((palavra = ler_proxima_palavra(possibilidades_senhas)) != NULL) {
        SHA512_Init(&ctx);
        SHA512_Update(&ctx, palavra, strlen(palavra));
        SHA512_Final(hash, &ctx);

        // Converte a hash para hexadecimal
        for (int i = 0; i < SHA512_DIGEST_LENGTH; i++) {
            sprintf(hash_hex + (i * 2), "%02x", hash[i]);
        }
        hash_hex[SHA512_DIGEST_LENGTH * 2] = '\0';

        // Armazena o hash
        guardar_hash(hash_hex);
    }

    fclose(possibilidades_senhas);
    return 0;
}
