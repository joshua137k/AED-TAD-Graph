//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphEccentricityMeasures
//

// Student Name :
// Student Number :
// Student Name :
// Student Number :

/*** COMPLETE THE GraphEccentricityMeasuresCompute FUNCTION ***/
/*** COMPLETE THE GraphGetCentralVertices FUNCTION ***/
/*** COMPLETE THE GraphEccentricityMeasuresPrint FUNCTION ***/

#include "GraphEccentricityMeasures.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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
    GraphEccentricityMeasures* measures = (GraphEccentricityMeasures*)malloc(sizeof(GraphEccentricityMeasures));
    assert(measures != NULL);

    measures->graph = g;
    measures->eccentricity = (int*)malloc(numVertices * sizeof(int));
    assert(measures->eccentricity != NULL);

    measures->graphRadius = INT_MAX;  // Inicializa com um valor alto
    measures->graphDiameter = -1;    // Inicializa com um valor baixo

    GraphAllPairsShortestDistances* apsd = GraphAllPairsShortestDistancesExecute(g);
    assert(apsd != NULL);

    // Calcula a excentricidade de cada vértice
    for (unsigned int v = 0; v < numVertices; v++) {
        int maxDistance = -1;
        for (unsigned int w = 0; w < numVertices; w++) {
            int distance = GraphGetDistanceVW(apsd, v, w);
            if (distance > maxDistance) {
                maxDistance = distance;
            }
        }
        measures->eccentricity[v] = maxDistance;

        // Atualiza raio e diâmetro do grafo
        if (maxDistance != -1) {  // Ignora vértices não alcançáveis
            if (maxDistance < measures->graphRadius) {
                measures->graphRadius = maxDistance;
            }
            if (maxDistance > measures->graphDiameter) {
                measures->graphDiameter = maxDistance;
            }
        }
    }

    // Determina os vértices centrais (com excentricidade igual ao raio)
    unsigned int centralCount = 0;
    for (unsigned int v = 0; v < numVertices; v++) {
        if (measures->eccentricity[v] == measures->graphRadius) {
            centralCount++;
        }
    }

    measures->centralVertices = (unsigned int*)malloc((centralCount + 1) * sizeof(unsigned int));
    assert(measures->centralVertices != NULL);
    measures->centralVertices[0] = centralCount;

    unsigned int index = 1;
    for (unsigned int v = 0; v < numVertices; v++) {
        if (measures->eccentricity[v] == measures->graphRadius) {
            measures->centralVertices[index++] = v;
        }
    }

    GraphAllPairsShortestDistancesDestroy(&apsd);

    return measures;
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

    // Retorna uma cópia do vetor de vértices centrais
    unsigned int centralCount = p->centralVertices[0];
    unsigned int* copy = (unsigned int*)malloc((centralCount + 1) * sizeof(unsigned int));
    assert(copy != NULL);
    for (unsigned int i = 0; i <= centralCount; i++) {
        copy[i] = p->centralVertices[i];
    }

    return copy;
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
