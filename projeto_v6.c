#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*essa versão está pegando um numero aleatorio do arquivo.txt*/

/*Essa versão é a que será enviada*/

void boas_vindas() {
printf("Bem Vindo ao nosso projeto de algoritmos-2\n");
printf("descubra a palavra certa em 6 tentativas\n");
printf("a cada tentativa você será informado o quão perto chegou\n");
printf("+-----------------+ \n");
printf("\n\n");
printf("\n\n");
}

int palavra(char palavra[], char Respos[], int n, char equivale[]) {
  int i, j; // variavel i e j para o for e 
  int win = 0;// quantos números ele acertou
  bool existe[n];//verifica se o espaço ja foi preenchido 
  bool presente[n];
  for (int l = 0; l < 5; l++) {
    existe[l] = false;//define como falso para verificar
    presente[l] = false;// mostra que não está presente
  }
  for (i = 0; i < n; i++) {
      if (palavra[i] == Respos[i]  ) {
        equivale[i] = '^';//coloca no caracter equivale o caractere
        presente[i] = true;//coloca que está presente
        existe[i] = true;//diz que ja existe em uma posição
        win++;//adiciona +1 a win que se for igual a 5 ganha o jogo
      } 
    }
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
        if (palavra[j] == Respos[i] && existe[j] == false  ) {
        presente[i] = true;//coloca que está presente
        equivale[i] = '!';//coloca no caracter equivale o caractere
        break;
      }
    }
    if (presente[i] == false) {//se ele n existe em nenhum local
      equivale[i] = 'X';//coloca no caracter equivale o caractere
    }
  }
  if (win == n) {
    return 1;
  }
  return 0;
}

int contar_linhas(FILE *file) { // funcao para contar as linhas do arquivo txt
  int linhas = 0; 
  char ch;
  while (!feof(file)) { //feof retorna um valor diferente de 0 se tentar ler apos o arquivo
    ch = fgetc(file);
    if (ch == '\n') {
      linhas++;
    }
  }
  return linhas;
}

void acumular_scores(int score_ind) { // funcao utilizada para acumular os scores no arquivo scores.txt
  FILE *score; //definindo uma varivel do tipo file para abrir o arquivo scores.txt
  score =
      fopen("scores.txt", "a"); // arquivo aberto em modo "a" para acumular dados.
  if (score == NULL) {
    printf("Ocorreu um erro ao carregar o arquivo!");
  } else {
    fprintf(score, "%d ", score_ind);// imprime as tentativas no arquivo scores.txt. Semelhante ao printf, mas esse imprime n tela e o fprintf no arquivo
    fclose(score); //fechndo o arquivo
  }
}
void guardar_nomes_scores(char name[]) { // Funcao utilizada par guardar nomes no arquivo scores.txt
  FILE *score;
  score =
      fopen("scores.txt", "a"); // arquivo aberto em modo a para acumular dados.
  if (score == NULL) {
    printf("Ocorreu um erro ao carregar o arquivo!");
  } else {
    fprintf(score, "%s ", name);// imprime o nome no arquivo scores.txt.
    fclose(score);
  }
}

bool verificar_palavra(FILE *sem_acentos, char palavra[]) { // verifica se a palavra digitada esta no arquivo sem acentos.txt
  char acumular_conteudo_linha[50];

  rewind(sem_acentos); // voltar para o inicio do arquivo

  while (fgets(acumular_conteudo_linha, sizeof(acumular_conteudo_linha),sem_acentos)) { // percorrendo as linhas do arquivo 
  //sizeof retorn o tamanhbo do array
    acumular_conteudo_linha[strcspn(acumular_conteudo_linha, "\n")] = 0; // tirar o \n da linha para a funcao strcmp() poder comparar de forma correta.
    if (strcmp(acumular_conteudo_linha, palavra) == 0) { // comparando a palavra da linha do arquivo com a palavra fornecida
      return true; // Palavra encontrada
    }
  } 
  return false; // caso nao encontre a palavra no arquivo
}

void guardar_word(char word[]) { // Funcao testatada e funcionando
  FILE *score;
  score =
      fopen("scores.txt", "a"); // arquivo aberto em modo a para acumular dados.
  if (score == NULL) {
    printf("Ocorreu um erro ao carregar o arquivo!");
  } else {
    fprintf(score, " %s ", word);// imprime a palavra no arquivo scores.txt.
    fclose(score);
  }
}

void guardar_tempo(double time) { // guardar o tempo de processamento no arquivo scores.txt
  FILE *score;
  score =
      fopen("scores.txt", "a"); // arquivo aberto em modo a para acumular dados.
  if (score == NULL) {
    printf("Ocorreu um erro ao carregar o arquivo!");
  } else {
    fprintf(score, " %f \n", time);// imprime o tempo no arquivo scores.txt.
    fclose(score);
  }
}

char *ler_palavra_aleatoria(FILE *pont_dados, int n) { // ler uma palavra de uma linha aleatória

  int random_linha = rand() % n;
  int linha_atual = 0;
  static char acumular_conteudo_linha[50]; //é como se fosse uma variavel

  rewind(pont_dados); // voltar para o inicio do arquivo

  while (fgets(acumular_conteudo_linha, sizeof(acumular_conteudo_linha),
               pont_dados)) {
    if (linha_atual == random_linha) {
      static char primeira_palavra[50];
      if (sscanf(acumular_conteudo_linha, "%s", primeira_palavra) ==
          1) { // sscanf pega a palavra do conteudo da linha e guarda em primeira palavra
        return primeira_palavra;
      } else {
        return NULL;
      }
    }
    linha_atual++;
  }
  return NULL; // caso nao encontre a linha
}

