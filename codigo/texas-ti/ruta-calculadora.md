# Ruta de dominio: TI-Nspire CX (sin CAS) + TI-Basic

Objetivo: usar la calculadora al 100% **sin depender del PC**, y poder programar en TI-Basic en el momento
si un parcial lo pide. Lo que se hace con los `.tns` (C++) queda como complemento para tareas y estudio.

## Cómo usar esta ruta

- **Orden:** Parte A (funciones nativas) → Parte B (programación en TI-Basic) → Parte C (puente con C++ y simulacros).
  La Parte A va primero porque es lo que más te salva en un parcial: resuelve en segundos lo que programando tarda minutos.
- **Cada módulo trae:** objetivo, qué herramientas usar, **casos de práctica con clave de respuesta**, errores típicos y
  un criterio de "dominado".
- **Las claves de respuesta** las calculé aparte con Python (no con la calculadora). Si tu calculadora da algo distinto,
  anotá la diferencia: es justo lo que hay que entender (modo grados/radianes, estimado inicial, tolerancia...).
- **Sintaxis:** los nombres de funciones y menús están **escritos de memoria y no los probé en tu calculadora**.
  La fuente de verdad es el **Catálogo** (tecla del libro): si algo no existe con ese nombre, buscalo ahí. Eso también es práctica.
- **Tiempos** (≈ horas por módulo): son estimaciones mías, no medidas.
- **Regla de trabajo:** para cada caso, primero predecí el resultado a mano o con la clave, después calculalo, después compará.
- Los valores de tablas de vapor que aparecen abajo son **ilustrativos** (inventados para practicar), no de tablas oficiales.

---

# PARTE A. La calculadora nativa

## A1. Operación básica y orden de trabajo (≈ 1 h)

**Objetivo:** moverte con soltura y no perder trabajo.

**Aprender:** teclas `doc`, `menu`, `ctrl`, `var`, Catálogo (libro), `esc`; páginas y problemas dentro de un documento;
guardar (`ctrl`+`S`) y deshacer (`ctrl`+`Z`); variables (`5→a` o `a:=5`); `Ans`; historial; `Define f(x)=...`;
modo de ángulos (grados/radianes) y dígitos mostrados en la configuración del documento.

**Casos:**
1. `3.2E-3 * 4.5E5` → **1440**.
2. Guardá `a:=5`, `b:=7`; calculá `a*b` → **35**; luego usá `Ans`.
3. `Define f(x)=x^2+1` → `f(3)` = **10**, `f(a+b)` = **145**.
4. Con la calculadora en **radianes** `sin(90)` = **0.8939967**; en **grados** = **1**. Cambiá el modo y verificá.
5. Guardá un documento con 2 problemas, cerralo y volvelo a abrir.

**Errores típicos:** confundir `=` (compara) con `:=` (asigna); olvidar el modo de ángulos; usar un nombre de variable ya ocupado.
**Dominado cuando:** hacés los 5 casos sin mirar y sabés en qué modo está tu calculadora sin abrir la configuración.

## A2. Resolver ecuaciones (≈ 1.5 h)

**Objetivo:** hallar raíces numéricas sin programar.

**Herramientas:** `nSolve(ecuación, variable)`, con estimado (`x=1.5`) y con cotas (`... | 1<x<2`);
en el menú *Álgebra* mirá también *Resolver* y *Ceros* y comprobá cuáles existen en tu modelo no CAS.
Idea clave: `nSolve` te da **una** solución, la más cercana a tu estimado.

**Casos:**
1. `x^3-x-2=0`, estimado 1.5 → **1.5213797**.
2. `e^x=3x`: estimado 0 → **0.6190613**; estimado 2 → **1.5121346**. (Dos raíces, dependen del estimado.)
3. `cos(x)=x` en radianes → **0.7390851**.
4. Sistema `x^2+y^2=25`, `x-y=1`: soluciones **(4, 3)** y **(−3, −4)**. Probá si tu menú resuelve sistemas con `nSolve`
   o con *Resolver*, y qué estimado hace falta para llegar a cada una.
5. `x^2+1=0`: no tiene raíz real. Anotá cómo responde la calculadora.
6. **Colebrook como ecuación** (el de fluidos): `1/√f = −2·log(2e-4/3.7 + 2.51/(1e5·√f))`, estimado f=0.02 → **f = 0.019005435**.
   Cuidado: comprobá si `log` es base 10 con `log(100)` (debe dar 2).
