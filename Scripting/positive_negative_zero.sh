#!/bin/bash

# Task: Check if a number is positive, negative, or zero

check_sign() {
    num=$1

    if (( num > 0 )); then
        echo "$num is Positive"
    elif (( num < 0 )); then
        echo "$num is Negative"
    else
        echo "$num is Zero"
    fi
}

read -p "Enter a number: " n
check_sign $n
