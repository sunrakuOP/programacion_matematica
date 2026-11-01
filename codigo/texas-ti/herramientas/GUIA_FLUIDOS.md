# Guía de `fluidos.tns` (Mecánica de Fluidos, flujo turbulento en tuberías)

Para qué sirve este documento: entender en el futuro **qué hace cada opción del programa, con qué
fórmulas y por qué se itera lo que se itera**. Está basado en la *Clase 10* (diapositivas 3 a 34) y en
el procedimiento que mostró el profesor para el Ejemplo 8-4.

> El programa está en `fluidos.tns` (esta misma carpeta). El código fuente está en `src/fluidos/`.
> Se abre en la calculadora **después de abrir el instalador de Ndless** (y cerrarlo con Ctrl+W).

---

## 1. Antes de empezar

### Sistema de unidades
Al abrir pregunta `1. Internacional` o `2. Inglés`. Todo el programa trabaja en ese sistema.

| | Internacional (SI) | Inglés |
|---|---|---|
| Longitud (L, D, e, hL) | m | ft |
| Caudal Q | m³/s | ft³/s |
| Viscosidad cinemática ν | m²/s | ft²/s |
| Viscosidad dinámica μ | Pa·s | lbm/(ft·s) |
| Densidad ρ | kg/m³ | lbm/ft³ |
| g | 9.81 | 32.2 |
| ΔP | Pa | lbf/ft² (y psi) |
| Potencia | W | W |

- En inglés, **2 in se escribe `2/12`** (ft). El programa acepta expresiones: `2/12`, `1.5e-6`, `0.0015/1000`.
- Se puede cambiar de sistema en cualquier momento con la **opción 7**.

### Viscosidad
Cuando el programa pide `nu, o 0 para dar mu y rho`:
- Si tenés **ν** (cinemática): escribila.
- Si tenés **μ** (dinámica) y **ρ**: escribí `0`, y después μ y ρ. El programa calcula `ν = μ/ρ`
  (es lo mismo que `Re = ρVD/μ`). Si das μ y ρ, además te entrega **ΔP** y la **potencia**.

### Rugosidad ε
`e (0 si liso)`. Va en la **misma unidad que D**. Se saca de la tabla de rugosidades (diapositivas 6 y 17).
- **Ojo con el acero inoxidable:** la tabla dice `0,000007 ft` y `0,02 mm`, pero 0.000007 ft son
  **0.0021 mm**. La columna en mm parece un error de tipeo. Usá el valor en **ft**.
- El programa muestra siempre **e/D**.

---

## 2. Las fórmulas (todas de la clase)

| Qué | Fórmula | Diapositiva |
|---|---|---|
| Velocidad | `V = Q / (πD²/4)` | 16, 24, 30 |
| Reynolds | `Re = V·D/ν = ρ·V·D/μ` | 16, 24 |
| Régimen | Re ≤ 2300 laminar · 2300–4000 transición · ≥ 4000 turbulento | 3 |
| Laminar | `f = 64/Re` | 7, 10 |
| **Colebrook** (implícita en f) | `1/√f = −2.0·log( ε/D/3.7 + 2.51/(Re·√f) )` | 5, 18, 24 |
| **Haaland** (explícita) | `1/√f ≅ −1.8·log[ 6.9/Re + (ε/D/3.7)^1.11 ]` | 8, 20, 33 |
| Darcy (pérdida en metros) | `hL = f·(L/D)·V²/(2g)` | 19, 24, 30 |
| Darcy (en presión) | `ΔP = f·(L/D)·ρ·V²/2` y `hL = ΔP/(ρg)` | 4, 19 |
| Potencia | `W = Q·ΔP` | 19 |
| Swamee-Jain, hL | `1.07·(Q²L/(gD⁵))·{ln[ε/(3.7D) + 4.62(νD/Q)^0.9]}^-2` | 13, 20 |
| Swamee-Jain, Q | `−0.965·(gD⁵hL/L)^0.5·ln[ε/(3.7D) + (3.17ν²L/(gD³hL))^0.5]` | 13, 32 |
| Swamee-Jain, D | `0.66·[ε^1.25·(L·Q²/(g·hL))^4.75 + ν·Q^9.4·(L/(g·hL))^5.2]^0.04` | 13, 25 |

Swamee-Jain declara validez para `10⁻⁶ < ε/D < 10⁻²` y un Re mínimo (3000 para hL, 2000 para Q,
5000 para D). Es una **aproximación**: "precisa a menos de 2 % del diagrama de Moody" (diapositiva 13).
El programa avisa si te salís de rango.