7. Misma ecuación del caso 1 pero con cotas `| 1<x<2`: debe dar lo mismo.

**Errores típicos:** modo grados/radianes en el caso 3; estimado malo → la raíz equivocada o ningún resultado; olvidar `=`.
**Dominado cuando:** resolvés los casos 1 a 3 y 6 sin ayuda y explicás por qué el caso 2 da dos respuestas.

## A3. Derivadas e integrales numéricas (≈ 1 h)

**Herramientas:** `nDeriv(f(x),x)` evaluada en un punto con `| x=valor`; `nInt(f(x),x,a,b)`.

**Casos (derivadas):**
1. `sin(x)` en `x=π/3` → **0.5**.  2. `x^3` en `x=2` → **12**.  3. `ln(x)` en `x=5` → **0.2**.

**Casos (integrales):**
4. `∫ sin(x) de 0 a π` → **2**.  5. `∫ x² de 0 a 3` → **9**.  6. `∫ 1/x de 1 a e` → **1**.
7. `∫ √x de 0 a 4` → **5.3333333**.
8. `∫ e^(−x²) de 0 a 1` → **0.7468241** (no tiene primitiva elemental: acá lo numérico gana).
9. Definí `Define g(x)=e^(-x^2)` y calculá `nInt(g(x),x,0,1)`: debe dar lo mismo.
10. **Comparar con tu programa:** el `.tns` de métodos numéricos con Simpson n=10 sobre `sin(x)` da 2.0001095; ¿cuánto se desvía de `nInt`?

**Errores típicos:** derivar en un punto de quiebre (`abs(x)` en 0); integrar una función con singularidad (`1/x` de −1 a 1).
**Dominado cuando:** sabés cuándo confiar en una derivada numérica y cuándo no.

## A4. Matrices y sistemas lineales (≈ 2 h)

**Herramientas:** crear matrices (menú *Matriz y vector* o la plantilla), `simult(A,b)`, `rref(augment(A,b))`,
`det(A)`, `A^-1`, transpuesta, `identity(n)`, `eigVl`, `eigVc`, descomposición `LU`.

**Casos:** sea `A = [[2,1,-1],[-3,-1,2],[-2,1,2]]` y `b = [8,-11,-3]`.
1. `simult(A,b)` → **(2, 3, −1)**. Lo mismo con `A^-1 * b`.
2. `det(A)` = **−1**. `A^-1` = **[[4,3,−1],[−2,−2,1],[5,4,−1]]**.
3. **Singular:** `[[1,2],[2,4]]` → `det` = 0; la inversa da error. Anotá el mensaje.
4. **4×4:** `M = [[4,-1,0,1],[-1,4,-1,0],[0,-1,4,-1],[1,0,-1,4]]`, `b = [6,4,6,14]` → **(1, 2, 3, 4)**.
5. **Infinitas soluciones:** `rref([[1,1,2],[2,2,4]])` deja una fila de ceros. Interpretalo.
6. **Autovalores:** `[[2,1],[1,2]]` → **1 y 3**; `[[4,1],[2,3]]` → **2 y 5**.
7. **Mal condicionada:** la matriz de Hilbert 3×3 `[[1,1/2,1/3],[1/2,1/3,1/4],[1/3,1/4,1/5]]` tiene `det` = **0.00046296** (=1/2160). Resolvé con ella y mirá cuánto cambia el resultado si perturbás un dato.
8. Planteá con tus datos de **estática** las 3 ecuaciones de equilibrio de una viga con 3 reacciones y resolvelas con `simult`.

**Errores típicos:** dimensiones que no coinciden; confundir matriz columna con fila; interpretar un `det` casi cero.
**Dominado cuando:** resolvés un sistema 3×3 con `simult` en menos de 1 minuto y reconocés uno singular.

## A5. Listas, hoja de cálculo y estadística (≈ 2 h)

**Herramientas:** listas `{1,2,3}`; `seq(expr,var,ini,fin)`, `sum`, `cumSum`, `mean`, `stdDev`, `sortA`, `dim`;
aplicación *Listas y hoja de cálculo* (columnas con fórmula); regresiones `LinRegMx`, `QuadReg` (y las cúbica, exponencial, potencia).

