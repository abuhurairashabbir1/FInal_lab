#!/bin/bash

# Task: Check if a number is even or odd

even_or_odd() {
    num=$1
    if (( num % 2 == 0 )); then
        echo "$num is Even"
    else
        echo "$num is Odd"
    fi
}

read -p "Enter a number: " n
even_or_odd $n
