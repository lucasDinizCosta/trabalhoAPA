#include <iostream>
#include <climits>
#include <string>
#include "node.h"

// TODO:->Fazer o nosso codigo
// TODO:->Fazer leitura das instancias
// TODO:->Fazer uma estrutura de arvore
// TODO:->Escrever numa string a ordem dos parenteses

// TODO:->Fazer o algoritmo comparativo
// TODO:->executar os testes
// TODO:->finalizar o relatorio 

void imprimeNo(std::string msg, int b) {

    for (int i = 0; i < b; i++){
        printf("   ");
    }

    std::cout << msg << std::endl;
}

void mostraArvore(Node* a, int b) {

    if (a == NULL) {
        imprimeNo("*", b);
        return;
    }

    mostraArvore(a->getRight(), b+1);

    std::string valNode = std::to_string(a->getStart()) + "-" + std::to_string(a->getEnd());

    imprimeNo(valNode, b);
    
    mostraArvore(a->getLeft(), b+1);
}

void exemplo_arvore(){

    Node* root = new Node(1, 4);

    Node* lf = new Node(1, 2);

    Node* rt = new Node(3, 3);

    root->setLeft(lf);

    root->setRight(rt);

    std::cout  << "\n\nImpressão da Árvore (de lado):" << std::endl   << std::endl;

    mostraArvore(root, 0);
}

int main (int argc, char* argv[]){

    int mats[4] = {1, 2, 3, 4};

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

    // Exemplo para instanciar uma arvore e imprimi-la
    exemplo_arvore();

    return 0;
}