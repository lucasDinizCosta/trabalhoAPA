#include "libs/common.h"
#include <queue>

void initMatrixes(int size) {

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

bool readFile(char *fileName, int *n) {
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


void delTree(Node *root) {
     root = free(root);
}

Node *free(Node *p) {

     if (p != NULL) {
          p->setLeft(free(p->getLeft()));
          p->setRight(free(p->getRight()));
          delete p;
          p = NULL;
     }

     return NULL;
}

void buildTree(Node *node, int numLeaves, int size) {

     if (node == NULL)
          return;

     Node *aux = node;
     int i = aux->getStart();
     int j = aux->getEnd();
     int value;

     if (numLeaves != size) {
          if (i != j) {
               value = locParentesis[i][j];

               aux->setLeft(new Node(aux->getStart(), value, aux));
               aux->setRight(new Node(value + 1, aux->getEnd(), aux));
          } else {
               aux->setIsLeaf(true);
               numLeaves++;
          }

          buildTree(aux->getLeft(), numLeaves, size);
          buildTree(aux->getRight(), numLeaves, size);
     }
}


void writeSolutionTree(int size) {

     solFile.open("solution.txt", std::ios_base::trunc);


     int i = 1;
     int j = size;
     int numLeaves = 0;

     Node *root = new Node(i, j, true);
     buildTree(root, numLeaves, size);

     std::vector<Node *> v; //Vetor que armazena os nos
     int it = 0;
     std::queue<Node *> q; //Fila para percorrer a arvore em largura
     q.push(root);
     int level = 0;

     //Busca em largura na arvore
     while (q.size() > 0) {
          Node *n = q.front();
          v.push_back(n);
          q.pop();

          if (level == v[it]->getLevel()) {
               std::string valNode = std::to_string(n->getStart()) + "-" + std::to_string(n->getEnd());
               solFile << ", " << valNode << "(" << std::to_string(n->getLevel()) << ")"
                         << " ";
          } else {
               solFile << std::endl;
               std::string valNode = std::to_string(n->getStart()) + "-" + std::to_string(n->getEnd());
               solFile << valNode << "(" << std::to_string(n->getLevel()) << ")"
                         << " ";
               level += 1;
          }

          it++;

          if (n->getLeft() != nullptr) {
               q.push(n->getLeft());
          }
          if (n->getRight() != nullptr) {
               q.push(n->getRight());
          }
     }

     solFile << std::endl;
     delTree(root);
}

int recursiveAlgo(int i, int j) {

     int q1;
     int q2;
     int q;

     //Se for a diagonal principal retorna 0
     if (i == j)
          return 0;

     opMatriz[i][j] = INT_MAX;
     
     //Para cada valor de k entre i e j-1
     //Chama recursivamente a funcao para os dois
     //subproblemas divididos em i ate k e k+1 ate j.
     for (int k = i; k <= j - 1; k++) {

          q1 = recursiveAlgo(i, k);
          q2 = recursiveAlgo(k + 1, j);
          q = q1 + q2 + dimensions[i - 1] * dimensions[k] * dimensions[j] ;

          //Testa se eh menor que o valor ja armazenado nessa posicao
          if (q < opMatriz[i][j]) {

               //Atualiza o valor da matriz em i,j
               opMatriz[i][j] = q;

               //Registra o k, para construir a solucao depois
               locParentesis[i][j] = k;
          }
     }

     //Retorna o valor minimo de operacoes de multiplicaçao
     //entre i e j
     return opMatriz[i][j];
}

int dynamicAlgo(int n) {


     int j, min, q;

     for (int d = 1; d < n - 1; d++) { //Para conseguir percorrer na diagonal de cima para baixo
          for (int i = 1; i < n - d; i++) { //Identifica a linha atual
               j = i + d; //Valor ajustado de j, para ficar na diagonal certa
               min = INT_MAX;

               for (int k = i; k <= j - 1; k++) { //Percorrer os valores possíveis de k entre i e j-1

                    //Recebe o numero das operaçoes de multiplicaçao entre os dois subproblemas armazenados na matriz
                    //de memoizacao opMatriz,  opMatriz[i][k], opMatriz[k + 1][j] + a multiplicacao entre as duas
                    q = opMatriz[i][k] + opMatriz[k + 1][j] + dimensions[i - 1] * dimensions[k] * dimensions[j];

                    //Testa se eh menor que o valor ja armazenado nessa posicao
                    if (q < min) {
                         min = q;

                         //Registra o k, para construir a solucao depois
                         locParentesis[i][j] = k;
                    }
               }

               //Atualiza o valor da matriz em i,j
               opMatriz[i][j] = min;
          }
     }
     
     //Retorna a ultima ponta superior direita da matriz
     //Onde consta o numero minimo de operacoes de multiplicacao
     //entre 1 e n-1, que eh igual a 1 ate o tamanho da instancia
     return opMatriz[1][n - 1];
}

void resultsToCSV(int numIterations, int instanceSize, std::string algorithm, int numberOfOp, long long int timeSpent, double memorySpent) {
     double averageNumOp = numberOfOp / numIterations;
     double averageTimeSpent = ((double)timeSpent / numIterations) / pow(10, 9);
     double averageMemSpent = memorySpent / numIterations;

     std::cout << algorithm.c_str() << ";" << std::to_string(numIterations) << ";" << std::to_string(instanceSize) << ";"
               << std::to_string(averageNumOp) << ";" << std::to_string(averageTimeSpent) << ";" << std::to_string(averageMemSpent) << ";" << std::endl;
}

void printResults(int numIterations, int instanceSize, std::string algorithm, int numberOfOp, long long int timeSpent, double memorySpent) {
     double averageNumOp = numberOfOp / numIterations;
     double averageTimeSpent = ((double)timeSpent / numIterations) / pow(10, 9);
     double averageMemSpent = memorySpent / numIterations;

     std::cout << "\nMethod: " << algorithm.c_str() << std::endl;
     std::cout << "Number of Iterations: " << std::to_string(numIterations) << std::endl;
     std::cout << "Instance Size: " << std::to_string(instanceSize) << std::endl;
     std::cout << "Average Number of Operations: " << std::to_string(averageNumOp) << std::endl;
     std::cout << "Average Time Spent: " << std::to_string(averageTimeSpent) << std::endl;
     std::cout << "Average Memory Spent: " << std::to_string(averageMemSpent) << "\n"
               << std::endl;
}

void writeSolutionParentesis(int i, int j){


          if (i == j)
               solFile << "M" << i;
          else{
               solFile << "(";
               writeSolutionParentesis(i, locParentesis[i][j]);
               writeSolutionParentesis(locParentesis[i][j] + 1 , j);
               solFile << ")";
          }
          
}
 