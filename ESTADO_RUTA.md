# ESTADO_RUTA: dónde estamos y hacia dónde va la ruta

**Última actualización:** 2026-11-08 (noche), Mac. (Si hay commits posteriores a esta fecha, reconciliar antes de enseñar.)

## 1. Quién es y qué quiere

Nicolás Ariza Rodríguez. Ingeniería de Sistemas (4.º semestre, PUJ Cali) + Ingeniería Mecánica (6.º). C++ es su
lenguaje favorito y el que quiere seguir usando. Metas de fondo: **análisis por elementos finitos con interfaz
gráfica** (proyecto de grado, dominio aún abierto entre estructural y transferencia de calor), **IA propia /
machine learning** (interés nuevo, ver §8) y robótica. Curso de Estructuras de Datos con el profesor Gonzalo Noreña.
Está exonerado del parcial del 3-nov (ya tiene 5.0). El **Proyecto Final "Simulador de Urgencias"** (entrega
23-nov, grupos de 3, sustentación individual) se lleva en OTRO chat: no mezclarlo acá.

## 2. La dirección de la ruta (el porqué)

```
Estructuras de datos (C++ sin apuro, a fondo)
   ordenamiento / búsqueda / hash   ✅
   STL: iteradores, map/set, lambdas y <algorithm>/<numeric>   ← ESTAMOS ACÁ
   árboles  →  grafos
        │
        ├── Métodos numéricos (libro de Chapra, chat aparte)  →  matriz de rigidez, sistemas lineales, etc.
        │        │
        │        └── FEM / mallado completo (DIFERIDO hasta terminar Chapra y tener base de termo/mecánica)
        │
        └── Machine learning (ruta paralela, `10-09-26/ruta_ml/`): base numérica → clásico → redes → herramientas → ML en ingeniería
```

- Las estructuras de datos son la base común de todo. La **malla** (nodos, triángulos, aristas, borde) se usa solo
  como **aplicación** para practicar estructuras, no como estudio de FEM todavía.
- Decisión de Nicolás (6-nov): NO meterse a fondo en FEM (matriz de rigidez, ensamble, cuánto discretizar,
  gráficos con modelo) hasta terminar Chapra y haber visto transferencia de calor. No proponer libros ni teoría
  de FEM antes de ese punto. Recordárselo cuando llegue el momento.
- Lo que se estudia en STL tiene un segundo objetivo: servir para métodos numéricos (lambdas como `f(x)` para
  bisección/integración, `<numeric>`, etc.).

## 3. Cerrado y verificado (código en `codigo/estructuras/codigo_universidad/`)

- Listas simples, circulares, dobles y centinela; pilas y colas (nodos y arreglo); regla de los tres.
- Ordenamientos: burbuja, selección, inserción, merge (el suyo y el del profesor), quick; **counting sort**
  (`ordenamientos/parametrico/parametrico.cpp`: versión simple y `ordenamientoEstable<T,Clave>` genérica, probada
  con 20.000 casos). Regla que formuló él: counting sort conviene si n ≥ rango.
