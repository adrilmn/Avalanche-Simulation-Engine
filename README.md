# Avalanche Simulation

A C++11 particle-based simulation of granular materials interacting with gravity, obstacles, and neighboring particles.

The project models **snow and rock particles** and focuses on clean object-oriented design and efficient spatial queries. The simulation includes a 3D spatial partitioning grid that limits particle interaction checks to nearby cells instead of scanning the entire particle set.

## Highlights

- Object-oriented C++ architecture with polymorphic particles and obstacles
- Snow and rock particle models
- Gravity and fluid-drag forces
- Particle–particle interaction forces
- Collision handling with planar obstacles
- 3D spatial partitioning for neighborhood queries
- Dynamic particle sources
- Text-based simulation output
- C++11, standard-library-only implementation

## Architecture

```text
Systeme
├── Particule
│   ├── ParticuleNeige
│   └── ParticuleRoche
├── Obstacle
│   ├── Plan
│   └── Dalle
├── Source
└── Spatial grid (Case)
```

The `Systeme` class owns the simulation objects and advances the system in discrete time steps. Polymorphism allows different particle and obstacle types to share the same simulation engine.

## Spatial optimization

A naive particle interaction loop requires approximately **O(N²)** pair checks.

The simulation maintains a 3D grid and only evaluates particles located in the current cell and its 26 neighboring cells. Under a reasonably uniform particle distribution, the number of local interaction checks becomes approximately linear in the number of particles.

This is the main performance-oriented component of the project.

## Build

### CMake

```bash
cmake -S . -B build
cmake --build build
./build/avalanche_simulation
```

### Make

```bash
make
./avalanche_simulation
```

Clean build artifacts with:

```bash
make clean
```

## Project structure

```text
.
├── app/            # Executable entry point
├── include/        # Public headers
├── src/            # Simulation implementation
├── CMakeLists.txt
├── Makefile
└── README.md
```

## Technical focus

This project demonstrates practical C++ concepts including:

- inheritance and runtime polymorphism
- abstract interfaces
- RAII and `std::unique_ptr`
- operator overloading
- modular compilation
- numerical vector operations
- physical simulation
- spatial data structures and algorithmic optimization

## Status

The repository contains the cleaned, standalone simulation and its build configuration. Educational worksheets, development logs, assignment-specific material, generated build files, and intermediate versions are intentionally excluded.
