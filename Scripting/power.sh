#!/bin/bash

# Task: Calculate base raised to the power of exponent

power() {
    base=$1
    exp=$2
    result=1

    for (( i = 0; i < exp; i++ )); do
        result=$(( result * base ))
    done

    echo "$base ^ $exp = $result"
}

read -p "Enter base: " b
read -p "Enter exponent: " e
power $b $e
