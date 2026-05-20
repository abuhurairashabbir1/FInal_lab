#!/bin/bash

# Task: Find all .log files in the current directory and display them

find_logs() {
    echo "Searching for .log files in current directory..."
    echo ""

    count=0

    for file in *.log; do
        if [[ ! -f "$file" ]]; then
            echo "No .log files found."
            return
        fi

        echo "Found: $file  (Size: $(wc -c < "$file") bytes)"
        count=$(( count + 1 ))
    done

    echo ""
    echo "Total .log files found: $count"
}

find_logs
