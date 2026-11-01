cmake_minimum_required(VERSION 3.10)
project(urgencias CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra)

add_executable(urgencias
    main.cpp
    src/modelo/Enums.cpp
    src/modelo/Paciente.cpp
    src/hospital/Cama.cpp
    src/hospital/Sala.cpp
)

# permite escribir #include "modelo/Paciente.hpp" desde cualquier archivo
target_include_directories(urgencias PRIVATE include)
