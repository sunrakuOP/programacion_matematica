#!/bin/bash
# Compila y corre el archivo activo. Si la carpeta tiene otros .cpp SIN main()
# (la clase, el .cpp de implementacion), los suma al enlace automaticamente.
# Los .cpp que tienen su propio main() (ejercicios sueltos) se ignoran.
# Uso: compilar.sh <ruta del archivo activo>

dir=$(dirname "$1")
cd "$dir" || exit 1
activo=$(basename "$1")
patron='^[[:space:]]*int[[:space:]]+main[[:space:]]*\('

if grep -qE "$patron" "$activo" 2>/dev/null; then
    principal="$activo"
else
    principal=$(grep -lE "$patron" *.cpp 2>/dev/null | head -n1)
fi

if [ -z "$principal" ]; then
    echo "No encontre ningun main() en esta carpeta."
    exit 1
fi

extras=()
for f in *.cpp; do
    [ "$f" = "$principal" ] && continue
    grep -qE "$patron" "$f" || extras+=("$f")
done

bin="/tmp/$(basename "$dir")_run"
echo "Compilando: $principal ${extras[*]}"
clang++ -std=c++20 -Wall -Wextra -fsanitize=address -o "$bin" "$principal" "${extras[@]}" && "$bin"
rm -f "$bin"
