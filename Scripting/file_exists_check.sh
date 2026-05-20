#!/bin/bash

# Task: Check if a file or directory exists and print its properties

check_file() {
    name=$1

    if [[ -f "$name" ]]; then
        echo "'$name' is a regular file."
        [[ -r "$name" ]] && echo "  -> Readable"
        [[ -w "$name" ]] && echo "  -> Writable"
        [[ -x "$name" ]] && echo "  -> Executable"
    elif [[ -d "$name" ]]; then
        echo "'$name' is a directory."
    else
        echo "'$name' does not exist."
    fi
}

read -p "Enter file or directory name: " fname
check_file "$fname"
