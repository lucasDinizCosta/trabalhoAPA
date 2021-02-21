#!/bin/bash

g++ ../common.cpp ../node.cpp ../dynamicProgMulMatrix.cpp -o batchCompiled

echo "method;numIt;instanceSize;avgNumOp;avgTime;avgMem;" >> ../results/recursiveSolution.csv

for f in ../instancias/recursiveSolution/*.csv; do
        echo "Executando Testes para o arquivo" "$f" "..."
        ./batchCompiled $f 1 2 >> ../results/recursiveSolution.csv
done

echo "method;numIt;instanceSize;avgNumOp;avgTime;avgMem;" >> ../results/dynamic.csv

for f in ../instancias/dynamicProgramming/*.csv; do
        echo "Executando Testes para o arquivo" "$f" "..."
        ./batchCompiled $f 2 2 >> ../results/dynamic.csv
done
