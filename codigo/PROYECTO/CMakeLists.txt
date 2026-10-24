cmake_minimum_required(VERSION 3.20)
project(ProyectoFEM LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(FUENTES_COMUNES
    src/ElementoFinito.cpp
    src/ElementoTriangular.cpp
    src/ElementoCuadrilatero.cpp
    src/ElementoBarra.cpp
    src/Malla.cpp
    src/Vector2D.cpp
    src/Vector3D.cpp
)

# --- ejecutable principal ---
add_executable(proyecto_fem src/main.cpp ${FUENTES_COMUNES})
target_include_directories(proyecto_fem PRIVATE include)

# --- Catch2 via FetchContent ---
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.7.1
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(Catch2)

# --- ejecutable de tests (sin main.cpp) ---
add_executable(tests
    tests/test_elemento_barra.cpp
    tests/test_vectores.cpp
    ${FUENTES_COMUNES}
)
target_include_directories(tests PRIVATE include)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

enable_testing()
include(CTest)
include(Catch)
catch_discover_tests(tests)
