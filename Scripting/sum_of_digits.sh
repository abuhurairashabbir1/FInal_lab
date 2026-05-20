#!/bin/bash

# Task: Calculate the sum of digits of a number

sum_of_digits() {
    number=$1
    sum=0

    while (( number > 0 )); do
        digit=$(( number % 10 ))
        sum=$(( sum + digit ))
        number=$(( number / 10 ))
    done

    echo "Sum of digits = $sum"
}

read -p "Enter a number: " n
sum_of_digits $n
