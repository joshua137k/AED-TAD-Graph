import random

def generate_graph_txt(num_vertices, degree, filename):
    """
    Gera um grafo com grau máximo especificado e salva no formato TXT.

    :param num_vertices: Número de vértices no grafo.
    :param degree: Grau máximo de cada vértice.
    :param filename: Nome do arquivo para salvar o grafo.
    """
    edges = []
    print(degree)
    degree_count = {i: 0 for i in range(num_vertices)}

    # Gera arestas aleatórias garantindo o grau máximo
    for u in range(num_vertices):
        while degree_count[u] < degree:
            v = random.randint(0, num_vertices - 1)
            if u != v and degree_count[v] < degree and (u, v) not in edges and (v, u) not in edges:
                edges.append((u, v))
                degree_count[u] += 1
                degree_count[v] += 1

    # Salva no formato esperado
    with open(filename, "w") as f:
        f.write("1\n")
        f.write("0\n")
        f.write(f"{num_vertices}\n")
        f.write(f"{len(edges)}\n")
        for u, v in edges:
            f.write(f"{u} {v}\n")

# Gera 5 grafos com mais de 50 vértices e grau máximo 2
for i in range(5,100):
    num_vertices = i
    print(num_vertices)
    filename = f"ll{i}.txt"
    generate_graph_txt(num_vertices, degree=2, filename=filename)
