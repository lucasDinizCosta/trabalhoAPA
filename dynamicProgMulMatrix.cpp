#include <iostream>
#include <climits>
#include <string>
#include <chrono>
#include "common.h"

// TODO:->Fazer o nosso codigo
// TODO:->Fazer leitura das instancias - OK
// TODO:->Fazer uma estrutura de arvore - OK
// TODO:->Escrever numa string a ordem dos parenteses

// TODO:->Fazer o algoritmo comparativo
// TODO:->executar os testes
// TODO:->finalizar o relatorio


void bruteForce(std::vector<int> dimensions){
    int minOperation = INT_MAX;
    int totalOperations = 0;
    int operationsNow = 0;
    int index = 0;

    std::cout << "\n----- EXECUTING BRUTE FORCE -----" << std::endl;
    while(dimensions.size() > 2){
        for (int i = 1; i < dimensions.size() - 1; i++)
        {
            operationsNow = dimensions[i - 1] * dimensions[i] * dimensions[i + 1];
            if(operationsNow < minOperation){
                minOperation = operationsNow;
                index = i;
            }
        }
        dimensions.erase(dimensions.begin()+index);
        totalOperations = totalOperations + minOperation;
        minOperation = INT_MAX;
    }
    
    std::cout << "Total Operations: " << totalOperations << std::endl;
}

int main (int argc, char* argv[]){


    if(argc > 1){

        std::vector<int> dimensions;
        int **opMatriz;
        int **locParentesis;
        int n;

        bool wasRead = readFile(argv[1], dimensions, &n);

        if(wasRead){

            initMatrixes(opMatriz, locParentesis, n);

            int j, min, q;

            clock_t tStart = clock();
            auto start = std::chrono::steady_clock::now();

            for(int d = 1; d < n-1; d++){
                for(int i = 1; i < n-d; i++){
                    j = i + d;
                    min = INT_MAX;

                    for (int k = i; k <= j-1; k++){
                        q = opMatriz[i][k] + opMatriz[k+1][j] + dimensions[i-1]*dimensions[k]*dimensions[j];

                        if(q < min){
                            min = q;
                            locParentesis[i][j] = k;
                        }
                    }

                    opMatriz[i][j] = min;
                }
            }
            
            auto end = std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;

            std::cout << "Number of operations = " << opMatriz[1][n-1] << std::endl;
            std::cout << "Time taken (chrono): " << elapsed_seconds.count() << std::endl;

            // for(int h = 0; h < n; h++){
            //     std::cout << std::endl;
            //     for(int g = 0; g < n; g++){
            //         std::cout << opMatriz[h][g] << " ";
            //     }
            // }

            // // Exemplo para instanciar uma arvore e imprimi-la
            // exemplo_arvore();


            for(int i = 0; i < n; i++){
                delete [] opMatriz[i];
                delete [] locParentesis[i];
            }
            delete [] opMatriz;
            delete [] locParentesis;
        }
        

        std::cout << "\nDimensions: ";
        for (int i = 0; i < dimensions.size(); i++)
        {
            std::cout << dimensions[i] << " - ";
        }
        std::cout << std::endl;

        bruteForce(dimensions);

    }
    return 0;
}

