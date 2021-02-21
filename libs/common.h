#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <chrono>
#include <climits>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "node.h"

///Variaveis globais instanciadas globalmente no arquivo ../dynamicProgMulMatrixes.cpp
extern int** opMatriz;
extern int** locParentesis;
extern std::vector<int> dimensions;
extern std::ofstream solFile;

/*Estrutura que configura o relogio para podermos medir o tempo de acordo com
a funcao desejada (segundo, milisegundo, microsegundo, nanosegundo)
*/
struct stop_watch final {
     //Starta o relogio
     stop_watch() : Start_(now()) {}

     std::chrono::seconds elapsed_s() const {  //Metodo para medir o tempo em segundos
          using std::chrono::seconds;
          return std::chrono::duration_cast<seconds>(elapsed());
     }

     std::chrono::milliseconds elapsed_ms() const {  //Metodo para medir o tempo em milisegundos
          using std::chrono::milliseconds;
          return std::chrono::duration_cast<milliseconds>(elapsed());
     }

     std::chrono::microseconds elapsed_us() const {  //Metodo para medir o tempo em microsegundos
          using std::chrono::microseconds;
          return std::chrono::duration_cast<microseconds>(elapsed());
     }

     std::chrono::nanoseconds elapsed_ns() const {  //Metodo para medir o tempo em nanosegundos
          using std::chrono::nanoseconds;
          return std::chrono::duration_cast<nanoseconds>(elapsed());
     }

     void restart() { Start_ = now(); }  // Restarta o relogio

     //Desaloca a memoria usada pelo relogio
     stop_watch(const stop_watch&) = delete;
     stop_watch& operator=(const stop_watch&) = delete;

    private:
     
     //Retorna o tempo atual
     static std::chrono::high_resolution_clock::time_point now() {
          return std::chrono::high_resolution_clock::now();
     }
     
     //Conta usando a configuracao padrao
     std::chrono::duration<double> elapsed() const {
          return (now() - Start_);
     }
     
     //Comeco do relogio
     std::chrono::high_resolution_clock::time_point Start_;
};

/*INPUT: O tamanho das matrizes de memoização e localização dos parenteses
OUTPUT: Nenhum
DESCRIP: Aloca dinamicamente as posições das matrizes passadas por parâmetro*/
void initMatrixes(int size);

/*INPUT: Nome do arquivo a ser lido, o tamanho das matrizes
OUTPUT: Retorna se o arquivo foi lido com sucesso ou não
DESCRIP: Lê o arquivo com as dimensões das matrizes passadas por parâmetro*/
bool readFile(char* fileName, int* n);

/*INPUT: Numero da primeira matriz, numero da segunda matriz
OUTPUT: Numero de operacoes de uma solucao otima
DESCRIP: Retorna o numero de operacoes de uma solução otima utilizando 
um algoritmo de forca bruta recursivo*/
int recursiveAlgo(int i, int j);

/*INPUT: O tamanho das matrizes de memoização e localização dos parenteses
OUTPUT: Numero de operacoes de uma solucao otima
DESCRIP: Retorna o numero de operacoes de uma solução otima utilizando 
um algoritmo de progamacao dinamica*/
int dynamicAlgo(int n);

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

/*INPUT: Raiz da arvore
OUTPUT: Nenhum
DESCRIP: Desaloca o espaco usado pela arvore*/
void delTree(Node* root);

/*INPUT: No da arvore
OUTPUT: No sempre valendo NULL
DESCRIP: Desaloca o espaco ocupado por um no*/
Node* free(Node* p);

/*INPUT: No a ser criado, numero de folhas, tamanho da instancia
OUTPUT: Nenhum
DESCRIP: Cria no da arvore com os limites Start e End corretos para printar a solucao a posteriori*/
void buildTree(Node* node, int numLeaves, int size);

/*INPUT: Tamanho da instancia
OUTPUT: Nenhum
DESCRIP: Escreve solucao em arvore no arquivo solution.txt*/
void writeSolutionTree(int size);

/*INPUT: Indice da primeira matriz, tamanho da instancia
OUTPUT: 
DESCRIP: Printa a cadeia de matrizes parentizada da solucao otima*/
void writeSolutionParentesis(int i, int size);

#endif  //COMMON_H_INCLUDED