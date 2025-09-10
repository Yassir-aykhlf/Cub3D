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
%% --- Cub3D Architectural Flowchart --- %%
flowchart LR
    %% === STYLING DEFINITIONS ===
    classDef entrypoint fill:#D6EAF8,stroke:#2874A6,stroke-width:2px
    classDef process fill:#E8DAEF,stroke:#6C3483,stroke-width:1px
    classDef loop fill:#D5F5E3,stroke:#1D8348,stroke-width:2px
    classDef render_pipe fill:#D4E6F1,stroke:#1A5276,stroke-width:1px
    classDef io fill:#FCF3CF,stroke:#B7950B,stroke-width:1px
    classDef decision fill:#FADBD8,stroke:#943126,stroke-width:1px
    classDef utils fill:#F2F3F4,stroke:#566573,stroke-width:1px,stroke-dasharray: 4 4

    %% === UTILITY SYSTEMS (Used by all phases) ===
    subgraph UTILS [Utility Systems]
        direction TB
        ERROR_SYS["Error Handling<br><i>error_loggers.c</i>"]
        DATA_UTILS["Data Structures<br><i>lines.c, string.c</i>"]
        MATH_UTILS["Math Utilities<br><i>direction_utils.c</i>"]
    end
    class UTILS,ERROR_SYS,DATA_UTILS,MATH_UTILS utils

    %% === MAIN PROGRAM LIFECYCLE ===
    subgraph ProgramLifecycle ["Program Lifecycle"]
        direction LR
        START(["./cub3D map.cub"]) --> MAIN["main.c<br>• Entry point & argument validation<br>• Initializes master <b>t_game</b> struct"]
        class START,MAIN entrypoint

        MAIN --> PHASE1_SETUP
        subgraph PHASE1_SETUP [PHASE 1: Configuration & Validation]
            direction TB
            READ_FILE["Read .cub file into lines<br><i>read_file.c</i>"]
            PARSE["<b>Parse</b> config into memory<br><i>parser_*.c, tokenizer.c</i>"]
            VALIDATE["<b>Validate</b> Map Integrity<br><i>map_validation.c (Flood-fill)</i>"]
            READ_FILE --> PARSE --> VALIDATE
        end
        class PHASE1_SETUP,READ_FILE,PARSE,VALIDATE process

        VALIDATE --> PHASE2_INIT
        subgraph PHASE2_INIT [PHASE 2: Game World Initialization]
            direction TB
            WINDOW_INIT["Setup Window & Buffer<br><i>window.c</i>"]
            TEXTURE_INIT["<b>Load Textures</b> from Paths<br><i>texture_loader.c</i>"]
            PLAYER_INIT["Initialize Player State<br><i>player.c</i>"]
        end
        class PHASE2_INIT,WINDOW_INIT,TEXTURE_INIT,PLAYER_INIT process

        PHASE2_INIT --> PHASE3_LOOP
        subgraph PHASE3_LOOP [PHASE 3: Interactive Game Loop]
            direction LR
            SETUP_HOOKS["Setup Event Hooks<br><i>events.c</i><br>Connects handlers to MLX engine"]
            SETUP_HOOKS --> MLX_LOOP["MLX Engine Starts<br><i>mlx_loop()</i><br>Listens for events, schedules frames"]

            subgraph "Input Handling (Event-Driven)"
                direction TB
                MLX_LOOP -- "User Input Event" --> INPUT_HANDLER["Input Handlers<br><i>events.c</i><br><b>Task:</b> Only sets boolean flags in <b>t_input</b>"]
                INPUT_HANDLER --> EXIT_CHECK{"Exit Signal?"}
            end
            
            subgraph "Frame Rendering (Continuous Heartbeat)"
                direction TB
                MLX_LOOP -- "Render Heartbeat" --> RENDER_FRAME["(1) Update Player State<br><i>player_movement.c</i><br>Reads <b>t_input</b> flags to calculate new position"]
                RENDER_FRAME --> RAYCAST["(2) Render 3D Scene (DDA)<br><i>raycast.c, draw_utils.c</i>"]
                RAYCAST --> RENDER_MINIMAP["(3) Render Minimap<br><i>renderer_utils.c</i>"]
                RENDER_MINIMAP --> DISPLAY["(4) Display Frame<br><i>mlx_put_image_to_window()</i>"]
                DISPLAY --> FPS_LIMIT["(5) Limit Framerate<br><i>renderer.c</i>"]
            end
        end
        class PHASE3_LOOP,SETUP_HOOKS,MLX_LOOP loop
        class INPUT_HANDLER,EXIT_CHECK io
        class RENDER_FRAME,RAYCAST,RENDER_MINIMAP,DISPLAY,FPS_LIMIT render_pipe

        EXIT_CHECK -- "Yes" --> CLEANUP["<b>Cleanup All Resources</b><br><i>cleanup.c</i><br>Frees all memory, destroys images & window"]
        CLEANUP --> END([Program End])
        class CLEANUP,END decision
    end

    %% === CROSS-CUTTING DEPENDENCIES ===
    ProgramLifecycle -.-> UTILS
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
