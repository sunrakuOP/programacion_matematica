# Ruta Fernando — análisis estructural con C++

Este camino se sigue en nombre de Fernando, papá de Nicolás e ingeniero civil — quien trabajó
análisis estructural con OpenGL y después Fortran/Winteracter. Todo lo que hay acá abajo apunta
a lo mismo que él hacía: cálculo estructural/matricial por cuenta propia, primero en C++ y más
adelante en Fortran 90.

**Para la sesión de Claude Code que retome esto:** leé este archivo completo antes de sugerir
nada. Resume dónde está parado Nicolás, qué decisiones ya se tomaron y cómo prefiere que se le
enseñe. No repitas explicaciones que ya se dieron (están resumidas abajo), y no le des un archivo
de teoría — la convención de este track es explicar en el chat, nunca en un `.md` de teoría (este
archivo es la excepción: es un documento de continuidad/estado, no de teoría).

---

## 1. Quién es y qué está haciendo

Nicolás (Juan Nicolás Ariza Rodríguez) es estudiante de doble titulación — Ing. de Sistemas e
Ing. Mecánica, Javeriana Cali. Nivel intermedio-avanzado en C++, en refuerzo activo tras un
tiempo sin programar. Está por entrar a la materia **Estructuras de Datos** del semestre de
Sistemas, y la meta de fondo (la que da sentido a todo esto) es poder hacer análisis estructural
propio — matrices de rigidez, ensamblaje de elementos finitos (FEM), y eventualmente visualización
con OpenGL — primero en C++, después migrando el cálculo pesado a Fortran 90.

**Timeline académico (actualizado 2026-09-28):** terminó Cálculo (integrales por sustitución,
partes, fracciones parciales). En Estática está viendo momentos en 3D, fuerzas en las tres
direcciones y producto cruzado (repaso) — objetivo personal ~1 mes para pasar a Mecánica de
Sólidos. En Termodinámica está en primera ley / balances de energía y ese mismo día vio cómo se
transmite trabajo y potencia a través de un cigüeñal usando torque, con el curso enfocado a
compresores, difusores, turbinas y motores — le está gustando mucho, piensa en una posible maestría
en esa área más adelante. También le interesa aerodinámica (cree que no está en su plan de
estudios). No meter esto en la ruta de C++ actual — es una señal a favor de "transferencia de
calor" como dominio del proyecto de grado (ver sección 5), no currícula nueva para agregar ya.
Nota de conexión: producto cruzado en Estática es la misma álgebra que eventualmente va en
`Vector3D` de `codigo/PROYECTO/` (ver sección 8) — no hace falta forzarla ahora, pero cuando escriba
`Vector3D::cruz()` va a reconocer el cálculo.

## 2. Qué se hizo hasta ahora (en la carpeta VSCODE, antes de mover el trabajo acá)

### 2.1 Repaso completo de C++ (Fases 0-8)
Repaso guiado de fundamentos → punteros → clases → objetos → copy/move → operadores → herencia →
polimorfismo → templates → smart pointers, con teoría en chat + ejercicios compilados y corregidos
en vivo (nunca solución completa de entrada, siempre pistas progresivas). Cerró con un ejercicio
integrador (`repaso_bases/reto1.cpp`, ver sección 3): una mini-simulación de ensamblaje FEM que
combina templates + operadores + herencia/polimorfismo + `unique_ptr`, verificada compilando y
corriendo (salida `7 32`, comprobada a mano).

### 2.2 `cpp-avanzado` — Tier 1 completo (Excepciones, CMake multiarchivo, Catch2 v3)
Se armó un proyecto real (`codigo/cpp-repaso/cmake/elementoFinito/`) que junta los tres temas
bloqueantes marcados como no-negociables en el CLAUDE.md de Nicolás:

- **Excepciones**: `Matriz<T>::operator+/-/*` y `operator()` lanzan `std::invalid_argument` /
  `std::out_of_range` en vez de fallar en silencio (antes hacían `return *this;`, un bug real que
  se usó como caso motivador).
- **Separación .hpp/.cpp**: practicado desde cero con la jerarquía `ElementoFinito` (base
  abstracta, puro virtual `matrizLocal()` y `area()`, destructor virtual) →
  `ElementoTriangular`/`ElementoCuadrilatero`. Regla fijada: un header por clase, mismo nombre que
  la clase; `Matriz<T>` (template) va completa en el `.hpp`, sin `.cpp`, porque el compilador
  necesita el cuerpo completo en el punto de instanciación.