**Casos:**
1. Datos (1;2.1) (2;3.9) (3;6.2) (4;7.8) (5;10.1) → `LinRegMx`: **m = 1.99, b = 0.05, r² ≈ 0.9973**.
2. Datos (0;1) (1;0) (2;1) (3;4) (4;9) → `QuadReg`: **y = x² − 2x + 1**, r² = 1.
3. `sum(seq(2k-1,k,1,50))` → **2500**.
4. **Iterar a mano con `Ans`:** guardá `1→x` y repetí `(x+2/x)/2→x`: **1.5, 1.4166667, 1.4142157, 1.4142136** (√2).
5. **Newton en la hoja:** columna A con `x₀=1.5` y columna siguiente `=a[1]-(a[1]^3-a[1]-2)/(3*a[1]^2-1)` hacia abajo
   (adaptá la sintaxis de referencia a celdas): **1.5217391, 1.5213798, 1.5213797**.
6. **Interpolación de tabla:** con los puntos ilustrativos (10;100) y (20;300), el valor en x=12 es **140**.
   Armalo con una fórmula en la hoja y con la regresión lineal de 2 puntos; compará.
7. Estadística descriptiva de la lista `{4,8,15,16,23,42}`: comprobá `mean` = **18**.

**Errores típicos:** listas de distinto tamaño; olvidar que la regresión guarda resultados en variables `stat.`; tomar r² como garantía.
**Dominado cuando:** ajustás datos y armás una iteración en la hoja sin ayuda.

## A6. Unidades y conversiones (≈ 1 h)

**Herramientas:** unidades con guion bajo (`_m`, `_s`, `_psi`...), conversión con `@>`, y `tmpCnv` para temperaturas.

**Casos:**
1. `60_mph @> _km/_hr` → **96.56064**.
2. `100_psi @> _kPa` → **689.4757**.
3. `1_gal/_min @> _l/_s` → **0.0630902**.
4. `1_hp @> _W` → **745.69987** (caballo mecánico; comprobá cuál usa tu calculadora).
5. `tmpCnv(72_°F,_°C)` → **22.2222** (las temperaturas no se convierten igual que las demás unidades).
6. **Número de Reynolds con unidades:** `(1.5915494_m/_s * 0.2_m)/(1.004E-6_m^2/_s)` → **317041.7**, adimensional.
7. **Detectar un error dimensional:** sumá `2_m + 3_s` y mirá el mensaje.

**Dominado cuando:** convertís entre sistemas sin copiar factores de memoria y usás las unidades para cazar errores en fluidos y termodinámica.

## A7. Gráficas y análisis (≈ 1.5 h)

**Herramientas:** aplicación *Gráficas*; ventana; menú *Analizar gráfica* (Cero, Mínimo, Máximo, Intersección, Integral, derivada en un punto); tabla de valores; deslizadores.

**Casos:**
1. `y=x²` y `y=2x+3` → intersecciones en **x = 3** y **x = −1**.
2. Mínimo de `x²−4x+1` → **(2, −3)**.
3. Cero de `x³−x−2` → **1.5213797**.
4. Área bajo `sin(x)` de 0 a π → **2**.
5. Función por tramos con la plantilla (o `when`): graficala y evaluala en el quiebre.
6. Un deslizador que mueva un parámetro `a` en `y=a·x²`: observá cómo cambia el vértice.
7. **Residuo de Colebrook:** graficá `1/√f + 2·log(...)` (con Re=1e5, e/D=2e-4) contra f y hallá el cero (≈ 0.019005).

**Dominado cuando:** usás la gráfica para elegir un buen estimado inicial antes de `nSolve`.

## A8. Bases numéricas, lógica, complejos y polinomios (≈ 1 h)

**Herramientas:** `@>Base2`, `@>Base16`, prefijos `0b` y `0h`, operaciones bit a bit (`and`, `or`, `xor`), `polyRoots`, números complejos.

**Casos:**
1. `255` a hexadecimal → **FF**; a binario → **11111111**.
2. `0b1100 and 0b1010` → **0b1000** (8); `or` → **14**; `xor` → **6**.
3. `(1+2i)(3−i)` → **5+5i**; `√(−4)` → **2i** (puede depender del modo Real/Complejo).
4. `polyRoots(x^3-6x^2+11x-6, x)` → **1, 2, 3**.
5. Pasá a decimal `0h1F` → **31**.

**Dominado cuando:** cambiás de base y evaluás una operación lógica sin pensar en el menú.

---

