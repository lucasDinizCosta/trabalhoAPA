#!/bin/bash

echo "method;numIt;instanceSize;avgNumOp;avgTime;avgMem;" >> ./results/dynamic.csv

for f in ./instancias/bruteForce/*.csv; do
	echo "Achou arquivo" + "$f"
done
