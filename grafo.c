#include "grafo.h"
#include <stdio.h>

struct no_aresta {
  Aresta *info;
  struct no_aresta *prox;
  int conferido;
};

struct grafo {
  No_aresta *primeiro_no;
};

static Grafo *cria_grafo() {
  Grafo *novo = (Grafo *)malloc(sizeof(Grafo));
  novo->primeiro_no = NULL;
  return novo;
}

static void limpa_lista(No_aresta **lista) {
  libera_lista(*lista);
  *lista = NULL;
}

static void insere_aresta(No_aresta **inicio, Aresta *aresta, int flag) {
  No_aresta *nova = (No_aresta *)malloc(sizeof(No_aresta));
  nova->info = aresta;
  nova->prox = *inicio;
  nova->conferido = flag;
  *inicio = nova;
}

static void insere_aresta_fim(No_aresta **inicio, Aresta *aresta, int flag) {
  No_aresta *nova = (No_aresta *)malloc(sizeof(No_aresta));
  nova->info = aresta;
  nova->prox = NULL;
  nova->conferido = flag;
  for (No_aresta *i = *inicio; i != NULL; i = i->prox) {
    if (i->prox == NULL) {
      i->prox = nova;
      return;
    }
  }
  *inicio = nova;
}

static void remove_aresta(No_aresta *inicio, Aresta *remover) {
  No_aresta *anterior = NULL;
  int cont = 0;
  for (No_aresta *i = inicio; i != NULL; i = i->prox) {
    if (i->info == remover) {
      printf("conferiu %d\n", aresta_busca_peso(i->info));
      if (anterior == NULL) {
        inicio = i->prox;
        free(i);
        printf("primeiro\n");
        return;
      }
      anterior->prox = i->prox;
      free(i);
      printf("nao primeiro\n");
      return;
    }
    anterior = i;
  }
  printf("nao achou\n");
}

static void copia_lista(No_aresta **destino, No_aresta *origem) {
  No_aresta *inversa = NULL;
  No_aresta *p = origem;
  while (p != NULL) {
    insere_aresta(&inversa, p->info, p->conferido);
    p = p->prox;
  }
  p = inversa;
  while (p != NULL) {
    insere_aresta(destino, p->info, p->conferido);
    p = p->prox;
  }
  libera_lista(inversa);
}

static void grafo_insere_aresta(Grafo *grafo, Aresta *i) {
  No_aresta *novo = (No_aresta *)malloc(sizeof(No_aresta));
  novo->info = i;
  novo->prox = grafo->primeiro_no;
  novo->conferido = 0;
  grafo->primeiro_no = novo;
}

static No_aresta *busca_arestas_saida(Grafo *grafo, char origem) {
  No_aresta *aresta = grafo->primeiro_no;
  No_aresta *retornar = NULL;
  for (No_aresta *i = aresta; i != NULL; i = i->prox) {

    if (aresta_busca_origem(i->info) == origem) {
      insere_aresta(&retornar, i->info, i->conferido);
    }
  }
  return retornar;
}

static int tempo_caminho(No_aresta *caminho) {
  int tempo = 0;
  while (caminho != NULL) {
    tempo += aresta_busca_peso(caminho->info);
    caminho = caminho->prox;
  }
  return tempo;
}

static int maior_que(No_aresta *caminho1, No_aresta *caminho2) {
  int tempo1 = tempo_caminho(caminho1);
  int tempo2 = tempo_caminho(caminho2);
  return tempo1 > tempo2;
}

static No_aresta *desvio_critico(Grafo *grafo, No_aresta *principal) {
  char origem = aresta_busca_origem(principal->info);
  char destino = aresta_busca_destino(principal->info);
  No_aresta *aresta = grafo->primeiro_no;
  No_aresta *retornar = NULL;
  for (No_aresta *i = aresta; i != NULL; i = i->prox) {
    if (aresta_busca_origem(i->info) == origem &&
        aresta_busca_destino(i->info) != destino) {
      insere_aresta(&retornar, i->info, i->conferido);
    }
  }
  return retornar;
}

