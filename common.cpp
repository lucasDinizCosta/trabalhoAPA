#include <iostream>
#include <fstream>
#include "common.h"

void initMatrixes( int** &opMatriz, int** &locParentesis, int size){

    opMatriz = new int*[size];

    for(int i = 0; i < size; i++)
        opMatriz[i] = new int[size];

    locParentesis = new int*[size];

    for(int i = 0; i < size; i++)
        locParentesis[i] = new int[size];

    for(int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            opMatriz[i][j] = 0;
            locParentesis[i][j] = 0;
        }
        
    }
}

bool readFile(char* fileName, std::vector<int> &dimensions, int* n){

    std::cout << "File name: " << fileName << std::endl;

    std::ifstream instance;
    instance.open(fileName);

    if(instance.is_open()){

        std::string buffer;

        //Primeira linha
        getline(instance, buffer, ',');
        dimensions.push_back(stoi(buffer));
        getline(instance, buffer, '\n');
        dimensions.push_back(stoi(buffer));

        while(!instance.eof()){
            //Pula o primeiro atributo
            getline(instance, buffer, ',');
            getline(instance, buffer, '\n');
            dimensions.push_back(stoi(buffer));    
        }

    }else{
        std::cout << "Algo errado em abrir o arquivo !" << std::endl;
        return false;
    }

    *n = dimensions.size();
    

    instance.close();
    return true;
}

// Função auxiliar de impressão da árvore.
// Recebe como parametro uma string com o que deve ser impresso
// e um valor inteiro b, que é responsável por aplicar um espaçamento de impressão
void imprimeNo(std::string msg, int b) {

    for (int i = 0; i < b; i++){
        printf("   ");
    }

    std::cout << msg << std::endl;
}

// Função recursiva para percorrer a árvore binária.
void mostraArvore(Node* a, int b) {

    if (a == NULL) {
        return;
    }

    mostraArvore(a->getRight(), b+1);

    std::string valNode = std::to_string(a->getStart()) + "-" + std::to_string(a->getEnd());

    imprimeNo(valNode, b);

    mostraArvore(a->getLeft(), b+1);
}

// Instancia uma nova árvore
void exemplo_arvore(){

    Node* root = new Node(1, 4);

    root->setLeft(new Node(1, 3));

    root->setRight(new Node(4, 4));

    Node* aux = new Node();

    aux = root->getLeft();

    aux->setLeft(new Node(1, 1));

    aux->setRight(new Node(2, 3));

    aux = aux->getRight();

    aux->setLeft(new Node(2, 2));

    aux->setRight(new Node(3, 3));

    std::cout  << "\n\nImpressao da Arvore (de lado):" << std::endl   << std::endl;

    mostraArvore(root, 0);
}