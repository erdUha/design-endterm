#!/bin/bash
set -e
cmake --build build

echo "PartA:"
./build/PartA

echo ""
echo "PartB:"
./build/PartB

echo ""
echo "PartC:"
./build/PartC
