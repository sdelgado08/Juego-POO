cmake_minimum_required(VERSION 3.28)
project(PruebaLibreriaGrafica LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Descargar SFML 2.5.1
include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.5.1
)
FetchContent_MakeAvailable(SFML)

# Crear ejecutable
add_executable(PruebaLibreriaGrafica main.cpp Ray.cpp Ray.h Plataforma.cpp Plataforma.h Hormiga.cpp Hormiga.h)

# Incluir directorios de cabecera
target_include_directories(PruebaLibreriaGrafica PRIVATE ${sfml_SOURCE_DIR}/include)

# Enlazar las bibliotecas construidas por SFML
target_link_libraries(PruebaLibreriaGrafica sfml-graphics sfml-window sfml-system)