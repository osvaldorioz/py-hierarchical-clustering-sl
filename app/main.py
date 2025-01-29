from fastapi import FastAPI
from fastapi.responses import FileResponse
from pydantic import BaseModel
import numpy as np
from typing import List
import matplotlib
import matplotlib.pyplot as plt
import networkx as nx
import hierarchical_clustering
import json

matplotlib.use('Agg')  # Usar backend no interactivo
app = FastAPI()

# Definir el modelo para el vector
class VectorF(BaseModel):
    vector: List[float]
    

@app.post("/hierarchical_linkage")
def calculo(seed: int, n_clusters: int):
    # Generar datos de prueba
    np.random.seed(seed)
    data = np.random.rand(n_clusters, 2)

    # Ejecutar clustering
    linkage_matrix = hierarchical_clustering.hierarchical_clustering(data.tolist())

    # Crear grafo
    G = nx.Graph()
    n = len(data)

    # Añadir nodos (puntos de datos originales)
    for i in range(n):
        G.add_node(i, pos=(data[i, 0], data[i, 1]))

    # Añadir enlaces según la matriz de clustering
    for c1, c2, dist, _ in linkage_matrix:
        G.add_edge(int(c1), int(c2), weight=dist)

    # Dibujar el grafo
    plt.figure(figsize=(10, 6))
    pos = nx.get_node_attributes(G, 'pos')
    nx.draw(G, pos, with_labels=True, node_size=300, node_color="lightblue", edge_color="gray", font_size=8)
    plt.title("Gráfico de red de clustering jerárquico (Single Linkage)")
    plt.grid(True)

    output_file = 'hierarchical_clustering_single_linkage.png'
    plt.savefig(output_file)
    plt.close()


    j1 = {
        "Grafica": output_file
    }
    jj = json.dumps(str(j1))

    return jj

@app.get("/hierarchical_linkage-graph")
def getGraph(output_file: str):
    return FileResponse(output_file, media_type="image/png", filename=output_file)