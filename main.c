#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>


char* ler_proxima_palavra (FILE *pont_dados) { 
    static char palavra[100];
    if (fscanf(pont_dados, "%s", palavra) == 1) {
        return palavra;
    } else {
        return NULL;
    }

}

void imprimir_vetor(char vet[][100], int n) {
  for (int i=0; i<n; i++) {
    printf(" %s ", vet[i]);
    printf("\n");
  }
}




int main(void) {
  
  FILE *palavras;
  palavras = fopen("palavras.txt", "r");
  int n = 24;
  char vetor_palavras[n][100];


  if (palavras == NULL) {
  printf("Ocorreu um erro!");
  return 1;
  }
  else {
    for (int i=0; i<n; i++) {
      char *palavra = ler_proxima_palavra(palavras);
      if (palavra != NULL) {
        strcpy(vetor_palavras[i], palavra); //copiando a palavra e colocando no vetor de palavras
      } else {
        break;
      }
    }
  }
  fclose(palavras);

//printando o vetor de palavras
//imprimir_vetor(vetor_palavras, n);

//criando toddas as possibilidades palavras, utilizando inicialmente somente 2 palavras
char todas_possibilidades_palavras[n*n+n][1000000];
int cont = 0;

//testando todas as possibilidades para uma palavra
for (int l=0; l<n; l++) {
  sprintf(todas_possibilidades_palavras[cont], "%s", vetor_palavras[l]);
  cont++;
}
//testando todas as possibilidades para duas palavras
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      sprintf(todas_possibilidades_palavras[cont], "%s %s", vetor_palavras[i], vetor_palavras[j]);
      cont++;
    }
  }
//testando para 3 palavras
for (int b=0; b<n; b++) {
  for (int c=0; c<n; c++) {
    for(int d=0; d<n; d++) {
      sprintf(todas_possibilidades_palavras[cont], "%s %s %s", vetor_palavras[b], vetor_palavras[c], vetor_palavras[d]);
      cont++;
    }
  }
}
//testando para 4 palavras
for (int b=0; b<n; b++) {
  for (int c=0; c<n; c++) {
    for(int d=0; d<n; d++) {
      for (int e=0; e<n; e++) {
        sprintf(todas_possibilidades_palavras[cont], "%s %s %s %s", vetor_palavras[b], vetor_palavras[c], vetor_palavras[d], vetor_palavras[e]);
        cont++;
      }
    }
  }
}
//testando para 5 palavras
for (int b=0; b<n; b++) {
  for (int c=0; c<n; c++) {
    for(int d=0; d<n; d++) {
      for (int e=0; e<n; e++) {
        for (int f=0; f<n; f++) {
          sprintf(todas_possibilidades_palavras[cont], "%s %s %s %s %s", vetor_palavras[b], vetor_palavras[c], vetor_palavras[d], vetor_palavras[e], vetor_palavras[f]);
          cont++;
        }
      }
    }
  }
}
printf("|Todas as combinacoes de palavras|\n");
imprimir_vetor(todas_possibilidades_palavras, cont);


  return 0;
}