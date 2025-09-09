# Cub3D

A 3D raycasting engine implementation inspired by the classic Wolfenstein 3D game. This project creates a first-person perspective maze navigation experience using advanced raycasting algorithms and texture mapping.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [System Architecture](#system-architecture)
- [Installation](#installation)
- [Usage](#usage)
- [Map Configuration](#map-configuration)
- [Controls](#controls)
- [Project Structure](#project-structure)
- [Build System](#build-system)
- [Technical Details](#technical-details)
- [Testing](#testing)
- [Contributing](#contributing)

## Overview

Cub3D is a 3D graphics engine built from scratch using the MiniLibX graphics library. The project demonstrates fundamental computer graphics concepts including raycasting, texture mapping, and real-time rendering. Players can navigate through maze-like environments with textured walls, creating an immersive 3D experience rendered in real-time.

## Features

- **Real-time 3D rendering** using raycasting algorithms
- **Texture mapping** with support for different wall textures based on direction
- **Smooth player movement** with collision detection
- **Mouse and keyboard controls** for navigation
- **Configurable maps** through .cub configuration files
- **Performance optimized** rendering at 60 FPS target
- **Memory safe** implementation with comprehensive cleanup
- **Modular architecture** for easy maintenance and extension

## System Architecture

```mermaid
graph TB
    A[Main Entry Point] --> B[Game Initialization]
    B --> C[Config Parser]
    B --> D[Graphics System]
    B --> E[Game Engine]
    
    C --> C1[Lexer/Tokenizer]
    C --> C2[Map Parser]
    C --> C3[Texture Parser]
    C --> C4[RGB Parser]
    
    D --> D1[Window Manager]
    D --> D2[Texture Loader]
    D --> D3[Raycasting Engine]
    D --> D4[Renderer]
    
    E --> E1[Player System]
    E --> E2[Movement Handler]
    E --> E3[Event System]
    
    D3 --> D3a[Ray Calculation]
    D3 --> D3b[DDA Algorithm]
    D3 --> D3c[Wall Detection]
    D3 --> D3d[Distance Calculation]
    
    D4 --> D4a[Screen Buffer]
    D4 --> D4b[Texture Mapping]
    D4 --> D4c[Pixel Drawing]
    
    F[Game Loop] --> G[Input Processing]
    G --> H[Player Update]
    H --> I[Raycasting]
    I --> J[Rendering]
    J --> K[Display]
    K --> F
    
    L[Utils Layer] --> L1[Memory Management]
    L --> L2[Data Structures]
    L --> L3[Error Handling]
    L --> L4[Map Validation]
```

## Installation

### Prerequisites

- GCC compiler with C99 support
- Make build system
- X11 development libraries (Linux)
- MiniLibX graphics library

### Build Instructions

```bash
# Clone the repository
git clone [repository-url]
cd Cub3D-main

# Build the project
make

# Build and run with default map
make run

# Build with debug information
make debug

# Clean build artifacts
make clean
make fclean

# Complete rebuild
make re
```

### Dependencies

The project automatically handles MiniLibX linking. Ensure you have X11 development libraries installed:

```bash
# Ubuntu/Debian
sudo apt-get install libx11-dev libxext-dev

# Fedora/CentOS
sudo yum install libX11-devel libXext-devel
```

## Usage

### Basic Usage

```bash
./cub3D [map_file.cub]
```

### Examples

```bash
# Run with basic test map
./cub3D assets/maps/test_basic.cub

# Run with maze configuration
./cub3D assets/maps/test_maze.cub

# Run with large map
./cub3D assets/maps/test_large.cub
```

## Map Configuration

Maps are defined in `.cub` files with the following format:

### Texture Configuration
```
NO assets/textures/north_wall.xpm  # North wall texture
SO assets/textures/south_wall.xpm  # South wall texture
WE assets/textures/west_wall.xpm   # West wall texture
EA assets/textures/east_wall.xpm   # East wall texture
```

### Color Configuration
```
F 220,100,0  # Floor color (RGB)
C 225,30,0   # Ceiling color (RGB)
```

### Map Layout
```
1111111111111111111111111
1000000000110000000000001
1011000001110000000000001
1001000000000000000000001
11111111101100000111000011111111
100000000011000001110111111111111
11110111111111011100000010001
11000000110101011100000010001
10000000000000001100000010001
11000001110101011111011110N0111
11111111 1111111 111111111111
```

### Map Elements
- `1`: Wall
- `0`: Empty space (walkable)
- `N/S/E/W`: Player starting position and orientation
- ` `: Void (outside map boundaries)

## Controls

### Movement
- `W`: Move forward
- `S`: Move backward
- `A`: Move left
- `D`: Move right

### Camera
- `←`: Rotate camera left
- `→`: Rotate camera right

### System
- `ESC`: Exit game

## Project Structure

```
Cub3D-main/
├── src/                    # Source code
│   ├── core/              # Core application logic
│   ├── engine/            # Game engine components
│   ├── graphics/          # Graphics and rendering
│   │   ├── render/        # Rendering subsystem
│   │   ├── raycast/       # Raycasting engine
│   │   └── window/        # Window management
│   ├── io/                # Input/Output operations
│   │   ├── parsing/       # Configuration parsing
│   │   ├── lexer/         # Lexical analysis
│   │   └── events/        # Event handling
│   └── utils/             # Utility functions
├── include/               # Header files
├── assets/                # Game assets
│   ├── maps/             # Map configurations
│   └── textures/         # Wall textures
├── tests/                # Test files
├── config/               # Configuration templates
└── docs/                 # Documentation
```

## Build System

### Available Targets

| Target | Description |
|--------|-------------|
| `make` | Build the project |
| `make clean` | Remove object files |
| `make fclean` | Remove all build artifacts |
| `make re` | Clean rebuild |
| `make run` | Build and run with default map |
| `make test` | Run test scenarios |
| `make norm` | Check code style |
| `make valgrind` | Run with memory leak detection |

### Build Configuration

The Makefile supports different build configurations:
- **Standard build**: Optimized for general use
- **Debug build**: Includes debugging symbols and AddressSanitizer
- **Release build**: Optimized for performance

## Technical Details

### Raycasting Algorithm

The engine uses a DDA (Digital Differential Analyzer) algorithm for efficient ray-wall intersection detection:

1. **Ray Initialization**: Calculate ray direction for each screen column
2. **DDA Setup**: Determine step direction and initial distances
3. **Wall Detection**: Iteratively step through the grid until hitting a wall
4. **Distance Calculation**: Compute perpendicular wall distance to avoid fisheye effect
5. **Texture Mapping**: Map wall textures based on hit position and wall orientation

### Performance Optimizations

- **Efficient memory management** with object pooling
- **Optimized texture sampling** with integer arithmetic
- **Frame rate limiting** to maintain consistent 60 FPS
- **Minimal memory allocations** during render loop
- **Cache-friendly data structures** for better performance

### Graphics Pipeline

1. **Input Processing**: Handle keyboard and mouse events
2. **Player Update**: Update player position and orientation
3. **Raycasting**: Cast rays for each screen column
4. **Wall Rendering**: Draw textured wall segments
5. **Floor/Ceiling**: Fill remaining pixels with solid colors
6. **Buffer Display**: Present the completed frame

## Testing

### Automated Tests

```bash
# Run all test scenarios
make test

# Memory leak detection
make valgrind

# Code style validation
make norm
```

### Test Maps

The project includes various test maps for different scenarios:
- `test_basic.cub`: Simple rectangular map
- `test_maze.cub`: Complex maze layout
- `test_large.cub`: Large-scale environment
- `test_corridor.cub`: Long corridor test
- `test_minimum.cub`: Minimal valid map