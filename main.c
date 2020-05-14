#include "grafo.h"
#include <stdio.h>

int main() {
  Grafo *grafo = import_grafo("grafo.txt");
  char inicio = grafo_busca_inicio(grafo);
  char fim = grafo_busca_fim(grafo);
  printf("Lista de adjacencias do grafo:\n");
  imprime_grafo(grafo);
  No_aresta *critico = NULL;
  busca_caminho_critico(grafo, inicio, fim, &critico);
  printf("\nCaminho critico:\n");
  imprime_lista_aresta(critico);
  printf("\nTarefas criticas:\n");
  busca_tarefas_criticas(grafo, inicio, fim, critico);
  libera_lista(critico);
  libera_grafo(grafo);

  return 0;
}
