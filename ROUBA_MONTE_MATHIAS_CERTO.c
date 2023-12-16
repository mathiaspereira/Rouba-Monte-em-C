 #include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Definindo as structs

typedef struct Carta {
    int numero;
    char nipe;
} carta;

typedef struct Pilha {
    struct Carta cartas[54];
    int topo;
} pilha;

typedef struct elemento {
    carta carta;
    struct elemento *anterior;
    struct elemento *prox;
} elemento;

typedef struct pilha_dinamica {
    elemento *topo;
} pilha_dinamica;

typedef struct {
    elemento *inicio;
    int num_de_cartas;
} lista;

typedef struct {
    char nome[20];
    pilha_dinamica monte;
    int numero_de_cartas;
    int pontos;
    int numCartas;
    char cartas[20][5];
} jogador;

// a cima todas as struct's que serão usadas ao decorrer do codigo
// a baixo funções para inicializar baralho e monte

int inicializa_monte(pilha_dinamica *p) {

  p->topo = NULL;

  if (p->topo == NULL)

    return 1;

  else

    return 0;
}

int inicializa_baralho(pilha *p) {

  p->topo = 0;

  if (p->topo == 0) {

    return 1;

  } else

    return 0;
}

int inicializa_lista(lista *l) {

  l->inicio = NULL;

  l->num_de_cartas = 0;

  if (l->inicio == NULL)

    return 1;

  else

    return 0;
}

int inicializa_num_de_cartas(jogador *j) {

  j->numero_de_cartas = 0;

  if (j->numero_de_cartas == 0)

    return 1;

  else

    return 0;
}

// Embaralha as cartas em uma pilha
void embaralharPilha(pilha *baralho) {
  srand(time(NULL)); // Semente de geracao de numeros aleatorios

  // Embaralhar a pilha
  for (int i = baralho->topo - 1; i > 0; i--) {
    // Gera um índice aleatório
    int j = rand() % (i + 1);

    // Troca as cartas nas posições i e j
    carta aux = baralho->cartas[i];
    baralho->cartas[i] = baralho->cartas[j];
    baralho->cartas[j] = aux;
  }
}

// Empilha uma carta no baralho
void empilhar_baralho(pilha *baralho, carta carta) {
  // Adiciona a carta ao topo do baralho
  baralho->cartas[baralho->topo] = carta;

  // Incrementa o índice do topo do baralho
  baralho->topo++;
}

// Desempilha uma carta do topo do baralho
carta desempilhar_baralho(pilha *baralho) {
  // Decrementa o índice do topo do baralho
  baralho->topo--;
  // Retorna a carta no topo do baralho
  return baralho->cartas[baralho->topo];
}

// Insere uma carta no inicio da lista
int insere_lista(lista *l, carta c) {
  // Aloca memória para um novo elemento
  elemento *novo = (elemento *)malloc(sizeof(elemento));

  // Verifica se a alocação foi bem-sucedida
  if (novo != NULL) {
    novo->carta = c; // Atribui a carta ao novo elemento
    // Configura os ponteiros do novo elemento
    novo->anterior = NULL;
    novo->prox = l->inicio;

    if (l->inicio != NULL) {
      l->inicio->anterior = novo; // Atualiza o ponteiro do elemento anterior,
                                  // se a lista não estiver vazia
    }

    l->inicio = novo; // Atualiza o início da lista para o novo elemento

    l->num_de_cartas++; // Incrementa o número de cartas na lista

    return 1; // Inserção bem-sucedida
  }
  return 0; // Falha na alocação de memória
}

void insere_monte_jogador(jogador *j, carta c) {
  // Aloca memória para um novo elemento
  elemento *novo = (elemento *)malloc(sizeof(elemento));

  // Verifica se a alocação foi bem-sucedida
  if (novo != NULL) {
    // Atribui a carta ao novo elemento
    novo->carta = c;

    // Atualiza o ponteiro do novo elemento para o elemento anterior no monte
    novo->anterior = j->monte.topo;

    // Atualiza o topo do monte para o novo elemento
    j->monte.topo = novo;

    // Incrementa o número de cartas no monte do jogador
    j->numero_de_cartas++;
  } else {
    // Lida com erro de alocação de memória
    printf("|->Erro ao alocar memória para a carta no monte do jogador.\n");
  }
}

int verificacao(carta *c1, carta *c2) { // Compara os números das cartas

  if (c1->numero == c2->numero)

    return 1; // Retorna 1 se os números são iguais

  else

    return 0; // Retorna 0 se os números são diferentes
}

carta pesquisa_indice(lista *l, int indicador) {// Função para pesquisar e retornar a carta em um índice específico da lista
  // Inicializa um ponteiro auxiliar apontando para o início da lista
  elemento *aux = l->inicio;

  int i = 0;

  // Percorre a lista até o índice desejado ou até o final da lista
  while (i < indicador && aux != NULL) {
    aux = aux->prox;
    i++;
  }

  // Se o ponteiro auxiliar não for nulo, retorna a carta no índice
  if (aux != NULL) {
    return aux->carta;
  }
  // Se o índice não for válido, a função pode retornar uma carta vazia ou tomar outra ação, conforme necessário
  carta carta_nula;

  carta_nula.nipe = '0';

  carta_nula.numero = 0;

  return carta_nula;
}

