//arquivo feito pra testar a funcao scores individualmente

#include <stdio.h>

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
void guardar_nomes (char name[]) { //Funcao testatada e funcionando
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

int main () {
    int pontos = 30;
    char nome[100] = {"Ryan"};
    acumular_scores(pontos);
    guardar_nomes(nome);
    return 0;
}

//versao final