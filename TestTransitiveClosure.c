//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira, Joao Manuel Rodrigues - Dec 2024
//
// Testing the Transitive Closure algorithm
//

#include <assert.h>

#include "Graph.h"
#include "GraphTransitiveClosure.h"
#include "instrumentation.h"


int main(void) {
  // Inicializa a instrumentação
  InstrName[0] = "memory_accesses";
  InstrName[1] = "edge_additions";
  InstrCalibrate();
  
  // What kind of graph is dig01?
  Graph* dig01 = GraphCreate(6, 1, 0);
  GraphAddEdge(dig01, 1, 2);
  GraphAddEdge(dig01, 1, 4);
  GraphAddEdge(dig01, 3, 4);
  printf("The graph:\n");
  // Displaying in DOT format
  GraphDisplayDOT(dig01);
  printf("\n");

  GraphCheckInvariants(dig01);

  printf("Computing Transitive Closure...\n");
  InstrReset(); // Reseta os contadores antes de iniciar a medição
  Graph* tcdig01 = GraphComputeTransitiveClosure(dig01);
  InstrPrint(); // Imprime os contadores após a execução
  printf("The transitive closure:\n");
  // Displaying in DOT format
  GraphDisplayDOT(tcdig01);
  printf("\n");

  GraphCheckInvariants(tcdig01);

  // Reading a directed graph from file
  FILE* file = fopen("DG_2.txt", "r");
  Graph* dig03 = GraphFromFile(file);
  fclose(file);
  // Displaying in DOT format
  GraphDisplayDOT(dig03);
  printf("\n");

  GraphCheckInvariants(dig03);

  printf("Computing Transitive Closure for graph from file...\n");
  InstrReset();
  Graph* tcdig03 = GraphComputeTransitiveClosure(dig03);
  InstrPrint();
  printf("The transitive closure:\n");
  // Displaying in DOT format
  GraphDisplayDOT(tcdig03);
  printf("\n");

  GraphCheckInvariants(tcdig03);

  const char* filenames[] = {
        "GRAFOS_ORIENTADOS/j1.txt",
        "GRAFOS_ORIENTADOS/j2.txt",
        "GRAFOS_ORIENTADOS/j3.txt",
        "GRAFOS_ORIENTADOS/j4.txt",
        "GRAFOS_ORIENTADOS/j5.txt",
        "GRAFOS_ORIENTADOS/j6.txt",
        "GRAFOS_ORIENTADOS/j7.txt",
        "GRAFOS_ORIENTADOS/j8.txt",
        "GRAFOS_ORIENTADOS/j9.txt",
        "GRAFOS_ORIENTADOS/j10.txt"
    };

  const unsigned int numFiles = 10;

  for (unsigned int f = 0; f < numFiles; f++) {
      printf("Processing file: %s\n", filenames[f]);

      FILE* file = fopen(filenames[f], "r");
      if (file == NULL) {
          perror("Error opening file");
          continue; // Pula para o próximo arquivo em caso de erro
      }

      Graph* digraph = GraphFromFile(file);
      fclose(file);

      // Exibe o grafo no formato DOT
      printf("Graph in DOT format:\n");
      GraphDisplayDOT(digraph);
      printf("\n");

      // Verifica invariantes do grafo
      GraphCheckInvariants(digraph);

      printf("Computing Transitive Closure for graph from file...\n");
      InstrReset();
      Graph* tcdig = GraphComputeTransitiveClosure(digraph);
      InstrPrint();
      printf("The transitive closure:\n");
      // Displaying in DOT format
      //GraphDisplayDOT(tcdig);
      printf("\n");
      GraphCheckInvariants(tcdig);

      // Destroi os grafos
      GraphDestroy(&digraph);
      GraphDestroy(&tcdig);
  }

  GraphDestroy(&dig01);
  GraphDestroy(&dig03);

  GraphDestroy(&tcdig01);
  GraphDestroy(&tcdig03);

  return 0;
}