# PARTE B. Programar en TI-Basic

**Dónde se escribe:** *Calculadora → Menú → Funciones y programas → Editor de programas → Nuevo*. Un programa se
define con `Define nombre(args)=Prgm ... EndPrgm`; una función con `Define nombre(args)=Func ... EndFunc`.
Se ejecuta escribiendo `nombre()` en la Calculadora.

## B1. Primer programa: entrada y salida (≈ 1 h)

**Herramientas:** `Local`, `Request "texto",variable`, `Disp`, asignación `:=`.

```
Define doble()=
Prgm
  Local n
  Request "Tu numero",n
  Disp "El doble es ",2*n
EndPrgm
```
(De memoria, sin probar. Si da error de sintaxis, corregirlo en la calculadora es parte del ejercicio.)

**Casos:**
1. Programa que pida un número y muestre el doble. Con 7 → **14**.
2. Área de un círculo con radio dado: r=3 → **28.274334**.
3. °C a °F: 100 → **212**; 37 → **98.6**.
4. Pedí dos números y mostrá suma, producto y cociente. Con 8 y 2 → **10, 16, 4**.
5. Probá el programa **sin** `Local` y comprobá que deja variables sueltas en tu documento.

**Errores típicos:** olvidar `EndPrgm`; usar `=` en vez de `:=`.
**Dominado cuando:** escribís el caso 4 en menos de 3 minutos.

## B2. Condicionales (≈ 1 h)

**Herramientas:** `If ... Then ... ElseIf ... Else ... EndIf`; `and`, `or`, `not`; comparaciones `=`, `≠`, `≤`, `≥` (los símbolos salen de un menú).

**Casos:**
1. **Régimen de flujo** con límites 2300 y 4000: Re=1500 → laminar; 3000 → transición; 100000 → turbulento. Probá exactamente 2300 y 4000 y decidí qué criterio querés.
2. **Raíces de `ax²+bx+c`:** `1,−5,6` → **2 y 3**; `1,2,1` → **−1 doble**; `1,0,1` → **complejas**; `0,2,−4` → no es cuadrática (x=2).
3. **Año bisiesto:** 2024 → sí; 1900 → no; 2000 → sí.
4. Signo de un número y valor absoluto sin usar `abs`.

**Dominado cuando:** el caso 2 cubre los 4 subcasos sin que se rompa.

## B3. Bucles (≈ 1.5 h)

**Herramientas:** `For i,ini,fin[,paso] ... EndFor`, `While ... EndWhile`, `Loop ... EndLoop` con `Exit`.

**Casos y claves:**
1. Suma de 1 a 100 → **5050**.   2. `10!` → **3628800**.
3. Fibonacci: el término 20 → **6765**.   4. `mcd(48,18)` por Euclides con `While` → **6**.
5. Cantidad de primos menores que 50 → **15**.   6. Suma de impares hasta 99 → **2500**.
7. **Collatz** desde 27 → **111 pasos**.
8. **Heron para √2** hasta que el cambio sea menor que 1e-10 → **1.4142136** (en 5 pasos).
9. Tabla de cuadrados de 1 a 10 con `For i,10,1,-1` (paso negativo).

**Errores típicos:** bucle infinito (se corta manteniendo la tecla `on`); error de un paso en el límite.
**Dominado cuando:** los casos 4 y 8 salen sin ayuda y sabés cortar un bucle colgado.

## B4. Funciones y recursión (≈ 1 h)

**Herramientas:** `Func ... Return ... EndFunc`; funciones de una línea con `when(cond,a,b)`.
Dentro de una función, en general no se permite `Disp` ni modificar variables globales: confirmalo en la guía.

**Casos:**
1. `Define cuadrado(x)=x^2` y `cuadrado(7)` → **49**.
2. **Factorial recursivo:** `fact(n)=when(n≤1,1,n*fact(n-1))`; `fact(10)` → **3628800**.
3. **Haaland como función:** `haaland(Re,eD)`; con `Re=1e5`, `eD=2e-4` → **0.018735458**.
   Fórmula: `1/√f = −1.8·log((eD/3.7)^1.11 + 6.9/Re)`.
4. Una función que reciba una lista: `promedio(L)=sum(L)/dim(L)`; con `{4,8,15,16,23,42}` → **18**.
5. Diferencia entre llamar a un programa (`doble()`) y una función (`cuadrado(7)`); cuándo conviene cada uno.

