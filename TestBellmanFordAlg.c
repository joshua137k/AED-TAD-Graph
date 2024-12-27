//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira, Joao Manuel Rodrigues - Dec 2024
//
// Testing the Bellman-Ford algorithm
//

#include <assert.h>

#include "Graph.h"
#include "GraphBellmanFordAlg.h"
#include "instrumentation.h"

int main(void) {
  InstrName[0] = "memops";
  InstrName[1] = "adds";
  InstrCalibrate(); // Calibrar os contadores
  

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

  // Bellman-Ford Algorithm

  // Consider each vertex as a start vertex
  InstrReset();     // Resetar contadores
  for (unsigned int i = 0; i < 6; i++) {
    
    GraphBellmanFordAlg* BF_result = GraphBellmanFordAlgExecute(dig01, i);

   // printf("The shortest path tree rooted at %u\n", i);
    //GraphBellmanFordAlgDisplayDOT(BF_result);
   
    printf("\n");

    GraphBellmanFordAlgDestroy(&BF_result);
  }
  InstrPrint();

  // What kind of graph is g01?
  Graph* g01 = GraphCreate(6, 0, 0);
  GraphAddEdge(g01, 0, 5);
  GraphAddEdge(g01, 2, 4);
  GraphAddEdge(g01, 2, 3);
  GraphAddEdge(g01, 1, 2);
  GraphAddEdge(g01, 0, 1);
  GraphAddEdge(g01, 3, 4);
  GraphAddEdge(g01, 3, 5);
  GraphAddEdge(g01, 0, 2);
  printf("The graph:\n");
  // Displaying in DOT format
  GraphDisplayDOT(g01);
  printf("\n");

  GraphCheckInvariants(g01);

  // Bellman-Ford Algorithm

  // Consider each vertex as a start vertex
  InstrReset();     // Resetar contadores
  for (unsigned int i = 0; i < 6; i++) {
    
    GraphBellmanFordAlg* BF_result = GraphBellmanFordAlgExecute(g01, i);

   // printf("The shortest path tree rooted at %u\n", i);
    //GraphBellmanFordAlgDisplayDOT(BF_result);
  
    printf("\n");

    GraphBellmanFordAlgDestroy(&BF_result);
  }
  InstrPrint();

  // Reading a directed graph from file
  FILE* file = fopen("DG_2.txt", "r");
  Graph* dig03 = GraphFromFile(file);
  fclose(file);
  // Displaying in DOT format
  GraphDisplayDOT(dig03);
  printf("\n");

  GraphCheckInvariants(dig03);

  // Bellman-Ford Algorithm

  // Consider each vertex as a start vertex
  InstrReset();     // Resetar contadores
  for (unsigned int i = 0; i < GraphGetNumVertices(dig03); i++) {
    
    GraphBellmanFordAlg* BF_result = GraphBellmanFordAlgExecute(dig03, i);

   // printf("The shortest path tree rooted at %u\n", i);
    //GraphBellmanFordAlgDisplayDOT(BF_result);
   
    printf("\n");

    GraphBellmanFordAlgDestroy(&BF_result);
  }
  InstrPrint();

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

      // Bellman-Ford Algorithm para cada vértice
      unsigned int numVertices = GraphGetNumVertices(digraph);
      InstrReset();     // Resetar contadores
      for (unsigned int i = 0; i < numVertices; i++) {
          GraphBellmanFordAlg* BF_result = GraphBellmanFordAlgExecute(digraph, i);

          //printf("The shortest path tree rooted at vertex %u:\n", i);
          // GraphBellmanFordAlgDisplayDOT(BF_result); // Se necessário, descomente esta linha
          
          printf("\n");

          GraphBellmanFordAlgDestroy(&BF_result);
      }
      InstrPrint();

      // Destroi o grafo
      GraphDestroy(&digraph);
  }

  GraphDestroy(&g01);
  GraphDestroy(&dig01);
  GraphDestroy(&dig03);

  return 0;
}
