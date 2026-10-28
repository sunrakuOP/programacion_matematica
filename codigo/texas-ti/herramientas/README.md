# Programas TI-Nspire CX (Ndless), uno por materia

Tres programas independientes. Pasar a la calculadora el que se necesite y abrirlo (con Ndless activo).

| Archivo | Contenido |
|---|---|
| `metodos_numericos.tns` | Biseccion, Newton-Raphson, secante, Gauss con pivoteo, Gauss-Seidel, interpolacion (Lagrange y Newton), minimos cuadrados (grado 1 a 5), trapecio y Simpson, Runge-Kutta 4 |
| `termodinamica.tns` | Interpolacion lineal, propiedad desde calidad, calidad desde propiedad, saturado entre dos filas + calidad, doble interpolacion |
| `fluidos.tns` | Factor f (Haaland + Colebrook), perdida hf, caudal Q, diametro D (tuberias), canal Manning |

## Entrada de datos
- Todo numero acepta expresiones: `1e-6`, `0.046/100`, `2/3`, `pi`.
- Las funciones f(x) se escriben **sin espacios**: `x^3-x-2`, `sin(x)*exp(-x)`.
  Disponibles: `sin cos tan asin acos atan exp ln log sqrt abs pi e`, variables `x` e `y`.
- Fluidos en SI: m, m3/s, m2/s (nu del agua a 20 C = 1.004e-6).

## Desarrollo
Requiere el SDK de Ndless en el PATH.
- `make` compila los tres; `make fluidos.tns` compila solo uno
- `make test` corre las pruebas en la Mac (valores de referencia calculados aparte)
- `make host-numericos | host-termo | host-fluidos` corre un menu en la Mac

Estructura: `src/comun` (evaluador de expresiones y entrada de datos, compartido),
y un directorio por materia con sus algoritmos, su menu y su `main`.