**Dominado cuando:** el caso 3 queda reutilizable desde un programa más grande.

## B5. Listas y matrices dentro de programas (≈ 2 h)

**Herramientas:** índice desde **1**; `dim`, `newList(n)`, `newMat(f,c)`, `m[i,j]`, `L[i]:=valor`.

**Casos:**
1. Máximo de una lista y su posición: `{3,9,2,9,5}` → máximo **9** en la posición **2** (primera aparición).
2. **Ordenar por burbuja** `{5,2,9,1}` → **{1,2,5,9}**. (Es el mismo algoritmo de tu curso de estructuras.)
3. Media y desviación estándar de una lista, comparando con `mean` y `stdDev`.
4. **Gauss sin pivoteo** en 3×3 con el sistema de A4 → **(2, 3, −1)**.
5. **Gauss con pivoteo:** `[[0,1],[1,0]]`, `b=[3,5]` → **(5, 3)**. Sin pivoteo falla; reproducí el fallo.
6. **Lagrange:** puntos (0,0) (1,1) (2,4) (3,9), evaluado en 2.5 → **6.25**.

**Errores típicos:** índice 0 en vez de 1; modificar una lista sin haberla creado con `newList`.
**Dominado cuando:** el caso 5 funciona y entendés por qué el caso 4 sin pivoteo no basta.

## B6. Métodos numéricos en TI-Basic (≈ 3 h)

Definí primero `Define f(x)=x^3-x-2` y que tus programas lo llamen.

**Casos y claves:**
1. **Bisección** en [1, 2] con tolerancia 1e-4 → **1.5214233** en **14** iteraciones. (Con 1e-10 el resultado se acerca a 1.5213797.)
2. **Newton** desde 1.5 (derivada numérica o dada) → **1.5213797** en **4** iteraciones con tolerancia 1e-10.
3. **Secante** con x₀=1, x₁=2, tolerancia 1e-10 → **1.5213797** en **8** iteraciones.
4. **Punto fijo** de `x = cos(x)` → **0.7390851**.
5. **Simpson** de `sin(x)` de 0 a π con n=10 → **2.0001095**; **trapecio** → **1.9835235**.
6. **Runge-Kutta 4:** `y' = x + y`, `y(0)=1`, hasta x=1 con 20 pasos → **3.4365634** (exacto: 3.4365637).
7. **Colebrook completo:** semilla de Haaland y punto fijo hasta que el cambio sea menor que 1e-8.
   | Re | e/D | f₀ (Haaland) | f (Colebrook) | iteraciones |
   |---|---|---|---|---|
   | 100000 | 0.0002 | 0.018735458 | **0.019005435** | 6 |
   | 50000 | 0.00046 | 0.022128880 | **0.022440170** | 6 |
   | 250000 | 0.002857143 | 0.026360770 | **0.026373690** | 3 |
   | 1000000 | 0.002 | 0.023630030 | **0.023606990** | 3 |
8. Casos de falla: bisección en [2, 3] (sin cambio de signo); Newton en `x²+1` (derivada cero); Colebrook con Re=1000 (laminar, f=64/Re=**0.064**).

**Dominado cuando:** escribís bisección y Colebrook desde cero en menos de 15 minutos cada uno, con los casos de falla controlados.

## B7. Aplicaciones de tu carrera (≈ 3 h)

**Termodinámica** (valores ilustrativos):
1. Interpolación lineal entre (10;100) y (20;300) en x=12 → **140**.
2. Mezcla: `f=191.81`, `g=2584.6`, `x=0.5` → `h = f + x(g−f)` = **1388.205**; la calidad inversa devuelve **0.5**.
3. **Dos filas + calidad:** T=45 entre la fila T=40 (f=167.53, g=2574.3) y T=50 (f=209.34, g=2592.1);
   interpolá f y g → **f=188.435, g=2583.2**; con x=0.3 → **h = 906.8645**.
4. **Doble interpolación** con `x₁=0, x₂=2, y₁=0, y₂=4` y valores de la tabla `0, 2, 4, 6` (que corresponden a `x+y`), en (1,1) → **2**.

