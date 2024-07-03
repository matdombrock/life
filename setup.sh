#!/bin/bash
echo "Copying config..."
cp cfg.example.txt cfg.txt || exit 1
echo "Creating output dir..."
mkdir -p ./out