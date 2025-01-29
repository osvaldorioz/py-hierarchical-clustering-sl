#### 🔹 **Hierarchical Clustering (Clustering Jerárquico)**
Es un algoritmo de agrupamiento que construye una jerarquía de clusters. Existen dos enfoques principales:
1. **Aglomerativo (Bottom-Up)**: Comienza con cada punto como un cluster individual y los fusiona progresivamente.
2. **Divisivo (Top-Down)**: Comienza con un solo cluster y lo divide en subclusters.

El método **aglomerativo** es el más común, y dentro de este, hay varias formas de medir la distancia entre clusters. Una de ellas es **Single Linkage**.

---

#### 🔹 **Single Linkage (Enlace Simple)**
Este método mide la distancia entre dos clusters como la distancia más corta entre cualquier par de puntos, uno de cada cluster:

\[
d(A, B) = \min_{i \in A, j \in B} d(i, j)
\]

Donde:
- \( A \) y \( B \) son clusters.
- \( d(i, j) \) es la distancia entre los puntos \( i \) y \( j \).

---

#### 🔹 **Pasos del Algoritmo Aglomerativo con Single Linkage**
1. **Inicialización**: Cada punto es un cluster individual.
2. **Cálculo de Distancias**: Se calcula la distancia entre todos los clusters usando la métrica Single Linkage.
3. **Fusión**: Se combinan los dos clusters más cercanos.
4. **Actualización**: Se recalcula la distancia entre el nuevo cluster fusionado y los demás.
5. **Repetición**: Se repiten los pasos 3 y 4 hasta que solo queda un cluster.

---

#### 🔹 **Ventajas y Desventajas**
 **Ventajas**:
- Captura estructuras en forma de cadena o agrupamientos irregulares.
- No requiere especificar el número de clusters.

 **Desventajas**:
- Sensible a outliers.
- Puede generar clusters poco compactos.

---