Grafo *import_grafo(char nome[]) {
  Grafo *grafo = cria_grafo();
  FILE *arquivo = fopen(nome, "r");
  if (arquivo == NULL) {
    printf("Error ao carregar arquivo");
    exit(1);
  }
  char linha[20];
  while (fgets(linha, 20, arquivo)) {
    char origem = linha[0];
    char destino = linha[2];
    int peso = atoi(&linha[4]);
    Aresta *aresta = cria_aresta(origem, destino, peso);
    grafo_insere_aresta(grafo, aresta);
    if (feof(arquivo))
      break;
  }
  fclose(arquivo);
  return grafo;
}

char grafo_busca_inicio(Grafo *grafo) {
  char inicio;
  for (No_aresta *i = grafo->primeiro_no; i != NULL; i = i->prox) {
    inicio = aresta_busca_origem(i->info);
    for (No_aresta *j = grafo->primeiro_no; j != NULL; j = j->prox) {
      char destino = aresta_busca_destino(j->info);
      if (destino == inicio) {
        inicio = '\0';
        break;
      }
    }
    if (inicio == aresta_busca_origem(i->info))
      break;
  }
  return inicio;
}

char grafo_busca_fim(Grafo *grafo) {
  char fim;
  for (No_aresta *i = grafo->primeiro_no; i != NULL; i = i->prox) {
    fim = aresta_busca_destino(i->info);
    for (No_aresta *j = grafo->primeiro_no; j != NULL; j = j->prox) {
      char origem = aresta_busca_origem(j->info);
      if (origem == fim) {
        fim = '\0';
        break;
      }
    }
    if (fim == aresta_busca_destino(i->info))
      break;
  }
  return fim;
}

void imprime_grafo(Grafo *grafo) {
  for (No_aresta *i = grafo->primeiro_no; i != NULL; i = i->prox) {
    printf("|------------------------|\n");
    printf("|      origem = %c        |\n", aresta_busca_origem(i->info));
    printf("|      destino = %c       |\n", aresta_busca_destino(i->info));
    printf("|      peso = %02d         |\n", aresta_busca_peso(i->info));
    printf("|------------------------|\n");
  }
}

void libera_grafo(Grafo *grafo) {
  No_aresta *p = grafo->primeiro_no;
  while (p != NULL) {
    libera_aresta(p->info);
    No_aresta *t = p->prox;
    free(p);
    p = t;
  }
  free(grafo);
}

void libera_lista(No_aresta *lista) {
  No_aresta *p = lista;
  while (p != NULL) {
    No_aresta *t = p->prox;
    free(p);
    p = t;
  };
}

void imprime_lista_aresta(No_aresta *inicio) {
  for (No_aresta *i = inicio; i != NULL; i = i->prox) {
    printf("|------------------------|\n");
    printf("|      origem = %c        |\n", aresta_busca_origem(i->info));
    printf("|      destino = %c       |\n", aresta_busca_destino(i->info));
    printf("|      peso = %02d         |\n", aresta_busca_peso(i->info));
    printf("|------------------------|\n");
  }
}

