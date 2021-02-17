#include <iostream>
#include <string>
#include "common.h"

// TODO:->Fazer o nosso codigo
// TODO:->Fazer leitura das instancias - OK
// TODO:->Fazer uma estrutura de arvore - OK
// TODO:->Escrever numa string a ordem dos parenteses

// TODO:->Fazer o algoritmo comparativo
// TODO:->executar os testes
// TODO:->finalizar o relatorio



int main (int argc, char* argv[]){

    std::vector<int> dimensions;
    int **opMatriz;
    int **locParentesis;
    int n;       

    if(argc > 1){

        bool wasRead = readFile(argv[1], dimensions, &n);

        if(wasRead){

            initMatrixes(opMatriz, locParentesis, n);
            std::string str(argv[2]) ;

            if(str == "1"){

                clock_t tStart = clock();
                auto start = std::chrono::steady_clock::now();
    
                int numOps = recursiveAlgo(opMatriz, dimensions, 1, n-1);

                auto end = std::chrono::steady_clock::now();
                std::chrono::duration<double> elapsed_seconds = end-start;
                std::cout << "Number of operations = " << numOps << std::endl;
                std::cout << "Time taken Recursive (chrono): " << elapsed_seconds.count() << std::endl;
            }
                
            else{

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
                std::cout << "Time taken Dynamic (chrono): " << elapsed_seconds.count() << std::endl;
            }



            for(int i = 0; i < n; i++){
                delete [] opMatriz[i];
                delete [] locParentesis[i];
            }
                delete [] opMatriz;
                delete [] locParentesis;
        }

    }

    return 0;
}