- **CMake + Catch2 v3 vía `FetchContent`**: `CMakeLists.txt` con dos targets (`elemento_finito` el
  ejecutable normal, `tests` con `Catch2::Catch2WithMain`, sin `main.cpp` propio). Compilado y
  verificado: **11 assertions, 5 test cases, todos en verde.**

Este proyecto (`codigo/cpp-repaso/cmake/elementoFinito/`) es la plantilla de referencia para
cualquier proyecto nuevo de acá en adelante: estructura `include/`+`src/`+`tests/`, CMake con
FetchContent de Catch2, tests desde el día uno.

**Pendiente, no bloqueante:** Tier 2 (row-major vs column-major, precisión de punto flotante,
Eigen, interop C++/Fortran), Tier 3 (lambdas, lldb, sanitizers, move semantics) y Tier 4
(constexpr, RAII para OpenGL) de `10-09-26/cpp-avanzado/repaso.html` — decisión explícita:
pausados hasta estar más metido en el curso de Estructuras de Datos, mismo criterio que OpenGL
(ver 2.3). Se retoman cuando el interop con Fortran o la visualización OpenGL vuelvan a ser el
foco activo.

### 2.3 Entorno OpenGL (armado y pausado)
`Documents/VSCODE/cpp/opengl/hello-window/` — GLFW (Homebrew) + GLAD2 (generado localmente con el
paquete Python `glad2`, sin dependencia web; el venv usado ya se borró, no hace falta en runtime).
Compila con `clang++ -std=c++17` + frameworks de macOS (`OpenGL`, `Cocoa`, `IOKit`, `CoreVideo`).
Verificado corriendo (ventana azul confirmada visualmente). Roadmap de 7 fases acordado (triángulo
→ transformaciones/GLM → texturas/luz → cámara → mapas de color por valor escalar para FEM → UI
ImGui) — **pausado** hasta avanzar en Estructuras de Datos, no depende de árboles/grafos pero sí
de C++ sólido.

## 3. Archivos movidos a esta carpeta

Todo el código del repaso de C++ vive ahora en `codigo/cpp-repaso/` (antes en
`Documents/VSCODE/cpp/papa_conceptos/preparacion-papa/`, se copió sin las carpetas `build/`
generadas — esas se regeneran solas con `cmake ..`):

```
codigo/
├── cpp-repaso/
│   ├── repaso_bases/        <- Fases 0-8 (repaso1.cpp, clases1rep.cpp, sobrecargaOp.cpp,
│   │                            templatesRepaso.cpp, herenciaRep.cpp, polimorfismosRep.cpp,
│   │                            smartPointersRep.cpp, reto1.cpp = capstone)
│   ├── excepciones/excp1.cpp
│   └── cmake/
│       ├── proyecto1/        <- primer ejercicio de separación .hpp/.cpp (Vector2D)
│       └── elementoFinito/   <- proyecto de referencia: CMake+Catch2 completo (ver 2.2)
└── estructuras/
    └── memoria/              <- YA EXISTÍA, empezado antes de esta sesión (ver sección 4)
```

Nota: `smartPointersRep.cpp` y `templatesRepaso.cpp` tienen partes sin terminar/sin probar
(faltaba `#include <vector>` en el segundo, y no se verificó `Matriz<int>` ni `operator-`/`*`) —
no son bloqueantes, quedaron ahí desde el repaso original.

## 4. Fase 1 de Estructuras de Datos — CERRADA (2026-09-15 a 2026-09-22)

Se completó a fondo, con mucha iteración (varias rondas de confusión real y corrección, no un
camino lineal) — el detalle completo vive en la conversación, acá el resumen operativo:

- **1.1-1.9 de `10-09-26/ruta_codigo/1-estructuras-de-datos.html`**: memoria/punteros/referencias,
  arrays estáticos/dinámicos, Big-O (ya visto en su carrera, repaso corto), structs/clases, listas
  enlazadas (manual con `NodoLista*` — insertar al frente/final, buscar, liberar — y con
  `std::list`), pilas/colas (manual con `NodoLista*` — `push`/`pop`/`top`/`front`/`back` — y con
  `std::stack`/`std::queue`), y **1.9 Tablas hash (`std::unordered_map`) — tema nuevo, agregado
  esta sesión**, no estaba en el roadmap original. Motivo: ya estaba citado como requisito real en
  el tema 2.1 de `ruta-fem` ("resolver una referencia de entidad siempre O(1) por hash") pero
  nunca se había armado el tema. `ruta_codigo/progreso.js` y `0-indice.html` actualizados (total
  38 temas, 5 fases — de paso se descubrió que ya existía `5-opengl-avanzado.html`, completo, sin
  linkear desde el índice; ya está linkeado).
