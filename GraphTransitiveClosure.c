//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphTransitiveClosure - Transitive Closure of a directed graph
//

// Student Name : Joshua Dourado
// Student Number : 115799
// Student Name : Alexandre Almeida
// Student Number : 119380

/*** COMPLETE THE GraphComputeTransitiveClosure FUNCTION ***/

#include "GraphTransitiveClosure.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphBellmanFordAlg.h"
#include "instrumentation.h"

// Compute the transitive closure of a directed graph
// Return the computed transitive closure as a directed graph
// Use the Bellman-Ford algorithm
Graph* GraphComputeTransitiveClosure(Graph* g) {
    assert(g != NULL);
    assert(GraphIsDigraph(g));
    assert(GraphIsWeighted(g) == 0);

    unsigned int numVertices = GraphGetNumVertices(g);
    InstrCount[3] = numVertices; // Guardar o número de vértices
    InstrCount[4] = 2 * numVertices; //2 is a max degree for testes

    // Cria o grafo do fecho transitivo com o mesmo número de vértices
    Graph* transitiveClosure = GraphCreate(numVertices, 1, 0);

    for (unsigned int v = 0; v < numVertices; v++) {
        InstrCount[0]++; // Contar um acesso à memória (loop externo)

        // Executa o algoritmo de Bellman-Ford a partir de cada vértice
        GraphBellmanFordAlg* bfResult = GraphBellmanFordAlgExecute(g, v);
        assert(bfResult != NULL);

        for (unsigned int w = 0; w < numVertices; w++) {
            //InstrCount[0]++; // Contar um acesso à memória (loop interno)
            // Se o vértice w for alcançável a partir de v, adiciona a aresta (v, w)
            if (GraphBellmanFordAlgReached(bfResult, w) && v != w) {
                GraphAddEdge(transitiveClosure, v, w);
                //InstrCount[1]++; // Contar uma operação de adição de aresta
            }
        }

        // Libera os recursos do algoritmo Bellman-Ford
        GraphBellmanFordAlgDestroy(&bfResult);
    }

    return transitiveClosure;
}