- Búsqueda lineal, binaria y ternaria. Tablas hash (`tabla_hash/`; `hash2.cpp` con `vector<list<pair>>`).
- **STL (`libreria_stl/`):**
  - 1a Iteradores (`iteradores/iteradores1.cpp`): rango `[begin,end)`, categorías, invalidación, patrón "o
    borrás o avanzás" con `it = erase(it)`, `erase` en bucle O(n²) vs `remove_if` O(n) (medido).
  - 1b `map`/`unordered_map`/`set` (`mapas/`): costos, la trampa de `[]`, `find/count/at`, `insert`/`try_emplace`
    y `.second`, `sort`+`unique`, rehash y `reserve` (sin reserve: 20 rehashes para 1e6; con reserve: 0),
    `lower_bound`/`upper_bound`, **claves compuestas** (`pair` como arista normalizada (menor,mayor), hash propio
    `HashArista` sin `%`: `funcionHashUnd.cpp`).
  - **Integrador 1 "Tienda de barrio"** (`integrador1/integrador1.cpp`): 10 métodos, 0 fallos en 3000 rondas
    diferenciales. Faltan main, separación hpp/cpp, tabla de medición con `<chrono>` y preguntas escritas
    (las dejó para después).
  - 1c lambdas (`lambdas/`): sintaxis, captura `[x]` vs `[&x]`, `mutable`, template `F` para recibir funciones
    (vs puntero a función vs `std::function`), devolver lambdas (fábricas), vector/mapa de `std::function`.
    Ejercicios E1 (`aplicarFnumVeces`), E2 (`crearFuncionP`) y E3 (`funcionCompuesta`) en `ejercicioLamdas.cpp`:
    lógica correcta y el archivo ya compila (había un nombre de macro pegado por el autocompletado del editor
    en la línea 8). `algoritmosLamba.cpp` (`count_if`, `find_if`, `any_of`): correcto, probado con casos que no
    cumplen nada.

## 4. Descartado por Nicolás (no volver a proponer)

Ejercicios de la clase 12 (paréntesis balanceados, postfija, papa caliente, cola con dos pilas), repaso de listas,
complejidad formal (ya la domina: T(n), contar for, O(n)), `break` de inserción, `hash1.cpp` con lista propia,
`max_element` con comparador (A4). Si algo se olvida, un recordatorio puntual.

## 5. Siguiente (en este orden)

1. **1c.4 `<numeric>`**: `accumulate`, `inner_product`, `iota`, `partial_sum` (útiles para sumatorias, producto
   punto, generar grillas).
2. **A5**: `sort` con criterio compuesto (semestre descendente y nombre alfabético).
3. Opcionales diferidos: E4 (tabla de funciones con vector/mapa de `std::function`), E5 (`biseccion` con template y
   lambda, caso `x²−4` en [0,5] y `cos(x)−x` en [0,1]; decidir qué hace si f(a) y f(b) tienen el mismo signo).
4. **Integrador 2 "topología de malla"** (aplicación): grilla `nx × ny` (nodos `(nx+1)(ny+1)`, triángulos
   `2·nx·ny`), aristas únicas con conteo (1 = borde, 2 = interior), nodos de borde, vecinos de cada nodo, salida SVG.
5. **Árboles** (BST, recorridos, altura, luego balanceo; búsqueda espacial) → **grafos** (BFS/DFS; la malla como grafo).
6. Diferido: 1d LRU cache, Parte C/D del integrador 1, mallado M4-M6. ML corre en paralelo según §8 (ligero hasta cerrar árboles/grafos).

## 6. Mapa de código

```
codigo/estructuras/codigo_universidad/
  ordenamientos/{burbuja,selection,insertion,merge,parametrico}/ + quickSort.cpp
  busquedas/  tabla_hash/  listas/ ...
  libreria_stl/{iteradores, mapas, lambdas, integrador1}/
codigo/PROYECTO/        proyecto FEM real (pausado)
codigo/metodos_numericos/   Chapra (chat aparte)
10-09-26/ruta_codigo/ y ruta-fem/   guías HTML (ver CLAUDE.md)
```

## 7. Patrones de error de Nicolás (nombrarlos al aparecer; no reexplicar desde cero)

1. Confundir **valor con índice/posición** (`cuenta[j]` en vez de `cuenta[v[j]]`; `v[i]` dentro de una lambda
   que ya recibe el elemento).
2. **Off-by-one** en tamaños y cortes (`b-a` sin `+1`; `lower_bound` vs `upper_bound` como fin de rango).
3. **Dirección invertida** (`a - x` en vez de `x - a`; asignación al revés en listas).
4. Usar un atributo/variable **antes de inicializarlo**, `return` mal ubicado, `[]` sobre vector vacío.
5. **Confundir tipos**: acumulador `int` con valores `double`, `int x` donde va `double`.
6. No contestar las preguntas de verificación **con números** (da la idea, no las cuentas): volver a pedirlas.
7. Avanzar después de borrar (`erase`/`delete`) sin mirar qué quedó en ese lugar.

