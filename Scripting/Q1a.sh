#!/bin/bash

echo "--- File Organization Started ---"

# Create subdirectories if they don't exist
mkdir -p short
mkdir -p medium
mkdir -p long

# Counters
total=0
short_count=0
medium_count=0
long_count=0

# Loop through all .txt files in current directory
for file in *.txt; do

    # Skip if no .txt files exist
    if [[ ! -f "$file" ]]; then
        echo "No .txt files found in current directory"
        exit 1
    fi

    # Count words in the file
    words=$(wc -w < "$file")

    # Categorize based on word count and move
    if (( words < 100 )); then
        mv "$file" short/
        echo "Processed $file (Words: $words) -> Moved to short/"
        short_count=$(( short_count + 1 ))

    elif (( words <= 500 )); then
        mv "$file" medium/
        echo "Processed $file (Words: $words) -> Moved to medium/"
        medium_count=$(( medium_count + 1 ))

    else
        mv "$file" long/
        echo "Processed $file (Words: $words) -> Moved to long/"
        long_count=$(( long_count + 1 ))
    fi

    total=$(( total + 1 ))

done

echo ""
echo "--- Organization Summary ---"
echo "Total .txt files processed: $total"
echo "Files moved to 'short/'  : $short_count (< 100 words)"
echo "Files moved to 'medium/' : $medium_count (100 - 500 words)"
echo "Files moved to 'long/'   : $long_count (> 500 words)"
echo "Process finished."
