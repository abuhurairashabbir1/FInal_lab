#!/bin/bash

# Task: Check if a number is prime or not

is_prime() {
    num=$1

    if (( num < 2 )); then
        echo "$num is NOT prime"
        return
    fi

    for (( i = 2; i * i <= num; i++ )); do
        if (( num % i == 0 )); then
            echo "$num is NOT prime"
            return
        fi
    done

    echo "$num is prime"
}

read -p "Enter a number: " n
is_prime $n
