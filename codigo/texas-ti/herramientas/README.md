# Programas TI-Nspire CX (Ndless), uno por materia

Tres programas independientes. Pasar a la calculadora el que se necesite y abrirlo (con Ndless activo).

| Archivo | Contenido |
|---|---|
| `metodos_numericos.tns` | Biseccion, Newton-Raphson, secante, Gauss con pivoteo, Gauss-Seidel, interpolacion (Lagrange y Newton), minimos cuadrados (grado 1 a 5), trapecio y Simpson, Runge-Kutta 4 |
| `termodinamica.tns` | Interpolacion lineal, propiedad desde calidad, calidad desde propiedad, saturado entre dos filas + calidad, doble interpolacion |
| `fluidos.tns` | Metodos de la clase (Clase 10): factor f (Haaland + Colebrook), tipo 1 (perdida hL), tipo 2 (caudal Q, tabla de iteracion), tipo 3 (D por Swamee-Jain y D iterando hasta hL), canal Manning (otro tema). Siempre muestra e/D, f Haaland, f Colebrook y el error entre ambas. Al abrir pide el sistema de unidades (SI o ingles) la opcion 1 calcula V, Re y e/D a partir de Q (o V) y D antes de sacar f, y las opciones 8 y 9 despejan D o Q de Darcy dado f |

Guia detallada de `fluidos.tns`: ver [GUIA_FLUIDOS.md](GUIA_FLUIDOS.md).

## Entrada de datos
- Todo numero acepta expresiones: `1e-6`, `0.046/100`, `2/3`, `pi`.
- Las funciones f(x) se escriben **sin espacios**: `x^3-x-2`, `sin(x)*exp(-x)`.
  Disponibles: `sin cos tan asin acos atan exp ln log sqrt abs pi e`, variables `x` e `y`.
- Fluidos: al abrir se elige SI (m, m3/s, m2/s, g = 9.81) o ingles (ft, ft3/s, ft2/s, g = 32.2). En ingles, 2 in se escribe 2/12 (ft).

## Desarrollo
Requiere el SDK de Ndless en el PATH.
- `make` compila los tres; `make fluidos.tns` compila solo uno
- `make test` corre las pruebas en la Mac (valores de referencia calculados aparte)
- `make host-numericos | host-termo | host-fluidos` corre un menu en la Mac

Estructura: `src/comun` (evaluador de expresiones y entrada de datos, compartido),
y un directorio por materia con sus algoritmos, su menu y su `main`.