- **Búsqueda y Ordenamiento (1.7/1.8) — pendientes de práctica real**, aunque `buscar()` ya se
  practicó de facto varias veces (es búsqueda lineal) tanto a mano como con `std::find`.
- **Benchmarks reales corridos y guardados en el HTML** como evidencia, no solo afirmación: vector
  vs lista insertando al frente (144ms vs 1ms), vector vs cola sacando del frente (147ms vs 0ms),
  búsqueda lineal vs hash (214ms vs 0ms), `std::sort` fallando en compilación sobre `std::list`.

### 4.1 Proyecto integrador de cierre de Fase 1

`codigo/estructuras/integradores/fase1_1/` — junta TODO lo de Fase 1 en un sistema chico pero
honesto, no ejercicios sueltos:

```
fase1_1/
├── codigoLargo.cpp        <- version original de un solo archivo, superada, se puede borrar
├── CMakeLists.txt         <- Catch2 v3 via FetchContent, mismo patron que elementoFinito
├── include/                (Nodo, RegistroCalculo, Matriz<T>, ElementoFinito, ElementoTriangular,
│                             ElementoCuadrilatero, ElementoBarra, Malla)
├── src/                    (implementaciones .cpp + main.cpp)
└── tests/test_elemento_barra.cpp   <- 3 test cases, 6 assertions, todos en verde
```

**Qué hace `Malla`** (la pieza nueva, el centro del ejercicio): dueña de `vector<Nodo*>` (todos los
nodos), `unordered_map<int,Nodo*>` (ID externo → nodo, resuelve por hash — el caso real de IFC),
`queue<ElementoBarra*>` (procesamiento en orden de llegada). Destructor libera todo sin fugas
(verificado con `-fsanitize=address`, cero leaks, cero double-free). API pública: `agregarNodo`,
`agregarBarra` (recibe IDs, resuelve nodos por hash internamente — no rompe encapsulación),
`procesarCola`. Compilado y corrido con CMake real: ejecutable + tests, ambos en verde.

**Bugs reales que aparecieron y se corrigieron en el camino** (vale la pena conocerlos si algo
similar reaparece): `area()` puro virtual sin `override` (clase abstracta, no compila),
`const` en un método que en realidad muta estado (rompe al agregar un `push` a una pila interna),
parámetro `e` ignorado y reemplazado por un literal `2` a mano, double-free por guardar el mismo
puntero en dos contenedores y liberarlo dos veces, loop infinito por `delete` sin `pop()` en una
cola.

## 5. Decisiones tomadas sobre cómo seguir

- **Estructuras de Datos arranca ya**, con los ejemplos aplicados a análisis estructural/matricial/
  métodos numéricos en vez de un dominio genérico — cambio deliberado de tema respecto a un
  roadmap anterior (13 fases, hilo conductor "flota de robots", registrado en memoria de la otra
  carpeta) que queda obsoleto para este track: acá el hilo conductor es nodos, mallas, matrices de
  rigidez, vectores de fuerza.
- Los `struct Nodo`/`Matriz<T>` ya escritos son la base — no hace falta reinventar desde cero,
  construir sobre `codigo/estructuras/integradores/fase1_1/` (la versión organizada, no
  `codigo/estructuras/memoria/` ni `codigo/estructuras/structs/`, que son intentos previos
  superados) y `codigo/cpp-repaso/cmake/elementoFinito/`.
- Tier 2-4 de `cpp-avanzado` y el roadmap de OpenGL quedan pausados (secciones 2.2/2.3) hasta que
  el curso avance lo suficiente — no sostener 4 frentes profundos a la vez.
- **Proyecto de grado**: "análisis por elementos finitos con interfaz gráfica" — dominio físico
  todavía abierto entre análisis estructural y transferencia de calor, no decidido. La maquinaria
  de código (ensamblar una matriz, resolver `Ku=F`, condiciones de frontera) es casi idéntica entre
  los dos dominios — no hace falta que decida para seguir avanzando en estructuras de datos y el
  motor de cálculo. El requisito de GUI conecta con el entorno OpenGL ya armado (sección 2.3).
