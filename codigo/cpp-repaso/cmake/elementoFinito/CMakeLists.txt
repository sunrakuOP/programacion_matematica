cmake_minimum_required(VERSION 3.20)
project(ElementoFinito LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- ejecutable principal (igual que antes) ---
add_executable(elemento_finito
    src/main.cpp
    src/ElementoFinito.cpp
    src/ElementoTriangular.cpp
    src/ElementoCuadrilatero.cpp
)
target_include_directories(elemento_finito PRIVATE include)

# --- Catch2 vía FetchContent ---
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.7.1
)
FetchContent_MakeAvailable(Catch2)

# --- ejecutable de tests (nota: NO incluye main.cpp) ---
add_executable(tests
    tests/test_matriz.cpp
    src/ElementoFinito.cpp
    src/ElementoTriangular.cpp
    src/ElementoCuadrilatero.cpp
)
target_include_directories(tests PRIVATE include)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

enable_testing()
include(CTest)
include(Catch)
catch_discover_tests(tests)