// PROGRAMA PRINCIPAL
int main() {
  clock_t inicio, fim;
  double tempo_gasto;
  inicio = clock();
  srand(time(NULL)); // inicializando o gerador de numeros aleatorios

  boas_vindas();

  FILE *pont_dados;
  static char palavra_str[20]; // usa-se o static para que o endereco do
                               // ponteiro persista
  // carregando o arquivo sem_acentos.txt
  pont_dados = fopen("sem_acentos.txt",
                     "r"); // carregando o arquivo.txt em modo de leitura
  if (pont_dados == NULL) {
    printf("Ocorreu um erro ao abrir o arquivo. \n");
    return 1;
  }
  // contando linhas do arquivo
  int total_linhas = contar_linhas(pont_dados);
  printf("o total de linhas é: %d\n\n\n", total_linhas);
  if (total_linhas == 0) {
    printf("O arquivo está vazio. \n");
    fclose(pont_dados);
    return 1;
  }
  // lendo uma palavra aleatoria
  char *word;
  do {
    word = ler_palavra_aleatoria(pont_dados, total_linhas);
    if (word != NULL) {
    }
  } while (strlen(word) != 5);
  char nome[20];
  printf("+-----------------+ \n");
  printf("Digite O seu nome: \n ");
  scanf("%s", nome);//grava o nome da pessoa

  printf("+-----------------+ \n");

  int n = 5, tentativa = 0;//grava a variavel com tamanho da palavra e as tentativas
  bool ver;//booleano para verificar
  int ganhou;// verifica se ganhou
  char word2[n];//para trasnformar a palavra em maiusculo
  char equivale[n]; // equivale é o simbolo que referencia o acero ou erro
                    // (^,!,X)
  for (int i = 0; i < n; i++) {
    word2[i] = toupper(word[i]);//trasnforma a palavra em maiusculo
  }

  char Respos[6];//resposta do usuario
  char Respos2[6];//para guardar em maiusculo

  do {
    if (tentativa == 6) {//se tentivas for igual a 6 o suario perde
      printf("Você perdeu\n");//
      printf("A palavra era \n:");
      printf("+----------------+ \n");//modelo
      printf("| ");//modelo
      for (int i = 0; i < n; i++) {
      printf(" %c ", word2[i]);
      }
      printf(" | \n");//modelo
      printf("+----------------+ \n");//modelo
      fim = clock();
      fclose(pont_dados);
      // calculando o tempo
      tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC * 1000;
      printf("O tempo gasto foi de %f milisegundos\n", tempo_gasto);
      break;
    }
    printf("\n");
    do {
      printf("+-----------------+ \n");
      printf("Digite a palavra: \n ");
      scanf("%s", Respos);//pede a resposta pro usuario
      printf("+-----------------+ \n");
      for (int i = 0; i < n; i++) {
        Respos[i] = tolower(Respos[i]);
      }
      bool ver2 = verificar_palavra(pont_dados, Respos);//verifica se a palavra existe no arquivo
      if (ver2 == true) {
        ver = true;// a palavra existe no arquivo
      } else {
        printf("A palavra não foi encontrada.\n");
        printf("Digite outra palavra presente no dicionario.\n");
        ver = false;// a palavra não existe no arquivo
      }

    } while (ver == false);//enquanto a palavra n for presente(ver = false) ele ira rodar a resposta de novo

    printf("\n");
    for (int i = 0; i < n; i++) {
      Respos2[i] = toupper(Respos[i]);//trasnforma a palavra em maiusculo
    }
    ganhou = palavra(word2, Respos2, n, equivale); // verificando se ganhou
    tentativa++;                                   // somando um na tentativa
    printf("+-----------------+ \n");//modelo
    printf("| ");//modelo
    for (int i = 0; i < n; i++) {
      printf(" %c ", Respos2[i]);
    }
    printf(" | \n");//modelo
    printf("| ");//modelo
    for (int i = 0; i < n; i++) {
      printf(" %c ", equivale[i]);//imprime o caractere que equivale a resposta
    }
    printf(" | \n");//modelo
    printf("+-----------------+ \n");//modelo
    if (ganhou == 1) {
      printf("+--------------------------------+ \n");//modelo
      printf("| ");//modelo
      printf("Ganhou o jogo em %d tentativas ", tentativa);
      printf(" | \n");//modelo
      printf("+--------------------------------+ \n");//modelo
      fim = clock();
      // calculando o tempo
      tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC * 1000; //variaveis doubles sao vriaveis float com precisao dupla, é usada para se ter uma boa proximacao do numero 
      printf("O tempo de processamento gasto foi de %f milisegundos\n", tempo_gasto);
      fclose(pont_dados);//fecha o arquivo dos dados
      guardar_nomes_scores(nome);//guarda o nome
      guardar_word(word);//guarda a palavra
      acumular_scores(tentativa);//guarda a tentativa
      guardar_tempo(tempo_gasto);//guarda o tempo gasto
      break;
    }

  } while (ganhou != 1); // continua rodando enquanto o usuario não ganhar e
                         // suas tentativas for <= 6.
  return 0;
}