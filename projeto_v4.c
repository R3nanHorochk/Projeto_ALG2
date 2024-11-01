#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*essa versão está pegando um numero aleatorio do arquivo.txt*/

void boas_vindas () {
    printf("Bem Vindo ao nosso projeto de algoritmos-2\n");
    printf("descubra a palavra certa em 6 tentativas \n a cada tentativa você será informado o quão perto chegou\n");
    printf("----");
    printf("\n\n");
}

int contar_linhas (FILE *file) { //funcao para contar as linhas do arquivo txt
    int linhas = 0;               //sera usada para pegar uma linha aleatoria em outra funcao
    char ch;
    while (!feof(file)) {
        ch = fgetc(file);
        if (ch == '\n') {
            linhas++;
        }
    }
    return linhas;
}

void acumular_scores (int score_ind) { //Funcao testatada e funcionando
    FILE *score;
    score = fopen("scores.txt", "a");//arquivo aberto em modo a para acumular dados.
    if (score == NULL) {
        printf("Ocorreu um erro ao carregar o arquivo!");
    } 
    else 
    {
        fprintf(score, "%d ", score_ind);
        fclose(score);
    }

}
void guardar_nomes_scores (char name[]) { //Funcao testatada e funcionando
    FILE *score;
    score = fopen("scores.txt", "a");//arquivo aberto em modo a para acumular dados.
    if (score == NULL) {
        printf("Ocorreu um erro ao carregar o arquivo!");
    } 
    else 
    {
        fprintf(score, " %s\n", name);
        fclose(score);
    }
}

char* ler_palavra_aleatoria (FILE *pont_dados, int n) { //ler uma palavra de uma linha aleatória
    //static char palavra[100];
    int random_linha = rand() % n;
    int linha_atual = 0;
    static char acumular_conteudo_linha[50];

    rewind(pont_dados); //voltar para o inicio do arquivo

    while (fgets(acumular_conteudo_linha, sizeof(acumular_conteudo_linha), pont_dados)) {
        if (linha_atual == random_linha) {
            static char primeira_palavra[50];
            if (sscanf(acumular_conteudo_linha, "%s", primeira_palavra) == 1) { //sscanf pega a palavra do conteudo da linha e guarda em primeira palavra
                return primeira_palavra;
            } else {
                return NULL;
            }
        }
        linha_atual++;
    }
    return NULL; //caso nao encontre a linha
}

//PROGRAMA PRINCIPAL 
int main () { 
    clock_t inicio, fim;
    double tempo_gasto;
    inicio = clock();
    srand(time(NULL)); //inicializando o gerador de numeros aleatorios

    boas_vindas();
   
    FILE *pont_dados; 
    static char palavra_str[20]; // usa-se o static para que o endereco do ponteiro persista 
    //carregando o arquivo sem_acentos.txt
    pont_dados = fopen("sem_acentos.txt", "r"); //carregando o arquivo.txt em modo de leitura
    if (pont_dados == NULL) {
        printf("Ocorreu um erro ao abrir o arquivo. \n");
        return 1;
    }
    //contando linhas do arquivo
    int total_linhas = contar_linhas(pont_dados);
    printf("o total de linhas é: %d\n", total_linhas);
    if (total_linhas == 0) {
        printf("O arquivo está vazio. \n");
        fclose(pont_dados);
        return 1;
    }
    //lendo uma palavra aleatoria
    char* word = ler_palavra_aleatoria(pont_dados, total_linhas);
     if (word != NULL) {
        printf("%s\n", word);
    }

    //scores 
    int pontos = 30;
    char nome[20] = "Ryan";
    acumular_scores(pontos);
    guardar_nomes_scores(nome);

    //fim do programa
    fim = clock();

    //calculando o tempo
    tempo_gasto = (double)(fim - inicio) /  CLOCKS_PER_SEC;
    printf("O tempo gasto foi de %f segundos\n", tempo_gasto);
    return 0;
}
