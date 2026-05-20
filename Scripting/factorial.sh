#!/bin/bash

# Task: Calculate factorial of a number

factorial() {
    num=$1

    if (( num < 0 )); then
        echo "Factorial is not defined for negative numbers"
        return
    fi

    result=1
    for (( i = 1; i <= num; i++ )); do
        result=$(( result * i ))
    done

    echo "Factorial of $num = $result"
}

read -p "Enter a number: " n
factorial $n
