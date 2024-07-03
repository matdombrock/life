#!/bin/bash
# sudo apt install imagemagick
# Usage:
# ./resize.sh <size> <?fileName>
# ./resize.sh 512 # resize the latest gif to 512x512
# ./resize.sh 1024 life1234 # resize a specific gif

cd out || exit 1

newSize=$1

#
# Specific file
#
if [[ -n "$2" ]]; then
    input="$2"
    convert $input.gif -filter point -resize 512x512 $input-rs.gif
fi

#
# Latest file
#
# Find the most recently created gif file (excluding "*rs.gif")
latest_gif=$(find . -maxdepth 1 -type f -name "*.gif" ! -name "*rs.gif" -printf "%T@ %p\n" | sort -nr | head -n 1 | cut -d' ' -f2-)

# Check if a gif file was found
if [[ -z "$latest_gif" ]]; then
  echo "No gif file found!"
  exit 1
fi

# Extract filename and path
filename="${latest_gif##*/}"

# Resize the gif
convert "$latest_gif" -filter point -resize "${newSize}x${newSize}" "${filename}-rs.gif"

echo "Successfully resized $filename to ${filename}-rs.gif"