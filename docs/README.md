# Cub3D - Project Structure

## Directory Structure

```
Cub3D-main/
├── src/                       # Source code
│   ├── core/                  # Core application logic
│   │   ├── main.c             # Entry point
│   │   ├── game.c             # Main game loop and initialization
│   │   ├── cleanup.c          # Memory cleanup
│   │   └── cleanup_helpers.c
│   ├── engine/                # Game engine components
│   │   ├── player.c           # Player state management
│   │   ├── player_movement.c  # Player movement logic
│   │   └── direction_utils.c  # Direction calculations
│   ├── graphics/              # Graphics and rendering
│   │   ├── render/            # Rendering subsystem
│   │   │   ├── renderer.c
│   │   │   ├── render_helpers.c
│   │   │   └── draw_utils.c
│   │   ├── raycast/           # Raycasting engine
│   │   │   ├── raycast.c
│   │   │   ├── ray_utils.c
│   │   │   └── texture_utils.c
│   │   ├── window/            # Window management
│   │   │   └── window.c
│   │   └── texture_loader.c
│   ├── io/                    # Input/Output operations
│   │   ├── parsing/           # Configuration parsing
│   │   │   ├── read_file.c
│   │   │   ├── parse_game_config.c
│   │   │   ├── parse_rgb.c
│   │   │   ├── parse_textures.c
│   │   │   ├── parse_texture_helpers.c
│   │   │   ├── parse_utils.c
│   │   │   ├── parse_rgb_helpers.c
│   │   │   ├── parse_debug.c
│   │   │   └── parse_map.c
│   │   ├── lexer/             # Lexical analysis
│   │   │   ├── tokenizer.c
│   │   │   ├── lexer_read.c
│   │   │   ├── lexer.c
│   │   │   └── token_utils.c
│   │   └── events/            # Event handling
│   │       └── events.c
│   └── utils/                 # Utility functions
│       ├── containers/        # Data structures
│       │   ├── lines.c
│       │   └── string.c
│       ├── gnl/               # Get Next Line
│       │   ├── get_next_line.c
│       │   └── get_next_line_utils.c
│       ├── error/             # Error handling
│       │   └── error_loggers.c
│       └── map/               # Map utilities
│           ├── map_validation.c
│           ├── map_validation_helpers.c
│           ├── map_utils.c
│           └── matrix_utils.c
├── include/                   # Header files
│   ├── cube.h
│   └── get_next_line.h
├── assets/                    # Game assets
│   ├── maps/                  # Map files (.cub)
│   └── textures/              # Texture files (.xpm)
├── tests/                     # Test files and scripts
├── config/                    # Configuration files
├── docs/                      # Documentation
└── Makefile
```

## Architecture Overview

### Core Layer (`src/core/`)
- **main.c**: Application entry point
- **game.c**: Main game initialization and loop
- **cleanup.c**: Memory management and cleanup

### Engine Layer (`src/engine/`)
- **Player Management**: Player state, movement, and physics
- **Direction Utils**: Mathematical utilities for direction calculations

### Graphics Layer (`src/graphics/`)
- **Rendering**: Screen buffer management, drawing operations
- **Raycasting**: 3D projection algorithms and texture mapping
- **Window**: MLX window management

### I/O Layer (`src/io/`)
- **Parsing**: Configuration file parsing (.cub files)
- **Lexer**: Tokenization and lexical analysis
- **Events**: Keyboard and window event handling

### Utils Layer (`src/utils/`)
- **Containers**: Dynamic data structures (lines, strings)
- **GNL**: File reading utilities
- **Error**: Error logging and handling
- **Map**: Map validation and manipulation

## Build System

### Available Targets
- `make` or `make all`: Build the project
- `make clean`: Remove object files
- `make fclean`: Remove all build artifacts
- `make re`: Clean rebuild
- `make run`: Build and run with default map
- `make test`: Run multiple test scenarios
- `make norm`: Check code style with norminette
- `make valgrind`: Run with memory leak detection
- `make print-srcs`: Display source file organization

### Build Configuration
- Debug build: `make debug` (with AddressSanitizer)
- Release build: `make release` (optimized)

## Benefits of This Structure

1. **Separation of Concerns**: Each directory has a clear responsibility
2. **Scalability**: Easy to add new features to appropriate modules
3. **Maintainability**: Related files are grouped together
4. **Testing**: Assets and tests are properly organized
5. **Documentation**: Clear project documentation structure
