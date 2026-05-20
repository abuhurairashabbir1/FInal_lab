#!/bin/bash

# Task: Count total lines, words, and characters in a file

count_file_stats() {
    filename=$1

    if [[ ! -f "$filename" ]]; then
        echo "Error: File '$filename' not found."
        return
    fi

    lines=$(wc -l < "$filename")
    words=$(wc -w < "$filename")
    chars=$(wc -c < "$filename")

    echo "File      : $filename"
    echo "Lines     : $lines"
    echo "Words     : $words"
    echo "Characters: $chars"
}

read -p "Enter filename: " fname
count_file_stats "$fname"