int busca_caminho_critico(Grafo *grafo, char vertice1, char vertice2,
                          No_aresta **critico) {
  // fim da recursao encontrou destino retorna flag positiva
  if (vertice1 == vertice2)
    return 1;

  // lista de arestas adjacentes
  No_aresta *saida = busca_arestas_saida(grafo, vertice1);
  // se saida estiver vazia e vertice diferente de destino retorna flag negativa
  if (saida == NULL) {
    return 0;
  }
  int achou = 0;
  // variavel para armazenar caminho critico para retornar

  // confere cada aresta de saida do no para encontrar o caminho critico
  for (No_aresta *i = saida; i != NULL; i = i->prox) {
    // entra na recursao buscando o caminho critico do fim para o inicio
    char destino = aresta_busca_destino(i->info);

    No_aresta *caminho = NULL;
    int achou_este = busca_caminho_critico(grafo, destino, vertice2, &caminho);

    // adiciona aresta atual ao caminho encontrado na recursao
    insere_aresta(&caminho, i->info, i->conferido);

    // confere se caminho e maior que critico anterior e salva nos valores
    // finais
    if (achou_este && maior_que(caminho, *critico)) {
      achou = achou_este;
      limpa_lista(critico);
      copia_lista(critico, caminho);
    }
    libera_lista(caminho);
  }
  libera_lista(saida);
  return achou;
}

char busca_limite(Grafo *grafo, No_aresta *critico, char origem) {
  No_aresta *caminho = NULL;
  for (No_aresta *i = critico; i != NULL; i = i->prox) {
    char destino = aresta_busca_destino(i->info);
    int achou = busca_caminho_critico(grafo, origem, destino, &caminho);
    if (achou) {
      libera_lista(caminho);
      return destino;
    }
    limpa_lista(&caminho);
  }
  return '\0';
}

//----------------------------------------------------------------------------//
//---------------------------- solucao final ---------------------------------//
//----------------------------------------------------------------------------//
void busca_tarefas_criticas(Grafo *grafo, char vertice1, char vertice2,
                            No_aresta *critico) {
  // fim da recursao
  if (vertice1 == vertice2)
    return;

  // valores para busca de tarefas criticas
  char nova_origem = aresta_busca_destino(critico->info);
  busca_tarefas_criticas(grafo, nova_origem, vertice2, critico->prox);
  int tempo_critico = tempo_caminho(critico);
  No_aresta *desvio = desvio_critico(grafo, critico);

  // laco para conferir caminhos alternativos a partir de arestas de desvio
  for (No_aresta *i = desvio; i != NULL; i = i->prox) {

    // valores para encontrar caminho e conferir se existe
    char origem = aresta_busca_destino(i->info);
    No_aresta *outro_caminho = NULL;
    int achou = busca_caminho_critico(grafo, origem, vertice2, &outro_caminho);

    // confere se existe caminho a partir dessa aresta
    if (!achou) {
      continue;
    }

    // valores para conferir se tarefa e critica
    insere_aresta(&outro_caminho, i->info,
                  i->conferido);              // completa caminho atual
    int tempo = tempo_caminho(outro_caminho); // calcula tempo do caminho atual
    int diferenca = tempo_critico - tempo;    // diferença entre os tempos
    char limite = busca_limite(grafo, critico, origem);
    // laco para comparar o caminho atual com
    // as arestas do caminho critico
    for (No_aresta *j = critico; j != NULL; j = j->prox) {
      if (aresta_busca_origem(j->info) == limite) {
        break;
      }
      // compara se o peso da aresta e maior que a diferenca
      int tempo_tarefa = aresta_busca_peso(j->info);
      if (tempo_tarefa > diferenca && !(j->conferido)) {
        No_aresta *caminho_inicio = NULL;
        char meio = aresta_busca_origem(i->info);
        char inicio = grafo_busca_inicio(grafo);
        int desvio_no_meio =
            busca_caminho_critico(grafo, inicio, meio, &caminho_inicio);
        char origem = aresta_busca_origem(j->info);
        char destino = aresta_busca_destino(j->info);
        printf("A tarefa %c->%c se reduzida mais de %d horas\n", origem,
               destino, diferenca);
        printf("altera o caminho critico.\n");
        printf("O caminho critico novo sera:\n");
        if (desvio_no_meio) {
          imprime_lista_aresta(caminho_inicio);
        }
        imprime_lista_aresta(outro_caminho);
        j->conferido = 1;
      }
    }
    libera_lista(outro_caminho);
  }
  libera_lista(desvio);
}
