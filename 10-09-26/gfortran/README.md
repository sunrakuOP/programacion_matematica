# gfortran — workspace de práctica

Un ejemplo por tema de la ruta (bloque 6, "De C++ a Fortran"). Cada `.f90` ya fue compilado y
corrido de verdad antes de dejarlo acá — no son solo copias del roadmap.

## Cómo compilar y correr cualquiera de estos

Desde esta carpeta (`gfortran/`), entrá a la subcarpeta del tema y corré:

```bash
export PATH="/opt/homebrew/bin:$PATH"     # solo si gfortran no está ya en tu PATH
gfortran -Wall -fcheck=all -o programa nombre_del_archivo.f90
./programa
```

`-Wall` muestra todos los warnings; `-fcheck=all` activa chequeos de límites de array y otros
errores en tiempo de ejecución — los mismos flags de modo debug que usa el proyecto real de tu
papá (`make FC=gfortran test-debug` en DELOS-3D e IFC-Bridge).

## Qué hay en cada carpeta

| Carpeta | Tema de la ruta | Qué muestra |
|---|---|---|
| `01-hola-mundo/` | 6.2 | `implicit none`, `print`, compilar y correr |
| `02-variables/` | 6.3 | `real(8)`, declaración y asignación |
| `03-control-flujo/` | 6.4 | `do i = 1, 10` (intervalo CERRADO, incluye el 10) |
| `04-arrays/` | 6.5 | matrices nativas, `sum()`, `matmul()` sin loops |
| `05-subrutinas-modulos/` | 6.6 | `module`, `subroutine`, `intent` — la rigidez de un elemento barra (EA/L) |
| `06-tipos-derivados/` | 6.7 | `type` — el `struct` de Fortran |

## Para abrir en VS Code

```bash
code /Users/sunraku2403/Documents/PAPA_09_codigo/10-09-26/gfortran
```

La extensión "Modern Fortran" y `fortls` ya están instalados — vas a tener resaltado de sintaxis
y autocompletado apenas abras cualquier `.f90` de acá.

## Siguiente paso natural

Cuando te sientas cómodo con estos 6, el próximo ejercicio real es traducir tu solver de cercha
en C++ (tema 6.1) a un módulo Fortran acá mismo — creá una carpeta `07-cercha/` y armalo con lo
que aprendiste en `05-subrutinas-modulos/`.