**Fluidos:**
5. **Pérdida en tubería:** Q=0.05 m³/s, D=0.2 m, L=100 m, ε=0.00026 m, ν=1.004e-6 → **Re=317041.7, f=0.021722373, v=1.5915494 m/s, hf=1.4022277 m**.
6. **Q a partir de hf:** con hf=1.4022277 y los mismos datos, el programa debe recuperar **Q=0.05** (iteración sobre f).
7. **D a partir de Q y hf:** debe recuperar **D=0.2** (bisección sobre D).
8. **Caso laminar:** Q=0.0005, D=0.1, L=50, ε=0.0001, ν=1e-4 → **Re=63.66, f=64/Re=1.0053096, hf=0.1038320**.
9. **Manning rectangular:** b=2, n=0.013, S=0.001, Q=3.0647848 → **y=1, v=1.5323924, Fr=0.4892552** (subcrítico).
10. **Manning trapecial:** b=3, z=1.5, n=0.015, S=0.0008, Q=9.2516768 → **y=1.2, v=1.6061939, Fr=0.5489391**.

**Dominado cuando:** resolvés un problema tipo parcial de cada área (interpolación + calidad, y tubería) con tu propio programa, y verificás con la clave.

## B8. Depuración, robustez y estilo (≈ 2 h)

**Herramientas:** `Try ... Else ... EndTry`, `Disp` de depuración, validación de entradas.

**Casos:**
1. Validá que `Re>0` y `D>0` antes de calcular y mostrá un mensaje claro si no.
2. Capturá una división por cero con `Try`.
3. **Rompé tus programas a propósito de 3 formas** (falta un `EndFor`, índice fuera de rango, `=` en vez de `:=`) y anotá el mensaje de error de cada una y cómo se arregla.
4. Mostrá siempre el número de iteraciones y la tolerancia usada.
5. Nombres claros y un comentario de una línea al inicio con las unidades de cada argumento.

**Dominado cuando:** ante un error tardás menos de 2 minutos en ubicarlo.

---

# PARTE C. Puente con C++ y simulacros

## C1. Traducción C++ → TI-Basic

| C++ | TI-Basic |
|---|---|
| `double x = 5;` | `x:=5` (y `Local x` en programas) |
| `if / else if / else` | `If ... Then / ElseIf ... Then / Else / EndIf` |
| `for (i=1; i<=n; i++)` | `For i,1,n ... EndFor` |
| `while (c) { }` | `While c ... EndWhile` |
| `cin >> x;` | `Request "x",x` |
| `cout << x;` | `Disp x` |
| `double f(double x) { return ...; }` | `Define f(x)=Func ... Return ... EndFunc` |
| `a[0]` | `a[1]` (los índices empiezan en 1) |
| `fabs`, `sqrt`, `pow` | `abs(`, `√(`, `^` |
| `log10(x)` | `log(x)` (comprobar con `log(100)=2`) |
| `a % b` | `mod(a,b)` |
| `&&`, `\|\|`, `!` | `and`, `or`, `not` |

## C2. Simulacros cronometrados

Reglas: sin PC, sin mirar la clave hasta terminar, y **resolvé primero con la función nativa** para saber la respuesta esperada.

| # | Reto | Tiempo objetivo | Caso de verificación |
|---|---|---|---|
| 1 | Bisección para `x^3-x-2` | 10 min | 1.5214233 (tol 1e-4) |
| 2 | Colebrook con semilla de Haaland | 15 min | Re=1e5, e/D=2e-4 → 0.019005435 |
| 3 | Interpolación lineal + calidad | 10 min | T=45, x=0.3 → 906.8645 |
| 4 | Gauss 3×3 con pivoteo | 20 min | (2, 3, −1) |
| 5 | Simpson para `sin(x)` | 15 min | 2.0001095 (n=10) |

**Regla de decisión en un parcial:** si la función nativa lo resuelve (`nSolve`, `simult`, regresión), usala. Programá solo lo que
es **repetitivo** o lo que te piden explícitamente.

## C3. Registro de progreso

Marcá cada módulo cuando lo hayas "dominado" según su criterio.

- [ ] A1  - [ ] A2  - [ ] A3  - [ ] A4  - [ ] A5  - [ ] A6  - [ ] A7  - [ ] A8
- [ ] B1  - [ ] B2  - [ ] B3  - [ ] B4  - [ ] B5  - [ ] B6  - [ ] B7  - [ ] B8
- [ ] C2: retos 1 a 5 dentro del tiempo

**Antes de contar con esta ruta para un parcial:** preguntale al profesor si se permiten programas en la calculadora y qué modelo exige (CAS o no CAS).
