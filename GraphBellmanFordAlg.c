//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphBellmanFord - Bellman-Ford Algorithm
//

// Student Name : Joshua Dourado
// Student Number : 115799
// Student Name : Alexandre Almeida
// Student Number : 119380

/*** COMPLETE THE GraphBellmanFordAlgExecute FUNCTION ***/

#include "GraphBellmanFordAlg.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


#include "Graph.h"
#include "IntegersStack.h"
#include "instrumentation.h"

struct _GraphBellmanFordAlg {
  unsigned int* marked;  // To mark vertices when reached for the first time
  int* distance;  // The number of edges on the path from the start vertex
                  // distance[i]=-1, if no path found from the start vertex to i
  int* predecessor;  // The predecessor vertex in the shortest path
                     // predecessor[i]=-1, if no predecessor exists
  Graph* graph;
  unsigned int startVertex;  // The root of the shortest-paths tree
};


GraphBellmanFordAlg* GraphBellmanFordAlgExecute(Graph* g, unsigned int startVertex) {
    assert(g != NULL);
    assert(startVertex < GraphGetNumVertices(g));
    assert(GraphIsWeighted(g) == 0); // Garantir que o grafo é ponderado
    
    unsigned int numVertices = GraphGetNumVertices(g);

    GraphBellmanFordAlg* result =
        (GraphBellmanFordAlg*)malloc(sizeof(struct _GraphBellmanFordAlg));
    assert(result != NULL);
    
    InstrReset();     // Resetar contadores
    result->graph = g;
    result->startVertex = startVertex;

    result->marked = (unsigned int*)calloc(numVertices, sizeof(unsigned int));
    result->distance = (int*)malloc(numVertices * sizeof(int));
    result->predecessor = (int*)malloc(numVertices * sizeof(int));

    assert(result->marked != NULL && result->distance != NULL && result->predecessor != NULL);

    // Inicializar distâncias e predecessores
    for (unsigned int i = 0; i < numVertices; i++) {
        result->distance[i] = -1; // "Infinito" representado por -1
        result->predecessor[i] = -1; // Nenhum predecessor inicialmente
        InstrCount[0] += 2; // Acesso à memória
    }

    // Definir a distância para o vértice inicial como 0
    result->distance[startVertex] = 0;

    // Relaxar arestas (numVertices - 1) vezes
    for (unsigned int step = 1; step < numVertices; step++) {
        for (unsigned int u = 0; u < numVertices; u++) {
            unsigned int* adjacents = GraphGetAdjacentsTo(g, u);
            double* distances = GraphGetDistancesToAdjacents(g, u);

            for (unsigned int i = 0; i < adjacents[0]; i++) {
                unsigned int v = adjacents[i + 1];
                double weight = distances[i + 1];
                InstrCount[0] += 2; // Acesso à memória

                if (result->distance[u] != -1 &&
                    (result->distance[v] == -1 || result->distance[u] + weight < result->distance[v])) {
                    result->distance[v] = result->distance[u] + weight;
                    result->predecessor[v] = u;
                    InstrCount[0] += 2; // Acesso à memória
                    InstrCount[1]++;   // Soma
                }
            }

            free(adjacents);
            free(distances);
        }
    }

    // Verificar ciclos negativos
    /*
    for (unsigned int u = 0; u < numVertices; u++) {
        unsigned int* adjacents = GraphGetAdjacentsTo(g, u);
        double* distances = GraphGetDistancesToAdjacents(g, u);

        for (unsigned int i = 0; i < adjacents[0]; i++) {
            unsigned int v = adjacents[i + 1];
            double weight = distances[i + 1];

            if (result->distance[u] != -1 &&
                result->distance[v] != -1 &&
                result->distance[u] + weight < result->distance[v]) {
                fprintf(stderr, "Graph contains a negative-weight cycle\n");
                free(adjacents);
                free(distances);
                GraphBellmanFordAlgDestroy(&result);
                return NULL;
            }
        }

        free(adjacents);
        free(distances);
    }*/

    // Atualizar vértices alcançados
    for (unsigned int i = 0; i < numVertices; i++) {
        if (result->distance[i] != -1) {
            result->marked[i] = 1;
            InstrCount[0]++; // Acesso à memória
        }
    }

    return result;
}


void GraphBellmanFordAlgDestroy(GraphBellmanFordAlg** p) {
  assert(*p != NULL);

  GraphBellmanFordAlg* aux = *p;

  free(aux->marked);
  free(aux->predecessor);
  free(aux->distance);

  free(*p);
  *p = NULL;
}

// Getting the paths information

int GraphBellmanFordAlgReached(const GraphBellmanFordAlg* p, unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  return p->marked[v];
}

int GraphBellmanFordAlgDistance(const GraphBellmanFordAlg* p, unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  return p->distance[v];
}
Stack* GraphBellmanFordAlgPathTo(const GraphBellmanFordAlg* p, unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  Stack* s = StackCreate(GraphGetNumVertices(p->graph));

  if (p->marked[v] == 0) {
    return s;
  }

  // Store the path
  for (unsigned int current = v; current != p->startVertex;
       current = p->predecessor[current]) {
    StackPush(s, current);
  }

  StackPush(s, p->startVertex);

  return s;
}

// DISPLAYING on the console

void GraphBellmanFordAlgShowPath(const GraphBellmanFordAlg* p, unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  Stack* s = GraphBellmanFordAlgPathTo(p, v);

  while (StackIsEmpty(s) == 0) {
    printf("%d ", StackPop(s));
  }

  StackDestroy(&s);
}

// Display the Shortest-Paths Tree in DOT format
void GraphBellmanFordAlgDisplayDOT(const GraphBellmanFordAlg* p) {
  assert(p != NULL);

  Graph* original_graph = p->graph;
  unsigned int num_vertices = GraphGetNumVertices(original_graph);

  // The paths tree is a digraph, with no edge weights
  Graph* paths_tree = GraphCreate(num_vertices, 1, 0);

  // Use the predecessors array to add the tree edges
  for (unsigned int w = 0; w < num_vertices; w++) {
    // Vertex w has a predecessor vertex v?
    int v = p->predecessor[w];
    if (v != -1) {
      GraphAddEdge(paths_tree, (unsigned int)v, w);
    }
  }

  // Display the tree in the DOT format
  GraphDisplayDOT(paths_tree);

  // Housekeeping
  GraphDestroy(&paths_tree);
}
