#!/bin/bash

# Compile

g++ common.cpp node.cpp dynamicProgMulMatrix.cpp -o complileLinux

# Run

./complileLinux instancias/dynamicProgramming/matrixes-500.csv 2 1
