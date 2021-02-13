#include <iostream>
#include <climits>

// TODO:->Fazer o nosso codigo
// TODO:->Fazer leitura das instancias
// TODO:->Fazer uma estrutura de arvore
// TODO:->Escrever numa string a ordem dos parenteses

// TODO:->Fazer o algoritmo comparativo
// TODO:->executar os testes
// TODO:->finalizar o relatorio


int main (int argc, char* argv[]){


    int mats[4] = {1, 2, 3, 4}

    int n = 5;
    int p[] = {5, 4, 6, 2, 7};
    int m[5][5] = {0};
    int s[5][5] = {0};

    int j, min, q;

    for(int d = 1; d < n-1; d++){
        for(int i = 1; i < n-d; i++){
            j = i + d;
            min = INT_MAX;

            for (int k = i; k <= j-1; k++){
                q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                
                if(q < min){
                    min = q;
                    s[i][j] = k;
                }
            }

            m[i][j] = min;
        }
    }

    std::cout << m[1][n-1];

    for(int h = 0; h < n; h++){
        std::cout << std::endl;
        for(int g = 0; g < n; g++){
            std::cout << s[h][g] << " ";
        }
    }



    return 0;
}