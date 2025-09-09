#!/bin/bash

# Test script for Cub3D maps
# Run this script to test all maps with your cub3D executable

EXECUTABLE="./cub3D"
MAPS_DIR="maps"

echo "========================================"
echo "Testing Cub3D with various test maps"
echo "========================================"

# Check if executable exists
if [ ! -f "$EXECUTABLE" ]; then
    echo "Error: $EXECUTABLE not found!"
    echo "Please compile your project first with 'make'"
    exit 1
fi

# Check if maps directory exists
if [ ! -d "$MAPS_DIR" ]; then
    echo "Error: $MAPS_DIR directory not found!"
    exit 1
fi

echo ""
echo "Testing VALID maps (should work):"
echo "--------------------------------"

valid_maps=(
    "test_simple.cub"
    "test_minimum.cub" 
    "test_corridor.cub"
    "test_large.cub"
    "test_maze.cub"
    "test_basic.cub"
)

for map in "${valid_maps[@]}"; do
    if [ -f "$MAPS_DIR/$map" ]; then
        echo "Testing: $map"
        timeout 3s $EXECUTABLE "$MAPS_DIR/$map" > /dev/null 2>&1
        result=$?
        if [ $result -eq 0 ] || [ $result -eq 124 ]; then
            echo "  ✓ PASSED (loaded successfully)"
        else
            echo "  ✗ FAILED (exit code: $result)"
        fi
    else
        echo "  ? SKIPPED ($map not found)"
    fi
done

echo ""
echo "Testing INVALID maps (should fail gracefully):"
echo "----------------------------------------------"

invalid_maps=(
    "test_no_player.cub"
    "test_multiple_players.cub"
    "test_open_map.cub"
)

for map in "${invalid_maps[@]}"; do
    if [ -f "$MAPS_DIR/$map" ]; then
        echo "Testing: $map"
        timeout 3s $EXECUTABLE "$MAPS_DIR/$map" > /dev/null 2>&1
        result=$?
        if [ $result -ne 0 ] && [ $result -ne 124 ]; then
            echo "  ✓ PASSED (correctly rejected)"
        else
            echo "  ✗ FAILED (should have been rejected)"
        fi
    else
        echo "  ? SKIPPED ($map not found)"
    fi
done

echo ""
echo "========================================"
echo "Testing complete!"
echo "========================================"
echo ""
echo "To manually test a specific map:"
echo "  $EXECUTABLE $MAPS_DIR/test_simple.cub"
echo ""
echo "Use WASD to move, ESC to quit"
