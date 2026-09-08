cmake_minimum_required(VERSION 3.16)
project(AvalancheSimulation VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(avalanche
    src/Aleatoire.cc
    src/Case.cc
    src/Obstacle.cc
    src/Particule.cc
    src/ParticuleNeige.cc
    src/ParticuleRoche.cc
    src/Source.cc
    src/Systeme.cc
    src/Vecteur3D.cc
)

target_include_directories(avalanche PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(avalanche PRIVATE
    -Wall -Wextra -Wpedantic
)

add_executable(avalanche_simulation app/main.cpp)
target_link_libraries(avalanche_simulation PRIVATE avalanche)
target_compile_options(avalanche_simulation PRIVATE
    -Wall -Wextra -Wpedantic
)

