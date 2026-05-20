#!/bin/bash

# Task: Search for a word inside a file and show which lines contain it

search_in_file() {
    filename=$1
    keyword=$2

    if [[ ! -f "$filename" ]]; then
        echo "Error: File '$filename' not found."
        return
    fi

    if grep -q "$keyword" "$filename"; then
        echo "Word '$keyword' found in '$filename':"
        grep -n "$keyword" "$filename"
    else
        echo "Word '$keyword' NOT found in '$filename'."
    fi
}

read -p "Enter filename: " fname
read -p "Enter word to search: " word
search_in_file "$fname" "$word"
