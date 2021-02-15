#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <vector>
#include "node.h"

void initMatrixes( int** &opMatriz, int** &locParentesis, int size);
bool readFile(char* fileName, std::vector<int> &dimensions, int* n);

// Instancia uma nova árvore
void exemplo_arvore();

// Função recursiva para percorrer a árvore binária.
void mostraArvore(Node* a, int b);

// Função auxiliar de impressão da árvore.
// Recebe como parametro uma string com o que deve ser impresso
// e um valor inteiro b, que é responsável por aplicar um espaçamento de impressão
void imprimeNo(std::string msg, int b);

#endif //COMMON_H_INCLUDED