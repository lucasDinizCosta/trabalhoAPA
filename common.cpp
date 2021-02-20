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

void delTree(Node* root){

     root = free(root);

}

// Função recursiva para percorrer a árvore binária.
Node* free(Node *p) {
     
     if (p != NULL)
     {
          p->setLeft( free(p->getLeft()) );
          p->setRight( free(p->getRight()) );
          delete p;
          p = NULL;
     }
     
     return NULL;
}


void buildTree(Node* node, int numLeaves, int size){

     if(node == NULL)
          return;
     
     Node* aux = node;
     int i = aux->getStart();
     int j = aux->getEnd();
     int value;


     if (numLeaves != size){
     
          if (i != j){

               value = locParentesis[i][j];

               aux->setLeft(new Node(aux->getStart(), value, aux));
               aux->setRight(new Node(value + 1, aux->getEnd(), aux));

          }else{
               aux->setIsLeaf(true);
               numLeaves++;
          }

          buildTree(aux->getLeft(), numLeaves, size);
          buildTree(aux->getRight(), numLeaves, size);
     }
}

// Instancia uma nova árvore
void writeSolution(int size) {

     int i = 1;
     int j = size;
     int numLeaves = 0;

     Node *root = new Node(i, j, true);
     buildTree(root, numLeaves, size);


     std::vector<Node *> v;
     int it = 0;
     std::queue<Node *> q;
     q.push(root);
     int level = 0;

     while (q.size() > 0) {
          Node *n = q.front();
          v.push_back(n);
          q.pop();

          if(level == v[it]->getLevel()){
               std::string valNode = std::to_string(n->getStart()) + "-" + std::to_string(n->getEnd());
               std::cout << ", " << valNode << "(" << std::to_string(n->getLevel()) << ")" << " ";
          }else{
               std::cout << std::endl;
               std::string valNode = std::to_string(n->getStart()) + "-" + std::to_string(n->getEnd());
               std::cout << valNode << "(" << std::to_string(n->getLevel()) << ")" << " ";
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


     delTree(root);
}

int recursiveAlgo(std::vector<int> &p, int i, int j) {
     int q1;
     int q2;
     int q;

     if (i == j)
          return 0;

     opMatriz[i][j] = INT_MAX;

     for (int k = i; k <= j - 1; k++) {
          q1 = recursiveAlgo(p, i, k);
          q2 = recursiveAlgo(p, k + 1, j);
          q = q1 + p[i - 1] * p[k] * p[j] + q2;

          if (q < opMatriz[i][j]){
               opMatriz[i][j] = q;
               locParentesis[i][j] = k;
          }
     }

     return opMatriz[i][j];
}

void resultsToCSV(int numIterations, int instanceSize, std::string algorithm, int numberOfOp, long long int timeSpent, double memorySpent) {
     double averageNumOp = numberOfOp / numIterations;
     double averageTimeSpent = ((double)timeSpent / numIterations)/pow(10, 9);
     double averageMemSpent = memorySpent / numIterations;

     std::cout << algorithm.c_str() << ";" << std::to_string(numIterations) << ";" << std::to_string(instanceSize) << ";"
               << std::to_string(averageNumOp) << ";" << std::to_string(averageTimeSpent) << ";" << std::to_string(averageMemSpent) << ";" << std::endl;
}

void printResults(int numIterations, int instanceSize, std::string algorithm, int numberOfOp, long long int timeSpent, double memorySpent) {
     double averageNumOp = numberOfOp / numIterations;
     double averageTimeSpent = ((double)timeSpent / numIterations)/pow(10, 9);
     double averageMemSpent = memorySpent / numIterations;

     std::cout << "\nMethod: " << algorithm.c_str() << std::endl;
     std::cout << "Number of Iterations: " << std::to_string(numIterations) << std::endl;
     std::cout << "Instance Size: " << std::to_string(instanceSize) << std::endl;
     std::cout << "Average Number of Operations: " << std::to_string(averageNumOp) << std::endl;
     std::cout << "Average Time Spent: " << std::to_string(averageTimeSpent) << std::endl;
     std::cout << "Average Memory Spent: " << std::to_string(averageMemSpent) << "\n" << std::endl;
}