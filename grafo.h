#include "arestas.h"
#include <stdlib.h>
#include <string.h>

typedef struct no_aresta No_aresta;
typedef struct grafo Grafo;

Grafo *import_grafo(char nome[]);
char grafo_busca_inicio(Grafo * grafo);
char grafo_busca_fim(Grafo * grafo);
void imprime_grafo(Grafo *grafo);
int busca_caminho_critico(Grafo *grafo, char vertice1, char vertice2,
                          No_aresta **critico);
void imprime_lista_aresta(No_aresta *inicio);
void busca_tarefas_criticas(Grafo *grafo, char vertice1, char vertice2,
                            No_aresta *critico);
void libera_lista(No_aresta *lista);
void libera_grafo(Grafo *grafo);
