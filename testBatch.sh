#!/bin/bash

g++ common.cpp node.cpp dynamicProgMulMatrix.cpp -o batchCompiled

echo "method;numIt;instanceSize;avgNumOp;avgTime;avgMem;" >> ./results/bruteForce.csv

for f in ./instancias/bruteForce/*.csv; do
        echo "Executando Testes para o arquivo " "$f" "..."
        ./batchCompiled $f 1 2 >> ./results/bruteForce.csv
done