#!/bin/bash

# Task: Organize .txt files into short/, medium/, long/ folders based on word count
# short  = less than 100 words
# medium = 100 to 500 words
# long   = more than 500 words

organize_files() {
    mkdir -p short medium long

    total=0
    short_count=0
    medium_count=0
    long_count=0

    for file in *.txt; do
        if [[ ! -f "$file" ]]; then
            echo "No .txt files found in current directory."
            return
        fi

        words=$(wc -w < "$file")

        if (( words < 100 )); then
            mv "$file" short/
            echo "$file (words: $words) -> short/"
            short_count=$(( short_count + 1 ))
        elif (( words <= 500 )); then
            mv "$file" medium/
            echo "$file (words: $words) -> medium/"
            medium_count=$(( medium_count + 1 ))
        else
            mv "$file" long/
            echo "$file (words: $words) -> long/"
            long_count=$(( long_count + 1 ))
        fi

        total=$(( total + 1 ))
    done

    echo ""
    echo "Total processed : $total"
    echo "short/          : $short_count"
    echo "medium/         : $medium_count"
    echo "long/           : $long_count"
}

organize_files
