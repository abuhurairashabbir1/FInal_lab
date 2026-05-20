#!/bin/bash

# Function 1: Calculate sum of digits
sum_of_digits() {
    number=$1
    sum=0

    # Extract last digit, add to sum, remove last digit — repeat until 0
    while (( number > 0 )); do
        digit=$(( number % 10 ))     # get last digit (e.g. 15 % 10 = 5)
        sum=$(( sum + digit ))        # add digit to sum
        number=$(( number / 10 ))    # remove last digit (e.g. 15 / 10 = 1)
    done

    echo "Sum of digits: $sum"
}

# Function 2: Print multiplication table 1 to 10
multiplication_table() {
    number=$1
    echo "Multiplication table of $number is:"

    for i in {1..10}; do
        result=$(( number * i ))
        echo "$number x $i = $result"
    done
}

# Prompt user to enter a number
read -p "Enter a number : " num

# Call both functions with the entered number
sum_of_digits $num
multiplication_table $num