- **Pidió explícitamente (2026-09-21) que se le recuerde el roadmap proactivamente** en cada
  transición de fase — no asumir que tiene el mapa completo en la cabeza.

## 6. Cómo escribir código en este track (estilo de enseñanza acordado)

- **Explicación siempre en el chat, nunca en archivos de teoría** — las carpetas de código llevan
  solo ejercicios, nunca un `.md` explicando un concepto (este archivo es la única excepción,
  porque es continuidad de sesión, no teoría).
- **Aprende mejor intentando primero.** Dar pistas progresivas en ejercicios, no la solución
  completa de entrada — solo desglosar paso a paso si de verdad se atasca.
- **Nada se da por "listo" sin compilar y correr.** Verificación real con el compilador delante
  (mostrar el error exacto, no solo describirlo) antes de seguir. Con Catch2 ya integrado, para
  código nuevo esto significa: escribir el test primero o junto con el código, no después "cuando
  haya tiempo".
- **Modo Cirujano para bugs**: una hipótesis por turno, evidencia del compilador, causa raíz no
  parche cosmético.
- **Todo proyecto nuevo lleva `CMakeLists.txt` + Catch2 v3 vía FetchContent desde el día uno** —
  no volver a `.cpp` sueltos compilados a mano salvo para experimentos muy chicos de un solo
  archivo.
- Reglas de estilo C++ ya vigentes: PascalCase clases, camelCase variables/métodos, datos siempre
  `private`, listas de inicialización en todos los constructores, `const` en métodos no-mutantes,
  un header por clase con el mismo nombre que la clase, templates completos en el `.hpp`.
- Puntos débiles conocidos a vigilar (ya se repitieron en este repaso): `virtual` vs herencia
  virtual, destructor virtual en bases polimórficas, elegir bien `T`/`T&`/`const T&`/`T*`/
  `unique_ptr<T>` como tipo de parámetro, off-by-one en bounds-checking (`>` vs `>=`).

## 7. Próximo paso concreto (actualizado 2026-09-25)

Fase 1 de Estructuras de Datos está cerrada en lo esencial (ver sección 4). 1.7 (búsqueda
lineal/binaria) se practicó a fondo (2026-09-22/23): lineal y binaria iterativas verificadas con
casos borde reales, benchmark real 1M elementos (lineal 2809ms vs binaria 4ms, mismo checksum —
evidencia de correctitud y de velocidad a la vez), aplicado a dominio (`buscarNodoPorCoordenadas`
lineal, con la trampa de comparar `double` con `==` ya discutida). 1.8 (ordenamiento) se cubrió
en teoría a fondo (inserción, mergesort explicado con traza completa a mano, familia `O(n log n)`,
nota de DELOS-3D/heapsort) pero el código de `mergesort` quedó con un bug real de recursión infinita
sin corregir (`codigo/estructuras/ordenamiento/ordenar.cpp` — caso base compara `v.size()` en vez
del rango `inicio`/`fin`, y la primera llamada recursiva no achica el rango) — **pendiente, no
bloqueante**, él decidió dejarlo así y seguir. `gdlRestringidos` (aplicado de binaria a condiciones
de frontera) también quedó pendiente con la firma correcta (`vector<int>` + `busquedaBinaria`, no
por coordenadas) — ver sección 4.1 de más abajo. A3 (binaria recursiva) se saltó por decisión propia.

Roadmap que sigue, y que hay que recordarle proactivamente en cada transición (ver sección 5):

1. **Fase 2 — Árboles y grafos** (`10-09-26/ruta_codigo/2-arboles-grafos.html`): BST, AVL, heaps,
   grafos, Dijkstra, Union-Find. Acá vuelve DFS/BFS — ya se le presentó el concepto una vez
   (2026-09-21) demasiado pronto, sin la base de grafos armada todavía, y se frenó a tiempo
   ("sigo sin entender un carajo") — cuando se retome, construir la base de grafos ANTES de mezclar
   con pila/cola, no al revés.
2. **Motor de cálculo real**: ensamblaje de matrices locales en una matriz global, condiciones de
   frontera, resolver `Ku=F` — Fase 3 de `ruta_codigo` (métodos numéricos en código: Gauss/LU).
