TestTransitiveClosure (OK)
 -> igual as imagens de exemplo
 
TestEccentricityMeasures (OK?)  
    digraph {
    // Vertices = 15
    // Edges = 26
    // Max Out-Degree = 3
    0;
    0 -> 1;
    0 -> 2;
    1;
    1 -> 3;
    1 -> 4;
    2;
    2 -> 1;
    2 -> 5;
    2 -> 6;
    3;
    3 -> 7;
    3 -> 8;
    4;
    4 -> 3;
    4 -> 9;
    4 -> 10;
    5;
    5 -> 4;
    5 -> 11;
    5 -> 12;
    6;
    6 -> 5;
    6 -> 13;
    6 -> 14;
    7;
    7 -> 14;
    8;
    8 -> 7;
    9;
    9 -> 8;
    10;
    10 -> 9;
    11;
    11 -> 10;
    12;
    12 -> 11;
    13;
    13 -> 12;
    14;
    14 -> 13;
    }

    Graph Radius: 3
    Graph Diameter: 7
    Vertex Eccentricity Values:
    Vertex 0: 3
    Vertex 1: 6
    Vertex 2: 3
    Vertex 3: 7
    Vertex 4: 6
    Vertex 5: 5
    Vertex 6: 4
    Vertex 7: 7
    Vertex 8: 7
    Vertex 9: 7
    Vertex 10: 7
    Vertex 11: 7
    Vertex 12: 7
    Vertex 13: 7
    Vertex 14: 7
    Central Vertices:
    Vertex 0
    Vertex 2
    acho que ta certo

TestCreateTranspose (falta o teste para o dig03)
-> igual a imagem de exemplo mas falta para o dig03

TestBellmanFordAlg (OK)
-> igual as imagens de teste

TestAllPairsShortestDistances
-> igual as imagens de teste