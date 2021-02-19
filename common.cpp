#include "common.h"

#include <fstream>
#include <iostream>
#include <queue>
#include <string>

void initMatrixes(int **&opMatriz, int **&locParentesis, int size) {
     opMatriz = new int *[size];

     for (int i = 0; i < size; i++)
          opMatriz[i] = new int[size];

     locParentesis = new int *[size];

     for (int i = 0; i < size; i++)
          locParentesis[i] = new int[size];

     for (int i = 0; i < size; i++) {
          for (int j = 0; j < size; j++) {
               opMatriz[i][j] = 0;
               locParentesis[i][j] = 0;
          }
     }
}

bool readFile(char *fileName, std::vector<int> &dimensions, int *n) {
     //std::cout << "File name: " << fileName << std::endl;

     std::ifstream instance;
     instance.open(fileName);

     if (instance.is_open()) {
          std::string buffer;

          //Primeira linha
          getline(instance, buffer, ',');
          dimensions.push_back(stoi(buffer));
          getline(instance, buffer, '\n');
          dimensions.push_back(stoi(buffer));

          while (!instance.eof()) {
               //Pula o primeiro atributo
               getline(instance, buffer, ',');
               getline(instance, buffer, '\n');
               dimensions.push_back(stoi(buffer));
          }
     } else {
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
     for (int i = 0; i < b; i++) {
          printf("   ");
     }

     std::cout << msg << std::endl;
}

// Função recursiva para percorrer a árvore binária.
void mostraArvore(Node *a, int b) {
     if (a == NULL) {
          return;
     }

     std::string valNode = std::to_string(a->getStart()) + "-" + std::to_string(a->getEnd());
     std::cout << valNode << " ";

     mostraArvore(a->getRight(), b + 1);

     //imprimeNo(valNode, b);

     mostraArvore(a->getLeft(), b + 1);
}

void buscaLargura() {
     // std::queue<Node*> q;
     // q.push(raiz_);

     // while (q.size() > 0)
     // {
     //     no* n = q.front();
     //     q.pop();
     //     std::cout << n->v << " ";

     //     if (n->esquerda !=nullptr) {
     //             q.push(n->esquerda);
     //     }
     //     if (n->direita !=nullptr) {
     //         q.push(n->direita);
     //     }
     // }

     // std::cout << std::endl;
}

// Instancia uma nova árvore
void exemplo_arvore() {
     Node *root = new Node(1, 4);

     root->setLeft(new Node(1, 3));

     root->setRight(new Node(4, 4));

     Node *aux = new Node();

     aux = root->getLeft();

     aux->setLeft(new Node(1, 1));

     aux->setRight(new Node(2, 3));

     aux = aux->getRight();

     aux->setLeft(new Node(2, 2));

     aux->setRight(new Node(3, 3));

     std::cout << "\n\nImpressao da Arvore (de lado):" << std::endl
               << std::endl;

     std::queue<Node *> q;
     q.push(root);
     int level = 0;

     while (q.size() > 0) {
          Node *n = q.front();
          q.pop();
          std::string valNode = std::to_string(n->getStart()) + "-" + std::to_string(n->getEnd());
          std::cout << valNode << " ";

          if (n->getLeft() != nullptr) {
               q.push(n->getLeft());
          }
          if (n->getRight() != nullptr) {
               q.push(n->getRight());
          }
     }

     std::cout << std::endl;

     //mostraArvore(root, 0);
}

int recursiveAlgo(int **&opMatriz, std::vector<int> &p, int i, int j) {
     int q1;
     int q2;
     int q;

     if (i == j)
          return 0;

     opMatriz[i][j] = INT_MAX;

     for (int k = i; k <= j - 1; k++) {
          q1 = recursiveAlgo(opMatriz, p, i, k);
          q2 = recursiveAlgo(opMatriz, p, k + 1, j);
          q = q1 + p[i - 1] * p[k] * p[j] + q2;

          if (q < opMatriz[i][j])
               opMatriz[i][j] = q;
     }

     return opMatriz[i][j];
}

void resultsToCSV(int numIterations, int instanceSize, std::string algorithm, int numberOfOp, std::chrono::duration<double> timeSpent, double memorySpent) {
     double averageNumOp = numberOfOp / numIterations;
     double averageTimeSpent = timeSpent.count() / numIterations;
     double averageMemSpent = memorySpent / numIterations;

     std::cout << algorithm.c_str() << ";" << std::to_string(numIterations) << ";" << std::to_string(instanceSize) << ";"
               << std::to_string(averageNumOp) << ";" << std::to_string(averageTimeSpent) << ";" << std::to_string(averageMemSpent) << ";" << std::endl;
}

void printResults(int numIterations, int instanceSize, std::string algorithm, int numberOfOp, std::chrono::duration<double> timeSpent, double memorySpent) {
     double averageNumOp = numberOfOp / numIterations;
     double averageTimeSpent = timeSpent.count() / numIterations;
     double averageMemSpent = memorySpent / numIterations;

     std::cout << "\nMethod: " << algorithm.c_str() << std::endl;
     std::cout << "Number of Iterations: " << std::to_string(numIterations) << std::endl;
     std::cout << "Instance Size: " << std::to_string(instanceSize) << std::endl;
     std::cout << "Average Number of Operations: " << std::to_string(averageNumOp) << std::endl;
     std::cout << "Average Time Spent: " << std::to_string(averageTimeSpent) << std::endl;
     std::cout << "Average Memory Spent: " << std::to_string(averageMemSpent) << "\n" << std::endl;
}