3. **Fase 4 (Gráficos) — AJUSTE DE PLAN (2026-09-25):** ya NO espera a que Fase 3 cierre del todo.
   Decisión tomada con él (modo Arquitecto): dibujar/rotar un vector simple y ver ejes en pantalla
   NO necesita el motor de cálculo resuelto — solo Fase 5.6 (color por valor escalar, visualización
   de RESULTADOS de FEM) sí lo necesita. Fase 4 puede arrancar en paralelo con Fase 2/3, motivado por
   su propio interés en replicar lo que hacía su papá con IFC (cargar figuras, rotar, sin duplicar
   nodos — eso es Fase 5.5 "EBO: mallas sin vértices duplicados", la misma técnica de hashing
   espacial de `buscarNodoPorCoordenadas`/1.9 aplicada a vértices de GPU). Fase 5 completa
   (EBO, picking, ImGui) sigue esperando a tener datos de malla reales de Fase 3.
4. **Maestría/tesis (nuevo, 2026-09-25):** interés genuino y creciente en termo/motores/transferencia
   de calor (ver [[intereses_termo_aero]] en la memoria) — se le dieron pistas de programas
   (Von Karman Institute, Cranfield Thermal Power, CFD como puente directo software↔termo) y se
   reforzó que esto es un argumento real a favor de "transferencia de calor" como dominio del
   proyecto de grado (ver sección 5, dominio todavía abierto). No es currícula de C++ inmediata.

## 8. `codigo/PROYECTO/` — el integrador real y creciente (arrancado 2026-09-25)

Reemplaza el criterio de "un integrador cerrado por fase" (como `fase1_1`, que queda como ejercicio
histórico, no se vuelve a tocar) por **un solo proyecto que crece con cada fase**, ensamblado a
medida que él avanza. Workflow acordado explícitamente con él: él escribe/valida la lógica nueva en
un archivo suelto (como ya venía haciendo — `vector1.cpp`, `busqLineal.cpp`), pregunta lo que necesite,
y **la integración al proyecto real (separar `.hpp`/`.cpp`, CMake, conectar con lo existente) la hace
Claude**, explicándole qué se movió y por qué en cada paso — a él "le da pereza" esa parte mecánica y
prefiere enfocar su tiempo en la lógica nueva, no en la fricción de ensamblar.

Estructura (verificada compilando con CMake real — `cmake --build build`, 27 assertions en verde):
```
PROYECTO/
├── CMakeLists.txt          <- mismo patrón que elementoFinito/fase1_1 (CMake+Catch2 FetchContent)
├── include/ + src/          <- Nodo, RegistroCalculo, Matriz<T>, ElementoFinito/Triangular/
│                                Cuadrilatero/Barra, Malla (copiados de fase1_1, sin tocar el
│                                original) + Punto2D/3D, Vector2D/3D (nuevos, ver abajo)
├── tests/                   <- test_elemento_barra.cpp (copiado) + test_vectores.cpp (nuevo,
│                                portea a Catch2 real las verificaciones que él ya hizo a mano)
├── graficos/                <- preview de OpenGL (adelanto de Fase 4, NO Fase 4 completa): dibuja
│                                el vector (3,4) + ejes en pantalla, reusa GLAD ya generado en
│                                Documents/VSCODE/cpp/opengl/hello-window/. build.sh con el comando
│                                de compilación (clang++ + GLFW de Homebrew + frameworks de macOS).
└── codigo-plano/             <- espejo de include/+src/ pero con cada grupo de clases en UN solo
                                 archivo (declaración+implementación juntas, sin separar hpp/cpp) —
                                 pedido explícito de él para leer más cómodo. vectores.cpp y
                                 elementos_malla.cpp, cada uno compilable suelto y verificado.
```

**Corrección de punto vs. vector aplicada** (él lo notó solo, ver conversación 2026-09-24/25):
`Punto2D`/`Punto3D` (solo posición, sin álgebra vectorial) separados de `Vector2D`/`Vector3D`
(magnitud/dirección, con toda el álgebra). Operadores libres `punto - punto = vector` y
`punto + vector = punto` — lo que en el archivo suelto iba a llamarse `desdePuntos` se volvió
directamente `operator-` entre dos `Punto2D`. `Nodo` (de `fase1_1`/FEM) se dejó separado de
`Punto3D` a propósito — mismo shape, pero no se fusionaron para no generar cambios en cascada sobre
`ElementoBarra`/`Malla` ya cerrados y probados.

**Próxima integración pendiente:** cuando él escriba `desdeMagnitudYAngulo` (la descomposición de
fuerza F·cos/F·sin que motivó todo esto) y `normalizado()`, se integran de la misma forma.