### Lo que NO está escrito en las diapositivas (es álgebra a partir de ellas)
Despejar D de Darcy. Se reemplaza `V = 4Q/(πD²)` en `hL = f(L/D)V²/2g`:

```
hL = 8·f·L·Q² / (π²·g·D⁵)      →      D = [ 8·f·L·Q² / (π²·g·hL) ]^(1/5)
```

Es la misma idea que en la diapositiva 33, donde despejan Darcy para la velocidad:
`V = √(2g·hL / (f·L/D))`. Para Q: `Q = V·πD²/4`.

---

## 3. El núcleo común: cómo se calcula f

**Colebrook no se puede despejar**, porque f está a los dos lados. Se itera (punto fijo):

1. Se arranca con la **f de Haaland** (explícita, ya está cerca).
2. Se mete esa f en el lado derecho de Colebrook y sale una f nueva.
3. Se repite hasta que f deje de cambiar. Suelen bastar **6 iteraciones**.

Ejemplo (Re = 100 000, ε/D = 0.0002):
`0.018735 → 0.019031 → 0.019003 → 0.019006 → 0.019005 → 0.019005 → 0.019005`

Cada paso reduce el error unas 10 veces. **Mientras itera f, el diámetro D (y por tanto Re y ε/D)
queda fijo**: Colebrook se resuelve para un Re y un ε/D dados.

**Error Haaland vs Colebrook** que muestra el programa: `|f_H − f_C| / f_C × 100` (%).
Esa definición es mía; confirmala con el profesor. Para Re = 1e5 y ε/D = 2e-4 da 1.42 %.

**Cuál f se usa para calcular hL:** siempre la **f de Colebrook final**. Haaland solo es el arranque de
Colebrook y el punto de comparación.

---

## 4. Los tres tipos de problema

La clase los clasifica según qué se conoce y qué se pide (diapositiva 12):

| Tipo | Se conoce | Se pide | Qué se supone para iterar |
|---|---|---|---|
| **1** | L, D, Q | ΔP (o hL) | nada |
| **2** | L, D, hL | Q | **f** |
| **3** | L, Q, hL | D | **D** |

### Tipo 1: pérdida hL (Ejemplo 8-3)  → opción 2
Todo se calcula en línea recta:
1. `V = Q/(πD²/4)`
2. `Re = VD/ν` → régimen
3. `ε/D`
4. f Haaland → f Colebrook (iterando)
5. `hL = f·(L/D)·V²/2g`; `ΔP = ρ·g·hL`; potencia `W = Q·ΔP`

**Ejemplo 8-3 (sistema inglés):** Q = 0.2 ft³/s, D = 2/12 ft, L = 200 ft, ε = 0.000007 ft,
μ = 7.536e-4, ρ = 62.36.

| | Diapositiva | Programa |
|---|---|---|
| V | 9.17 ft/s | 9.167 |
| Re | 126 400 | 126 432 |
| e/D | 0.000042 | 4.2e-05 |
| f Haaland / Colebrook | 0.0172 / 0.0174 | 0.01718 / 0.01740 |
| hL | 27.3 ft | 27.24 (la diapositiva redondea f) |
| ΔP | 1700 lbf/ft² = 11.8 psi | 1699 = 11.80 |
| Potencia | 461 W | 460.7 |

### Tipo 2: caudal Q (Ejemplo 8-5)  → opción 3
Aquí no se conoce Q, así que **no se conoce V, ni Re, ni f**. Lo que sí se conoce es hL, que relaciona V y f
por Darcy. Por eso se **supone una f** y se corrige (método 3 de la diapositiva 33):

| Paso | Qué se hace |
|---|---|
| 1 | Con la f supuesta: `V = √(2g·hL / (f·L/D))` (Darcy despejada para V) |
| 2 | `Re = V·D/ν` |
| 3 | f corregida con Colebrook |
| 4 | Si f corregida ≈ f supuesta, listo. Si no, la corregida pasa a ser la supuesta |
| 5 | `Q = V·πD²/4` (Darcy despejada para Q) |

La f inicial **no cambia el resultado**, solo el número de vueltas (la diapositiva usa 0.04).

**Ejemplo 8-5** (aire, D = 0.267, L = 300, hL = 20, ε = 0, μ = 1.895e-5, ρ = 1.145, f inicial 0.04):