void retirar_carta(lista *l, int indicador) {

  if (indicador < 0 || l->num_de_cartas <= 0 || l->inicio == NULL) {

    printf("\n|==============================|\n");
    printf("\n|Indice invalido ou lista vazia|\n");
    printf("\n|==============================|\n");

    return;
  }

  printf("Indice recebido: %d\n", indicador);

  if (indicador == 0) {

    elemento *aux = l->inicio;

    l->inicio = l->inicio->prox;

    free(aux);

    l->num_de_cartas--;

    printf("\n|====================================|\n");
    printf("\n|Elemento removido do inicio da lista|\n");
    printf("\n|====================================|\n");

    if (l->num_de_cartas > 0) {

      l->inicio = l->inicio->prox;
    }

    return;
  }

  elemento *aux_anterior = NULL;

  elemento *aux_atual = l->inicio;

  int i = 0;

  while (i < indicador && aux_atual != NULL) {

    aux_anterior = aux_atual;

    aux_atual = aux_atual->prox;

    i++;
  }

  if (aux_atual == NULL) {

    printf("\n|==================|\n");
    printf("\n|Indice inexistente|\n");
    printf("\n|==================|\n");

    return;
  }

  printf("\n|================================|\n");
  printf("\n|Elemento antes da remocao:|%d_%c|\n", aux_atual->carta.numero,aux_atual->carta.nipe);
  printf("\n|================================|\n");

  if (aux_anterior != NULL) {

    aux_anterior->prox = aux_atual->prox;

  } else {

    l->inicio = aux_atual->prox;
  }

  free(aux_atual);

  l->num_de_cartas--;
  printf("\n|==============================|\n");
  printf("\n|Elemento removido do indice %d|\n", indicador);
  printf("\n|==============================|\n");
}

////////////////////////////////////
// print

void print_lista(lista *cartas) {

  elemento *aux = cartas->inicio;

  int i = 1;

  printf("\n↓↓↓As cartas da mesa sao:↓↓↓\n");

  while (aux != NULL) {

    printf("\n");
    printf("%d |=> '[%d_%c]' ", i, aux->carta.numero, aux->carta.nipe);

    aux = aux->prox;

    i++;
  }

  return;
}

void print_montes(jogador *j) { // Função para imprimir as informações do monte de um jogador

  // Inicializa um ponteiro auxiliar apontando para o topo do monte do jogador
  elemento *aux = j->monte.topo;

  // Verifica se o jogador não possui cartas
  if (j->numero_de_cartas == 0) {
    printf("\n Jogador %s Nao possui cartas\n", j->nome);
    printf("\n|================================|\n");
    return;
  } else {
    // Imprime o nome do jogador, a carta no topo do monte e o número total de cartas
    printf("\n|-> Monte do jogador %s \n -> | [%d_%c] |\n", j->nome, aux->carta.numero, aux->carta.nipe);
    printf("\n|^===^====^=^=^===^=^=^====^====^|\n");
    printf("\n|Numero de cartas do jogador:[%d]|\n", j->numero_de_cartas);
    return;
  }
}

void roubarMonte(jogador *jogadores, int indiceAlvo, int indiceJogadorAtual) {
    // Adicione um alias para a struct jogador
    jogador *alvo = &jogadores[indiceAlvo];

    // Verifique se o monte do jogador alvo não está vazio
    while (alvo->monte.topo != NULL) {
        // Adiciona carta ao monte do jogador atual
        insere_monte_jogador(&jogadores[indiceJogadorAtual], alvo->monte.topo->carta);

        // Remove a carta do monte do jogador alvo
        elemento *elementoRemovido = alvo->monte.topo;
        alvo->monte.topo = alvo->monte.topo->anterior;
        free(elementoRemovido);
    }

    printf("\n|->Monte roubado com sucesso!\n");
}

int empilharProprioMonte(jogador *j, carta c) {
  // Verifica se o monte do jogador não está vazio e se a carta no topo do monte é igual à carta a ser empilhada
  if (j->monte.topo != NULL && j->monte.topo->carta.numero == c.numero) {
    // Adiciona a carta ao monte do jogador
    insere_monte_jogador(j, c);
    return 1; // Retorna 1 indicando que a carta foi empilhada com sucesso
  } else {
    return 0; // Retorna 0 indicando que não foi possível empilhar no próprio monte
  }
}

// Função para comparar dois jogadores para qsort
int compararJogadores(const void *a, const void *b) {
    return ((jogador *)b)->numCartas - ((jogador *)a)->numCartas;
}

// Função para exibir o ranking
void exibirRanking(jogador *jogadores, int numJogadores) {
    printf("\n==== RANKING ====\n");
    for (int i = 0; i < numJogadores; i++) {
        printf("%dº lugar: %s \n", i + 1, jogadores[i].nome);

        if (jogadores[i].numCartas > 0) {
            printf("Cartas: ");
            for (int j = 0; j < jogadores[i].numCartas; j++) {
                printf("[%s] ", jogadores[i].cartas[j]);
            }
            printf("\n");
        }
    }
}

int compararCartas(const void *a, const void *b) {
    // Comparação com base no número da carta
    return ((elemento *)a)->carta.numero - ((elemento *)b)->carta.numero;
}

int compararElementos(const void *a, const void *b) {
    elemento *elementoA = *(elemento **)a;
    elemento *elementoB = *(elemento **)b;
    return (elementoA->carta.numero - elementoB->carta.numero);
}

