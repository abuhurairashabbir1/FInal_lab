#!/bin/bash

# Task: Read a file line by line and display each line with its line number

read_file() {
    filename=$1

    if [[ ! -f "$filename" ]]; then
        echo "Error: File '$filename' not found."
        return
    fi

    line_num=1
    while IFS= read -r line; do
        echo "Line $line_num: $line"
        line_num=$(( line_num + 1 ))
    done < "$filename"
}

read -p "Enter filename to read: " fname
read_file "$fname"