## 8. Machine learning: la ruta paralela (HTML en `10-09-26/ruta_ml/`)

Decisión del 2026-11-08: ML corre **en paralelo** a las estructuras de datos, Chapra y el FEM, no después. Las estructuras, los
árboles, los grafos y los métodos numéricos son parte de las bases de ML. Se sigue en C++ y se suma Python como herramienta.

**Guías generadas (se abren en el navegador; indice: `10-09-26/ruta_ml/0-indice.html`):**

| Página | Contenido |
|---|---|
| `0-indice.html` | mapa de cobertura: 45 temas de un temario experto vs lo que ya está programado |
| `1-base-numerica.html` | 8 temas: álgebra lineal, mínimos cuadrados, estadística, datos, gradiente, descenso, eficiencia, SVG |
| `2-aprendizaje-clasico.html` | 13 temas: regresión, regularización, logística, k-NN, árboles, bosques, boosting, SVM, k-means, PCA, validación, probabilísticos |
| `3-redes-neuronales.html` | 12 temas: MLP, pérdidas, backprop, XOR, autodiff en C++, optimizadores, CNN, RNN, transformers, generativos, refuerzo |
| `4-herramientas.html` | 7 temas: Python, NumPy, pandas, scikit-learn, PyTorch, Eigen/mlpack, experimentos reproducibles |
| `5-ml-mecanica.html` | 8 temas: leyes físicas con datos, surrogates de FEM, vibraciones, series de tiempo, PINNs, diseño, robótica + proyecto integrador |
| `6-libros-y-cursos.html` | libros/cursos con lo que se verificó y lo que no |
| `7-ruta-combinada.html` | plano de conjunto, fases A-F, criterios de paso, hitos H1-H5 |

Código de los ejemplos (solo fuentes): `10-09-26/ruta_ml/ejemplos/`. Los programas se compilaron y corrieron en la Mac (clang++ -std=c++17);
los de PyTorch y PINN NO se ejecutaron (no hay PyTorch instalado) y están marcados así en las páginas. Los tiempos son de la Mac.
Los tildes de "hecho" de las páginas viven en `localStorage` de cada navegador: NO se sincronizan entre PCs; el avance real se anota acá.

Regla de ritmo (Nicolás): un frente principal; ML en modo ligero hasta cerrar árboles/grafos y Chapra; no abrir la Fase 3 de ML sin pasar los criterios
de la Fase C de `7-ruta-combinada.html`. Nicolás ya vio probabilidad y estadística en la carrera (hace falta repaso, lo hace por su cuenta).

**Siguiente paso acordado:** seguir con estructuras (árboles) y Chapra; empezar ML por 1.1-1.4 en ligero.

## 9. Registro de sesiones

- **2026-11-08, Mac:** cerrado 1c.3 (`count_if`/`find_if`/`any_of`). Se creó `CLAUDE.md` y este archivo para
  continuidad entre la Mac y la nueva PC con Windows. Pendiente: que Nicolás revise `ejercicioLamdas.cpp`,
  haga commit y push.
- **2026-11-08 (noche), Mac:** se investigaron temarios de ML (CS229, Ng, ISLR, d2l, Goodfellow, Géron, Brunton) y se generó la ruta de ML
  paralela en `10-09-26/ruta_ml/` (8 HTML, 48 temas, 27 ejemplos en `ejemplos/`, mapa de cobertura, libros con verificación, plano combinado).
  Se enlazó desde `10-09-26/ruta_codigo/0-indice.html`. Pendiente: Nicolás revisa las páginas, hace commit y push; confirma el temario preliminar.
