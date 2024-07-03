#!/bin/bash

#cd ./out || exit 1

# Find the most recently created html file
url=$(find ./out -maxdepth 1 -type f -name "*.html" -printf "%T@ %p\n" | sort -nr | head -n 1 | cut -d' ' -f2-)

# Check if a gif file was found
if [[ -z "$url" ]]; then
  echo "No gif file found!"
  exit 1
fi
# Write the nohup.out file in case we have an issue but delete it if we dont
nohup open $url || exit 1
rm nohup.out