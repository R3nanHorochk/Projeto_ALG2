#include <stdio.h>
#include <stdlib.h>

int busca_linear_str (char vetor[], int n, char palavra) {
    int i;
    for (i=0; i < n; i++) {
        if (vetor[i] == palavra) {
            return i;
        }
    }
}
void acumular_scores (score_ind) { //Precisa testar essa funcao
    int score_ind; 
    FILE *score;
    static char pontuacao[20];
    score = fopen("scores.txt", "w");
    if (score == NULL) {
        printf("Ocorreu um erro ao carregar o arquivo!");
        return 1;
    } 
    else 
    {
        while (score_ind != '\n') {
            fputc(score_ind,score);
        }
    }

}

char* ler_proxima_palavra (FILE *pont_dados) { 
    static char palavra[100];
    if (fscanf(pont_dados, "%s", palavra) == 1) {
        return palavra;
    } else {
        return NULL;
    }

}//preciso pegar palavras de linhas aleatorias 

//PROGRAMA PRINCIPAL 
int main () { 
    printf("Bem Vindo ao nosso projeto de algoritmos\n");
    printf("descubra a palavra certa em 6 tentativas \n a cada tentativa você será informado o quão perto chegou\n");



    FILE *pont_dados;
    static char palavra_str[20]; // usa-se o static para que o endereco do ponteiro persista 
    pont_dados = fopen("sem_acentos.txt", "r"); //carregando o arquivo.txt em modo de leitura
    if (pont_dados == NULL) {
        printf("Ocorreu um erro ao abrir o arquivo.");
        return 1;
    }
    char *word;
    word = ler_proxima_palavra(pont_dados);
    if (word != NULL) {
        printf("%s\n", word);
    }
    
    word = ler_proxima_palavra(pont_dados);
     if (word != NULL) {
        printf("%s\n", word);
    }
    return 0;
}