| it | f supuesta | V | Re | f corregida |
|---|---|---|---|---|
| 1 | 0.04000 | 2.955 | 47 669 | 0.02112 |
| 2 | 0.02112 | 4.067 | 65 609 | 0.01968 |
| 3 | 0.01968 | 4.213 | 67 963 | 0.01953 |
| 4 | 0.01953 | 4.229 | 68 223 | 0.01951 |
| 5 | 0.01951 | 4.231 | 68 251 | 0.01951 |

Resultado: **V = 4.231 m/s, Q = 0.2369 m³/s** (la diapositiva: 0.24), Re ≈ 68 254, f = 0.0195.
La caída de caudal respecto de los 0.35 originales es de ~32 % (la diapositiva dice 31 %, con valores redondeados).

> Nota: los valores de las primeras filas difieren un poco de la tabla de la diapositiva 34 porque los Re
> de esa tabla no cuadran exactos con `V·D/ν`. Además, el recuadro de la diapositiva 33 muestra la fórmula
> de Haaland, pero los números de la tabla coinciden con **Colebrook**; el programa usa Colebrook.

### Tipo 3: diámetro D (Ejemplo 8-4)  → opciones 4 y 5
Aquí D está en `V`, en `Re`, en `ε/D` y en Darcy. **No se puede despejar directo**, así que se supone un D.
La diapositiva 23 ofrece tres enfoques:
1. **Iterativo:** suponer D, calcular hL, comparar con la pedida, repetir.
2. Resolver las 4 ecuaciones a la vez (D, V, Re, f) con un solucionador.
3. **Swamee-Jain directo** (da D ≈ 0.271 m).

La diapositiva 25 une el 3 con el 1: *"con el resultado de Swamee-Jain como estimado inicial, el diámetro
converge a 0.267 m en poco tiempo."* Procedimiento:

| Paso | Qué se hace |
|---|---|
| 0 | **D₀ de Swamee-Jain** (opción 4) |
| 1 | Con ese D: `V`, `Re`, `ε/D` |
| 2 | f Haaland (arranque) → **f Colebrook** (iterando, con D fijo) |
| 3 | Chequeo: `hL = f·(L/D)·V²/2g`. Si hL < pedida, D es grande (bajar); si hL > pedida, D es chico (subir) |
| 4 | **D nuevo** despejando Darcy, con esa f y **la hL pedida**: `D = [8fLQ²/(π²g·hL)]^(1/5)` |
| 5 | Repetir desde el paso 1 con el D nuevo, hasta que el D deje de cambiar (hL = la pedida) |

El paso 4 usa la hL **pedida**, no la calculada. Por eso el sentido (subir/bajar) sale solo.

**Ejemplo 8-4 con los datos del profesor** (aire, Q = 0.35, hL = 20, L = 150, **ε = 1.5e-6 m**,
μ = 1.895e-5, ρ = 1.145):

| it | D de entrada | Re | f Haaland | f Colebrook | D nuevo |
|---|---|---|---|---|---|
| 1 | 0.270812 | 99 428 | 0.01786 | 0.01804 | 0.267496 |
| 2 | 0.267496 | 100 660 | 0.01782 | 0.01800 | 0.267360 |
| 3 | 0.267360 | 100 711 | 0.01782 | 0.01799 | 0.267355 |
| 4 | 0.267355 | 100 713 | 0.01782 | 0.01799 | 0.267354 |

- **D final = 0.26735 m**, V = 6.2345 m/s, Re = 100 713, e/D = 5.6105e-6, f_H = 0.01782, f_C = 0.01799, hL = 20.000.
- **Error del D** (el "% error" del profesor): `|D_Swamee − D_final| / D_final × 100` = **1.29 %**.
  Con los números redondeados que él escribió (0.272 y 0.267) da 1.87 %.
- Con ε = 0 (como indica la diapositiva 22) el D final es 0.26726 m.

#### Cosas a tener en cuenta del ejemplo del profesor
- Su fila 1 muestra D = 0.272, pero la fórmula de Swamee-Jain con sus datos da **0.2708** (el libro: 0.271).
  El exponente 0.04 amortigua mucho cualquier redondeo, así que la diferencia es del orden del 0.4 %.
- Su fila 2 coincide con el programa y con **g = 9.81**.
- Mostró solo la fila de Swamee y la final; las pasadas intermedias no aparecen en su hoja.

---

## 5. Guía del menú

Al abrir: elegís el sistema de unidades. Después aparece:

| Opción | Nombre | Para qué |
|---|---|---|
| **1** | Factor f (con V, Re y e/D) | Calcular f. Pregunta qué datos tenés: Q y D, V y D, o Re y D |
| **2** | Tipo 1: pérdida hL (dado Q) | Problemas tipo 1 |
| **3** | Tipo 2: caudal Q (dado hL) | Problemas tipo 2 (con tabla de iteración) |
| **4** | Tipo 3: D por Swamee-Jain | D₀ y verificación (fila 1 del profesor) |
| **5** | Tipo 3: D iterando hasta hL | D final con tabla de pasadas (fila 2 del profesor) |
| **6** | Canal Manning | Otro tema (no es de esta clase) |
| **7** | Cambiar sistema de unidades | SI ↔ inglés |
| **8** | Despejar D de Darcy (dado f) | Último paso del tipo 3 con una f que ya tenés |
| **9** | Despejar Q de Darcy (dado f) | Último paso del tipo 2 con una f que ya tenés |
| **0** | Salir | |

### Qué datos pide cada opción
| Opción | Datos |
|---|---|
| 1 | Datos (1, 2 o 3) → Q o V o Re, D · e · (ν o μ y ρ, salvo con Re directo) · ¿ver iteraciones? |
| 2 | Q, D, L, e, (ν o μ y ρ) |
| 3 | hL, D, L, e, (ν o μ y ρ), **f inicial supuesta** (ej. 0.04) |
| 4 | Q, hL máxima, L, e, (ν o μ y ρ) |
| 5 | Q, hL pedida, L, e, (ν o μ y ρ) |
| 8 | f (Colebrook), L, Q, hL pedida |
| 9 | f (Colebrook), L, D, hL |

### Qué entrega cada opción
Todas las de los tipos 1, 2 y 3 muestran: **V, Re (con régimen), e/D, f Haaland, f Colebrook (con nº de
iteraciones), error H vs C, hL con cada f**, y `ΔP` y potencia si diste μ y ρ.

| Opción | Además entrega |
|---|---|
| 2 | hL de Swamee-Jain, para comparar |
| 3 | La tabla de iteración (f supuesta → V → Re → f corregida), `V` y **`Q` despejados de Darcy**, Q de Swamee-Jain |
| 4 | **D de Swamee-Jain**, **D despejado de Darcy** (D nuevo de la pasada 1), la hL que resulta y si cumple |
| 5 | D inicial (Swamee), tabla de pasadas, nº de vueltas, **error del D (Swamee vs final)**, D final, **D despejado de Darcy** (igual al final: comprobación) y si cumple |
| 8 | D y la V que resulta |
| 9 | V y Q |

---

## 6. Cómo reproducir la tabla del profesor (Ejemplo 8-4)
1. Opción **4** → fila 1: D de Swamee-Jain, V, Re, e/D, f_H, f_C, hL (= 18.81).
2. Opción **5** → fila 2: D final, V, Re, e/D, f_H, f_C, hL (= 20), más el error del D.

Datos para ambas: Q = `0.35`, hL = `20`, L = `150`, e = `1.5e-6`, ν = `0`, μ = `1.895e-5`, ρ = `1.145`.

---

## 7. Límites y advertencias
- **Transición (2300 < Re < 4000):** el programa usa Colebrook igual y solo avisa.
- **Laminar (Re < 2300):** usa `f = 64/Re`; Haaland y Colebrook no aplican, y no se muestra el error H vs C.
- **Un solo tubo recto:** no hay pérdidas menores (accesorios, codos) ni redes.
- **Swamee-Jain:** el programa avisa si te salís de su rango de validez.
- **Manning** (opción 6) no pertenece a esta clase; en inglés usa k = 1.486.
- Las salidas muestran 8 cifras significativas; las tablas, menos, por el ancho de la pantalla.
- **Pantalla pequeña:** las opciones con muchas líneas pueden "subir" y perder las primeras. Anotá a medida que sale.

---

## 8. Mantenimiento
Requiere el SDK de Ndless en el PATH (`~/dev/Ndless/ndless-sdk`).

```bash
make fluidos.tns   # compila solo este programa
make test          # corre las pruebas en la Mac (valores de referencia calculados aparte)
make host-fluidos  # corre el menú en la Mac, sin calculadora
```

- Algoritmos: `src/fluidos/fluidos.cpp`. Menús: `src/fluidos/menu_fluidos.cpp`.
- Las pruebas (`test/test_main.cpp`) comparan contra los ejemplos 8-3, 8-4 y 8-5 de la clase y contra
  valores calculados aparte con Python.
