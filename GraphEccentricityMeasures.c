//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphEccentricityMeasures
//

// Student Name : Joshua Dourado
// Student Number : 115799
// Student Name : Alexandre Almeida
// Student Number : 119380

/*** COMPLETE THE GraphEccentricityMeasuresCompute FUNCTION ***/
/*** COMPLETE THE GraphGetCentralVertices FUNCTION ***/
/*** COMPLETE THE GraphEccentricityMeasuresPrint FUNCTION ***/

#include "GraphEccentricityMeasures.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphAllPairsShortestDistances.h"

struct _GraphEccentricityMeasures {
  unsigned int*
      centralVertices;  // centralVertices[0] = number of central vertices
                        // array size is (number of central vertices + 1)
  int* eccentricity;    // the eccentricity value of each vertex
  Graph* graph;         // the graph
  int graphRadius;      // the graph radius
  int graphDiameter;    // the graph diameter
};

// Allocate memory
// Compute the vertex eccentricity values
// Compute graph radius and graph diameter
// Compute the set of central vertices
GraphEccentricityMeasures* GraphEccentricityMeasuresCompute(Graph* g) {
    assert(g != NULL);

    unsigned int numVertices = GraphGetNumVertices(g);

    GraphEccentricityMeasures* result =
        (GraphEccentricityMeasures*)malloc(sizeof(GraphEccentricityMeasures));
    assert(result != NULL);

    result->graph = g;
    result->eccentricity = (int*)malloc(numVertices * sizeof(int));
    assert(result->eccentricity != NULL);

    // Executar o cálculo das distâncias mais curtas entre todos os pares
    GraphAllPairsShortestDistances* distances = GraphAllPairsShortestDistancesExecute(g);

    result->graphRadius = -1;  // Valor indefinido inicialmente
    result->graphDiameter = -1; // Valor indefinido inicialmente

    // Calcular excentricidade para cada vértice
    for (unsigned int v = 0; v < numVertices; v++) {
        int maxDistance = -1;
        for (unsigned int u = 0; u < numVertices; u++) {
            int distance = GraphGetDistanceVW(distances, v, u);
            if (distance != -1 && distance > maxDistance) {
                maxDistance = distance;
            }
        }
        result->eccentricity[v] = maxDistance;

        // Atualizar o raio e o diâmetro do grafo
        if (maxDistance != -1) {
            if (result->graphRadius == -1 || maxDistance < result->graphRadius) {
                result->graphRadius = maxDistance;
            }
            if (maxDistance > result->graphDiameter) {
                result->graphDiameter = maxDistance;
            }
        }
    }

    // Encontrar os vértices centrais
    unsigned int centralCount = 0;
    for (unsigned int v = 0; v < numVertices; v++) {
        if (result->eccentricity[v] == result->graphRadius) {
            centralCount++;
        }
    }

    result->centralVertices = (unsigned int*)malloc((centralCount + 1) * sizeof(unsigned int));
    assert(result->centralVertices != NULL);
    result->centralVertices[0] = centralCount;

    unsigned int idx = 1;
    for (unsigned int v = 0; v < numVertices; v++) {
        if (result->eccentricity[v] == result->graphRadius) {
            result->centralVertices[idx++] = v;
        }
    }

    // Liberar memória das distâncias
    GraphAllPairsShortestDistancesDestroy(&distances);

    return result;
}


void GraphEccentricityMeasuresDestroy(GraphEccentricityMeasures** p) {
  assert(*p != NULL);

  GraphEccentricityMeasures* aux = *p;

  free(aux->centralVertices);
  free(aux->eccentricity);

  free(*p);
  *p = NULL;
}

// Getting the computed measures

int GraphGetRadius(const GraphEccentricityMeasures* p) {
  assert(p != NULL);

  return p->graphRadius;
}

int GraphGetDiameter(const GraphEccentricityMeasures* p) {
  assert(p != NULL);

  return p->graphDiameter;
}

int GraphGetVertexEccentricity(const GraphEccentricityMeasures* p,
                               unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));
  assert(p->eccentricity != NULL);

  return p->eccentricity[v];
}

// Getting a copy of the set of central vertices
// centralVertices[0] = number of central vertices in the set
unsigned int* GraphGetCentralVertices(const GraphEccentricityMeasures* p) {
    assert(p != NULL);
    assert(p->centralVertices != NULL);

    unsigned int centralCount = p->centralVertices[0];
    unsigned int* centralVertices = (unsigned int*)malloc((centralCount + 1) * sizeof(unsigned int));
    assert(centralVertices != NULL);

    for (unsigned int i = 0; i <= centralCount; i++) {
        centralVertices[i] = p->centralVertices[i];
    }

    return centralVertices;
}

// Print the graph radius and diameter
// Print the vertex eccentricity values
// Print the set of central vertices
void GraphEccentricityMeasuresPrint(const GraphEccentricityMeasures* p) {
    assert(p != NULL);

    printf("Graph Radius: %d\n", p->graphRadius);
    printf("Graph Diameter: %d\n", p->graphDiameter);

    printf("Vertex Eccentricity Values:\n");
    for (unsigned int v = 0; v < GraphGetNumVertices(p->graph); v++) {
        printf("Vertex %u: %d\n", v, p->eccentricity[v]);
    }

    printf("Central Vertices:\n");
    unsigned int centralCount = p->centralVertices[0];
    for (unsigned int i = 1; i <= centralCount; i++) {
        printf("Vertex %u\n", p->centralVertices[i]);
    }
}
