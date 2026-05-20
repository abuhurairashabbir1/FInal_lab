#!/bin/bash

# Task: Print multiplication table of a number (1 to 10)

multiplication_table() {
    number=$1
    echo "Multiplication table of $number:"

    for i in {1..10}; do
        result=$(( number * i ))
        echo "$number x $i = $result"
    done
}

read -p "Enter a number: " n
multiplication_table $n
