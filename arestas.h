#include <stdio.h>
#include <stdlib.h>

typedef struct aresta Aresta;

Aresta *cria_aresta(char origem, char destino, int peso);
void libera_aresta(Aresta *aresta);
char aresta_busca_origem(Aresta *aresta);
char aresta_busca_destino(Aresta *aresta);
int aresta_busca_peso(Aresta *aresta);
