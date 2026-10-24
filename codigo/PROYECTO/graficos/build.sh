#!/bin/bash
# Compila el preview de OpenGL. Requiere GLFW instalado via Homebrew
# (brew install glfw) -- GLAD ya viene generado en glad_gen/.
set -e
cd "$(dirname "$0")"
clang++ -std=c++17 \
  -I/opt/homebrew/opt/glfw/include \
  -Iglad_gen/include \
  -I../include \
  vector_visual.cpp glad_gen/src/gl.c ../src/Vector2D.cpp \
  -L/opt/homebrew/opt/glfw/lib -lglfw \
  -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo \
  -o vector_visual
echo "Listo: ./vector_visual"
