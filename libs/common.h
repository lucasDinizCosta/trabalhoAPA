#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <climits>
#include <string>
#include <cmath>
#include "node.h"


extern int **opMatriz;
extern int **locParentesis;

/*INPUT: Endereço da matriz de memoização, Endereço da matriz que armazena aonde os parentesis serão colocados, tamanho das matrizes a ser alocado
OUTPUT: Nenhum
DESCRIP: Aloca dinamicamente as posições das matrizes passadas por parâmetro*/
void initMatrixes(int size);

/*INPUT: Nome do arquivo a ser lido, vetor com as dimensões das matrizes, o tamanho desse vetor
OUTPUT: Retorna se o arquivo foi lido com sucesso ou não
DESCRIP: Lê o arquivo com as dimensões das matrizes passadas por parâmetro*/
bool readFile(char* fileName, std::vector<int> &dimensions, int* n);

/*INPUT: Endereço da matriz de memoização, endereço do vetor com as dimensoões, tamanho desse vetor
OUTPUT: Numero de operacoes de uma solucao otima
DESCRIP: Retorna o numero de operacoes de uma solução otima utilizando 
um algoritmo de forca bruta recursivo*/
int recursiveAlgo(std::vector<int> &dimensions, int i, int j);

/*INPUT: Endereço da matriz de memoização, Endereço da matriz que armazena aonde os parentesis serão colocados,
vetor com as dimensões das matrizes e o tamanho desse vetor
OUTPUT: Numero de operacoes de uma solucao otima
DESCRIP: Retorna o numero de operacoes de uma solução otima utilizando 
um algoritmo de progamacao dinamica*/
int dynamicAlgo(std::vector<int> &dimensions, int n);


/*INPUT: Numero de iteracoes de teste para cada instancia, tamanho da instancia, qual algoritmo foi usado, 
numero de operacoes da solucao otima, tempo medio gasto nas iteracoes, memoria media gasta nas iteracoes
OUTPUT: Nenhum
DESCRIP: Grava em um arquivo csv as informacoes do teste para a instancia passada*/
void resultsToCSV(int numIterations, int instanceSize, std::string algorithm, int numberOfOp, long long int timeSpent, double memorySpent);

/*INPUT: Numero de iteracoes de teste para cada instancia, tamanho da instancia, qual algoritmo foi usado, 
numero de operacoes da solucao otima, tempo medio gasto nas iteracoes, memoria media gasta nas iteracoes
OUTPUT: Nenhum
DESCRIP: Printa na tela informacoes do teste para a instancia passada*/
void printResults(int numIterations, int instanceSize, std::string algorithm, int numberOfOp, long long int timeSpent, double memorySpent);


void delTree(Node* root);
Node* free(Node* p);
void buildTree( Node* node, int numLeaves, int size);
void writeSolution( int size);


/*INPUT:
OUTPUT: 
DESCRIP: Gera um arquivo csv com as dimensões das matrizes geradas aleatoriamente entre 1 - 61*/
void mostraArvore(Node* a, int b);

/*INPUT:
OUTPUT:
DESCRIP: Gera um arquivo csv com as dimensões das matrizes geradas aleatoriamente entre 1 - 61*/
// Função auxiliar de impressão da árvore.
// Recebe como parametro uma string com o que deve ser impresso
// e um valor inteiro b, que é responsável por aplicar um espaçamento de impressão
void imprimeNo(std::string msg, int b);

#endif //COMMON_H_INCLUDED