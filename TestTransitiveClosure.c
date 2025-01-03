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
  InstrName[3] = "V";
  InstrName[4] = "E";

  InstrCalibrate();
  
  // What kind of graph is dig01?
  Graph* dig01 = GraphCreate(6, 1, 0);
  GraphAddEdge(dig01, 1, 2);
  GraphAddEdge(dig01, 1, 4);
  GraphAddEdge(dig01, 3, 4);
  printf("The graph:\n");
  // Displaying in DOT format
  //GraphDisplayDOT(dig01);
  printf("\n");

  GraphCheckInvariants(dig01);

  printf("Computing Transitive Closure...\n");
  InstrReset(); // Reseta os contadores antes de iniciar a medição
  Graph* tcdig01 = GraphComputeTransitiveClosure(dig01);
  InstrPrint(); // Imprime os contadores após a execução
  printf("The transitive closure:\n");
  // Displaying in DOT format
  //GraphDisplayDOT(tcdig01);
  printf("\n");

  GraphCheckInvariants(tcdig01);

  // Reading a directed graph from file
  FILE* file = fopen("DG_2.txt", "r");
  Graph* dig03 = GraphFromFile(file);
  fclose(file);
  // Displaying in DOT format
  //GraphDisplayDOT(dig03);
  printf("\n");

  GraphCheckInvariants(dig03);

  printf("Computing Transitive Closure for graph from file...\n");
  InstrReset();
  Graph* tcdig03 = GraphComputeTransitiveClosure(dig03);
  InstrPrint();
  printf("The transitive closure:\n");
  // Displaying in DOT format
  //GraphDisplayDOT(tcdig03);
  printf("\n");

  GraphCheckInvariants(tcdig03);

  const char* filenames[] = {
        /*"GRAFOS_ORIENTADOS/j1.txt",
        "GRAFOS_ORIENTADOS/j2.txt",
        "GRAFOS_ORIENTADOS/j3.txt",
        "GRAFOS_ORIENTADOS/j4.txt",
        "GRAFOS_ORIENTADOS/j5.txt",
        "GRAFOS_ORIENTADOS/j6.txt",
        "GRAFOS_ORIENTADOS/j7.txt",
        "GRAFOS_ORIENTADOS/j8.txt",
        "GRAFOS_ORIENTADOS/j9.txt",
        "GRAFOS_ORIENTADOS/j10.txt",
        "GRAFOS_ORIENTADOS/j11.txt",
        "GRAFOS_ORIENTADOS/j12.txt",
        "GRAFOS_ORIENTADOS/j13.txt",
        "GRAFOS_ORIENTADOS/j14.txt",
        "GRAFOS_ORIENTADOS/j15.txt"
        "GRAFOS_ORIENTADOS/j16.txt",
        "GRAFOS_ORIENTADOS/j17.txt",
        "GRAFOS_ORIENTADOS/j18.txt",
        "GRAFOS_ORIENTADOS/j19.txt",
        "GRAFOS_ORIENTADOS/j20.txt"
        "GRAFOS_ORIENTADOS/jj0.txt",
        "GRAFOS_ORIENTADOS/jj1.txt",
        "GRAFOS_ORIENTADOS/jj2.txt",
        "GRAFOS_ORIENTADOS/jj3.txt",
        "GRAFOS_ORIENTADOS/jj4.txt",
        "GRAFOS_ORIENTADOS/jj5.txt",
        "GRAFOS_ORIENTADOS/jj6.txt"
        "GRAFOS_ORIENTADOS/jj7.txt",
        "GRAFOS_ORIENTADOS/jj8.txt",
        "GRAFOS_ORIENTADOS/jj9.txt",
        "GRAFOS_ORIENTADOS/jj10.txt",
        "GRAFOS_ORIENTADOS/jj11.txt",
        "GRAFOS_ORIENTADOS/jj12.txt",
        "GRAFOS_ORIENTADOS/jj13.txt",
        "GRAFOS_ORIENTADOS/jj14.txt",
        "GRAFOS_ORIENTADOS/jj15.txt",
        "GRAFOS_ORIENTADOS/jj16.txt",

        
"GRAFOS_ORIENTADOS/other/ll11.txt",
"GRAFOS_ORIENTADOS/other/ll12.txt",
"GRAFOS_ORIENTADOS/other/ll13.txt",
"GRAFOS_ORIENTADOS/other/ll14.txt",
"GRAFOS_ORIENTADOS/other/ll15.txt",
"GRAFOS_ORIENTADOS/other/ll16.txt",
"GRAFOS_ORIENTADOS/other/ll17.txt",
"GRAFOS_ORIENTADOS/other/ll18.txt",
"GRAFOS_ORIENTADOS/other/ll19.txt",
"GRAFOS_ORIENTADOS/other/ll20.txt",
"GRAFOS_ORIENTADOS/other/ll21.txt",
"GRAFOS_ORIENTADOS/other/ll22.txt",
"GRAFOS_ORIENTADOS/other/ll24.txt",
"GRAFOS_ORIENTADOS/other/ll25.txt",
"GRAFOS_ORIENTADOS/other/ll26.txt",
"GRAFOS_ORIENTADOS/other/ll27.txt",
"GRAFOS_ORIENTADOS/other/ll28.txt",
"GRAFOS_ORIENTADOS/other/ll29.txt",
"GRAFOS_ORIENTADOS/other/ll30.txt",
"GRAFOS_ORIENTADOS/other/ll31.txt",
"GRAFOS_ORIENTADOS/other/ll32.txt",
"GRAFOS_ORIENTADOS/other/ll33.txt",
"GRAFOS_ORIENTADOS/other/ll34.txt",
"GRAFOS_ORIENTADOS/other/ll35.txt",
"GRAFOS_ORIENTADOS/other/ll37.txt",
"GRAFOS_ORIENTADOS/other/ll38.txt",
"GRAFOS_ORIENTADOS/other/ll39.txt",
"GRAFOS_ORIENTADOS/other/ll4.txt",
"GRAFOS_ORIENTADOS/other/ll40.txt",
"GRAFOS_ORIENTADOS/other/ll41.txt",
"GRAFOS_ORIENTADOS/other/ll42.txt",
"GRAFOS_ORIENTADOS/other/ll43.txt",
"GRAFOS_ORIENTADOS/other/ll47.txt",
"GRAFOS_ORIENTADOS/other/ll48.txt",
"GRAFOS_ORIENTADOS/other/ll49.txt",
"GRAFOS_ORIENTADOS/other/ll5.txt",
"GRAFOS_ORIENTADOS/other/ll50.txt",
"GRAFOS_ORIENTADOS/other/ll51.txt",
"GRAFOS_ORIENTADOS/other/ll53.txt",
"GRAFOS_ORIENTADOS/other/ll54.txt",
"GRAFOS_ORIENTADOS/other/ll55.txt",
"GRAFOS_ORIENTADOS/other/ll57.txt",
"GRAFOS_ORIENTADOS/other/ll62.txt",
"GRAFOS_ORIENTADOS/other/ll64.txt",
"GRAFOS_ORIENTADOS/other/ll7.txt",
"GRAFOS_ORIENTADOS/other/ll70.txt",
"GRAFOS_ORIENTADOS/other/ll72.txt",
"GRAFOS_ORIENTADOS/other/ll8.txt",*/
"GRAFOS_ORIENTADOS/other2/ll10.txt",
"GRAFOS_ORIENTADOS/other2/ll11.txt",
"GRAFOS_ORIENTADOS/other2/ll12.txt",
"GRAFOS_ORIENTADOS/other2/ll13.txt",
"GRAFOS_ORIENTADOS/other2/ll14.txt",
"GRAFOS_ORIENTADOS/other2/ll19.txt",
"GRAFOS_ORIENTADOS/other2/ll21.txt",
"GRAFOS_ORIENTADOS/other2/ll22.txt",
"GRAFOS_ORIENTADOS/other2/ll26.txt",
"GRAFOS_ORIENTADOS/other2/ll28.txt",
"GRAFOS_ORIENTADOS/other2/ll30.txt",
"GRAFOS_ORIENTADOS/other2/ll31.txt",
"GRAFOS_ORIENTADOS/other2/ll32.txt",
"GRAFOS_ORIENTADOS/other2/ll34.txt",
"GRAFOS_ORIENTADOS/other2/ll36.txt",
"GRAFOS_ORIENTADOS/other2/ll37.txt",
"GRAFOS_ORIENTADOS/other2/ll40.txt",
"GRAFOS_ORIENTADOS/other2/ll41.txt",
"GRAFOS_ORIENTADOS/other2/ll5.txt", 
"GRAFOS_ORIENTADOS/other2/ll50.txt",
"GRAFOS_ORIENTADOS/other2/ll51.txt",
"GRAFOS_ORIENTADOS/other2/ll52.txt",
"GRAFOS_ORIENTADOS/other2/ll6.txt",
"GRAFOS_ORIENTADOS/other2/ll8.txt",

    };

  const unsigned int numFiles = 24;

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
      //GraphDisplayDOT(digraph);
      printf("\n");

      // Verifica invariantes do grafo
      GraphCheckInvariants(digraph);

      printf("Computing Transitive Closure for graph from file...\n");
      InstrReset();
      Graph* tcdig = GraphComputeTransitiveClosure(digraph);
      InstrPrint();
      printf("The transitive closure:\n");
      // Displaying in DOT format
      ////GraphDisplayDOT(tcdig);
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
