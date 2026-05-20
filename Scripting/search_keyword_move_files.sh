#!/bin/bash

# Task: Search for a keyword inside .log files and move matching files to a folder

search_and_move() {
    keyword=$1
    dest=$2

    mkdir -p "$dest"

    moved=0
    total=0

    for file in *.log; do
        if [[ ! -f "$file" ]]; then
            echo "No .log files found in current directory."
            return
        fi

        total=$(( total + 1 ))

        if grep -q "$keyword" "$file"; then
            mv "$file" "$dest/"
            echo "$file -> keyword '$keyword' found. Moved to '$dest/'"
            moved=$(( moved + 1 ))
        else
            echo "$file -> keyword '$keyword' not found. Kept."
        fi
    done

    echo ""
    echo "Total files checked : $total"
    echo "Files moved         : $moved"
}

read -p "Enter keyword to search: " word
read -p "Enter destination folder: " folder

echo ""
search_and_move "$word" "$folder"
