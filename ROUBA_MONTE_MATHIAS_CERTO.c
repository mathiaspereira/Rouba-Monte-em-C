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

int main() {
  // Todas minhas variaveis
  int num_jogadores = 0;

  int num_baralhos = 0;

  int retorno_insere_lista;

  carta carta_pesquisa;

  int carta_jogada;

  int retorno_verificacao;

  int aux_carta;

  carta retorno_desempilhamento;

  carta_pesquisa.nipe = '0';

  carta_pesquisa.numero = 0;

  char nomeJogadorAlvo[20];

  ////////////////////////////////////MENU INTERAÇÃO
  printf("|♤=====================♤|\n");
  printf("|=♡=====Bem=Vindo=====♡=|\n");
  printf("|=♡========AO=========♡=|\n");
  printf("|=♡===ROUBA=MONTES====♡=|\n");
  printf("|♤=====================♤|\n");

  printf("\n|> Cartas de [1 a 13]\n");
  printf("\n|> Naipes:'P', 'C', 'E', 'O'\n");

  printf("\n|->Digite o numero de jogadores: ");// Solicita ao usuário as informacoes
  scanf("%d", &num_jogadores);
  printf("\n|->Digite a quantidade de baralhos: ");
  scanf("%d", &num_baralhos);

    pilha baralho_principal;// Inicializa a pilha principal do baralho

    jogador *jogadores = (jogador *)malloc(num_jogadores * sizeof(jogador));// Aloca dinamicamente a memória para o array de jogadores

    lista *cartas_mesa = (lista *)malloc(sizeof(lista));// Aloca dinamicamente a memoria para a lista de cartas da mesa

  // nome dos jogadores
  for (int i = 0; i < num_jogadores; i++) {

    printf("\n|->Digite o nome do Jogador %d: ", i + 1);
    scanf("%19s", jogadores[i].nome);

    jogadores[i].numero_de_cartas = 0;// Inicializa o numero de cartas do jogador como 0
  }

  // Inicializa o monte de cada jogador e o número de cartas
    for (int i = 0; i < num_jogadores; i++) {

    int retorno_cria_monte = inicializa_monte(&jogadores[i].monte);// Inicializa o monte do jogador usando a função inicializa_monte

    int retorno_num_de_cartas = inicializa_num_de_cartas(&jogadores[i]);// Inicializa o número de cartas do jogador usando a função inicializa_num_de_cartas
}

  char np[4] = {'P', 'C', 'E', 'O'};// Definindo os naipes possíveis: 'P' (Paus), 'C' (Copas), 'E' (Espadas), 'O' (Ouros)

  int retorno_inicializa_baralho = inicializa_baralho(&baralho_principal);// Inicializando o baralho principal usando a função inicializa_baralho

  if (retorno_inicializa_baralho == 0) {

    printf("\n|->Erro na inicializacao de baralho!"); // Fazendo o teste de inicializazcao

    return 0;

  } else {// Se o número de baralhos não for 0, inicializa o baralho principal com cartas

    for (int i = 0; i < num_baralhos; i++) {// Loop para cada baralho
      for (int numero = 1; numero <= 13; numero++) {   // Loop para cada número de carta de 1 a 13

        for (int j = 0; j < 4; j++) {// Loop para cada naipe 'P', 'C', 'E', 'O'

          carta c;

          c.numero = numero;

          c.nipe = np[j];// Configuracao da carta com numero e naipe

          empilhar_baralho(&baralho_principal, c); // Empilha a carta no baralho principal
        }
      }
      for (int k = 0; k < 2; k++) {// Adiciona duas cartas curingas (número 0 e naipe 'J') ao final de cada baralho

        carta c;

        c.numero = 0;

        c.nipe = 'J';

        empilhar_baralho(&baralho_principal, c);
      }
    }
  }

  embaralharPilha(&baralho_principal);// Embaralha o baralho principal antes do início do jogo

  printf("\n\n|->Tudo pronto, vamos comecar o jogo!\n\n");

  int retorno_inicializa_cartas_comunitarias = inicializa_lista(cartas_mesa); // Inicializa a lista de cartas da mesa

  if (retorno_inicializa_cartas_comunitarias == 0) {// Se houver um erro na inicializacao da lista, exibe uma mensagem de erro

    printf("\n|->Erro na inicializacao da lista!");

  } else {

    carta carta_desempilhada = desempilhar_baralho(&baralho_principal);// Desempilha a primeira carta do baralho principal e a coloca na mesa

    insere_lista(cartas_mesa, carta_desempilhada);

    print_lista(cartas_mesa); // Exibe a lista de cartas da mesa

    carta carta_mao;

    while (baralho_principal.topo > 0) {// Loop principal, enquanto houver cartas no baralho principal segue o jogo
        //printf("\n\n|->Cartas restantes no baralho: %d\n", baralho_principal.topo);

      if (baralho_principal.topo == 1 || baralho_principal.topo == 0) {// Se restar apenas uma carta no baralho, exibe uma mensagem de atenção

        printf("\n|->ATENCAO!!!!\n");
        printf("\n|->Ultima rodada!\n");

      } else {

        for (int i = 0; i < num_jogadores; i++) {// Loop para cada jogador

          printf("\n\n|->Cartas restantes no baralho: %d\n",baralho_principal.topo);// Exibe o número de cartas restantes no baralho
          printf("\n|->Jogada jogador %s Aperte qualquer tecla para iniciar",jogadores[i].nome);

          int c;

          while ((c = getchar()) != '\n' && c != EOF); // Limpa o buffer de entrada
          getchar(); // Aguarda uma nova entrada do usuario

          // Exibe a carta no topo do monte do jogador que está na jogada
          printf("\n|->Monte do jogador %s: ", jogadores[i].nome);
          if (jogadores[i].monte.topo != NULL) {
          printf("%d_%c", jogadores[i].monte.topo->carta.numero, jogadores[i].monte.topo->carta.nipe);
            } else {
          printf("Monte vazio");
         }
            printf("\n");

          carta_mao = desempilhar_baralho(&baralho_principal);// Desempilha a carta do baralho principal para a mao do jogador

          printf("\n>>Sua carta e:<<\n");

          printf("|-> %d_%c \n", carta_mao.numero, carta_mao.nipe);

          if (cartas_mesa->num_de_cartas == 0) {// Se a mesa estiver vazia, desempilha uma carta do baralho principal para a mesa

            carta carta_desempilhada = desempilhar_baralho(&baralho_principal);

            insere_lista(cartas_mesa, carta_desempilhada);
          }

          printf("\n");

          print_lista(cartas_mesa);// Exibe a lista de cartas da mesa

          printf("\n\n");

          for (int k = 0; k < num_jogadores; k++) {

            if (k != i)

              print_montes(&jogadores[k]); // Exibe os montes dos outros jogadores
          }

          int op;

          printf("\n|->Qual jogada sera feita?\n1-Descarte\n2-Usar carta da "
                 "mesa de descarte\n3-Roubar Monte\n4-Empilhar no propio monte\n");

          scanf("%d", &op);

          switch (op) {

          case 1:

            retorno_insere_lista = insere_lista(cartas_mesa, carta_mao);

            if (retorno_insere_lista == 1)

              printf("\n|->Jogada realizada com sucesso!\n");

            else

              printf("|->ERRO!\n");

            break;

          case 2:
            printf("\n|->Qual o indice da carta que sera usada?\n");
            scanf("%d", &carta_jogada);

            // Ajusta o índice do usuário para o índice interno (subtraindo 1)
            int indice_interno = carta_jogada - 1;

            // Verifica se o índice fornecido é válido
            if (indice_interno < 0 ||
                indice_interno >= cartas_mesa->num_de_cartas) {
              printf("\n|->Indice esta invalido!\n");
              break;
            }

            aux_carta = indice_interno;

            carta_pesquisa = pesquisa_indice(cartas_mesa, indice_interno);

            // Adiciona mensagens
            printf("|-> Carta da mesa escolhida: || %d %c ||\n",
                   carta_pesquisa.numero, carta_pesquisa.nipe);

            retorno_verificacao = verificacao(&carta_mao, &carta_pesquisa);

            if (retorno_verificacao == 1) {
              printf("\n|->Jogada valida!\n");

              // Remover a carta da mesa (descarte)
              retirar_carta(cartas_mesa, indice_interno);

              // Adicionar carta à mão do jogador
              insere_monte_jogador(&jogadores[i], carta_mao);

              // Adicionar carta da mesa à mão do jogador
              insere_monte_jogador(&jogadores[i], carta_pesquisa);

              printf("\n|->Voce tem direito a uma nova jogada!\n");
              i--;
            } else {
              printf("\n|->Jogada invalida!\n");
            }

            break;

         case 3:
            printf("Nome do jogador atual: %s\n", jogadores[i].nome);
            printf("Deseja roubar o monte de qual jogador?\n");
            char qualJog[20];
            scanf("%s", qualJog);

            int jogadorEncontrado = 0;
            int indiceJogadorAlvo = -1;

            for (int q = 0; q < num_jogadores; q++) {
                if (strcmp(qualJog, jogadores[q].nome) == 0 && q != i) {
                    jogadorEncontrado = 1;
                    indiceJogadorAlvo = q;
            break;
                }
            }

                if (jogadorEncontrado) {
                    roubarMonte(jogadores, indiceJogadorAlvo, i);
                } else {
                    printf("\n|->Jogador não encontrado ou jogada inválida.\n");
            }
            break;

         case 4:
            if (empilharProprioMonte(&jogadores[i], carta_mao)) {
            printf("Carta empilhada com sucesso.\n\n");
            printf("Jogue Novamente!\n");
                } else {
            printf("Não foi possível empilhar no próprio monte.\n");
            }
            break;
          }
        }
      }

    }
        int vencedor = 0;

        for (int i = 1; i < num_jogadores; i++) {
        if (jogadores[i].numero_de_cartas > jogadores[vencedor].numero_de_cartas) {
        vencedor = i; // Atualiza o índice do vencedor se encontrarmos um jogador com mais cartas
                }
        }
        // Ordena os jogadores com base no número de cartas
        qsort(jogadores, num_jogadores, sizeof(jogador), compararJogadores);

        // Exibe o ranking ultima rodada
        exibirRanking(jogadores, num_jogadores);

        printf("\n|===== FIM DE JOGO =====|\n");
        printf("|-> O jogador vencedor é: %s\n", jogadores[vencedor].nome);
        // Exibe o total de cartas do jogador vencedor
        printf("|-> Com um total de %d cartas!\n", jogadores[vencedor].numero_de_cartas);

        // Exibe mensagens de debug
        printf("|-> Montando monte do vencedor...\n");

        elemento *atual = jogadores[vencedor].monte.topo;
        int numCartas = jogadores[vencedor].numero_de_cartas;

        printf("|-> Número de cartas no monte do vencedor: %d\n", numCartas);

        elemento **cartasArray = (elemento **)malloc(numCartas * sizeof(elemento *));
        int i = 0;

        // Preenche o array temporário
        while (atual != NULL && i < numCartas) {
        cartasArray[i] = atual;
        atual = atual->anterior;
        i++;
        }

        // Ordena o array temporário em ordem crescente com base no número da carta
        qsort(cartasArray, numCartas, sizeof(elemento *), compararElementos);

        // Imprime o array temporário em ordem crescente
        printf("|-> Cartas no monte do vencedor (em ordem crescente):\n");
        for (int j = 0; j < numCartas; j++) {
        printf("|-> [%d_%c] ",cartasArray[j]->carta.numero, cartasArray[j]->carta.nipe);
        }

        printf("\n");

        // Libera a memória alocada para o array temporário
        free(cartasArray);
  }

    printf("\n|-> Fim do programa. Pressione ENTER para sair...\n");
    getchar(); // Aguarda o usuário pressionar ENTER
return 0;
}
