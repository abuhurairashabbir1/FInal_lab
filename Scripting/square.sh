#!/bin/bash

# Task: Find the square of a number

square() {
    num=$1
    result=$(( num * num ))
    echo "Square of $num = $result"
}

read -p "Enter a number: " n
square $n
