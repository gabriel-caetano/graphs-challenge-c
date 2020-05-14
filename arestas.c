#include "arestas.h"

struct aresta {
  char origem;
  char destino;
  int peso;
};

Aresta *cria_aresta(char origem, char destino, int peso) {
  Aresta *novo = (Aresta *)malloc(sizeof(Aresta));
  novo->origem = origem;
  novo->destino = destino;
  novo->peso = peso;
  return novo;
}

void libera_aresta(Aresta *aresta) { free(aresta); }

char aresta_busca_origem(Aresta *aresta) { return aresta->origem; }

char aresta_busca_destino(Aresta *aresta) { return aresta->destino; }

int aresta_busca_peso(Aresta *aresta) { return aresta->peso; }
