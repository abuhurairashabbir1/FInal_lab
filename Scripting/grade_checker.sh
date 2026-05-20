#!/bin/bash

# Task: Check grade based on marks entered by user

check_grade() {
    marks=$1

    if (( marks >= 90 )); then
        echo "Grade: A"
    elif (( marks >= 80 )); then
        echo "Grade: B"
    elif (( marks >= 70 )); then
        echo "Grade: C"
    elif (( marks >= 60 )); then
        echo "Grade: D"
    else
        echo "Grade: F"
    fi
}

read -p "Enter marks (0-100): " m
check_grade $m
