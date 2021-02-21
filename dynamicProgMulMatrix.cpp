#include "libs/common.h"
//#include <unistd.h> (Apenas no Linux)

// TODO:->Documentar tudo e comentar os codigos


// // Funcao Auxiliar para Calcular Memória Utilizada (Apenas no Linux)
// void process_mem_usage(double &vm_usage, double &resident_set) {
//      vm_usage = 0.0;
//      resident_set = 0.0;

//      // the two fields we want
//      unsigned long vsize;
//      long rss;
//      {
//           std::string ignore;
//           std::ifstream ifs("/proc/self/stat", std::ios_base::in);
//           ifs >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> vsize >> rss;
//      }

//      long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024;  // in case x86-64 is configured to use 2MB pages
//      vm_usage = vsize / 1024.0;
//      resident_set = rss * page_size_kb;
// }


///Variáveis globais das estruturas em comum
int **opMatriz; //Matriz de memoizacao
int **locParentesis; //Matriz que guarda a posição dos parenteses para montar a solucao a posteriori
std::vector<int> dimensions; //Vetor que armazena as dimensoes das matrizes, desconsiderando a segunda aparicao da dimensao em comum entre duas matrizes consecutivas
std::ofstream solFile; //Arquivo de solucao

int main(int argc, char *argv[]) {

     //double vmInit, rssInit;              // Armazena a memória utilizada ao inicio da execucao
     //double vmEnd, rssEnd;                // Armazena a memória utilizada ao final da execucao
     //process_mem_usage(vmInit, rssInit);  // Calcula a memoria utilizada e seta no inicio Only in linux

     
     int n;

     int numIterations = 5;
     int instanceSize = 0;
     std::string algorithm = "";
     int meanNumberOfOp = 0;
     long long int timeSpent = 0;
     double memorySpent = 0.0;

     if (argc < 4) {
          std::cout << "\n- Error: Arguments missing!" << std::endl;

          std::cout << "\n- Use the following pattern to run the program properly on Windows:" << std::endl;

          std::cout << "\n.\\dynamicProgMulMatrix.exe <path_to_instance_file> <algorithm_code> <print_type> <print_sol>" << std::endl;

          std::cout << "\nWhere:" << std::endl;

          std::cout << " - Algorithm Code: use 1 for Recursive Solution and 2 for Dynamic Programming." << std::endl;
          std::cout << " - Print Type: use 1 for easy terminal reading and 2 for csv output file formatting" << std::endl;
          std::cout << " - Print sol: use 1 to write the solution into a file" << std::endl;

          return 0;
     }

     if (argc > 1) {

          
          bool wasRead = readFile(argv[1], &n);
          
          //Verifica se o arquivo foi lido corretamente
          if (wasRead) {
               
               //Inicia as matrizes de operacao e posicao dos parenteses
               initMatrixes(n);
               std::string str(argv[2]);

               if (str == "1") {
                    //std::cout << "\nRunning Recursive tests, please wait... \n" << std::endl;

                    algorithm = "Recursive Solution";
                    instanceSize = dimensions.size() - 1;

                    for (int i = 0; i < numIterations; i++) {

                         stop_watch sw;

                         int numOps = recursiveAlgo(1, n - 1); //Execura o algoritmo

                         auto m = sw.elapsed_ns().count();

                         meanNumberOfOp += numOps;
                         timeSpent += m;
                         memorySpent += 0.0;
                    }

               }

               else if (str == "2") {
                    // std::cout << "\nRunning dynamic programming tests, please wait...\n" << std::endl;

                    algorithm = "Dynamic Programming";
                    instanceSize = dimensions.size() - 1;

                    for (int i = 0; i < numIterations; i++) {

                         stop_watch sw;
                         
                         int numOps = dynamicAlgo(n); //Execura o algoritmo

                         auto m = sw.elapsed_ns().count();

                         meanNumberOfOp += numOps;
                         timeSpent += m;
                         memorySpent += 0.0;
                    }
               }

               // process_mem_usage(vmEnd, rssEnd);  // Calcula a memoria utilizada e seta no final Only in linux
               // memorySpent = rssEnd - rssInit;    // Calcula a dif de memoria entre o final e no inicio

               if(argc == 5 && std::string(argv[4]) == "1"){
                    writeSolutionTree(instanceSize);
                    writeSolutionParentesis(1, instanceSize);
                    solFile.close();
               }

               for (int i = 0; i < n; i++) {
                    delete[] opMatriz[i];
                    delete[] locParentesis[i];
               }
               delete[] opMatriz;
               delete[] locParentesis;
          }

          
          if (std::string(argv[3]) == "1") {
               printResults(numIterations, instanceSize, algorithm, meanNumberOfOp, timeSpent, memorySpent);
          } else if (std::string(argv[3]) == "2") {
               resultsToCSV(numIterations, instanceSize, algorithm, meanNumberOfOp, timeSpent, memorySpent);
          } else
               std::cout << "No valid output method choosed. Please, check arguments." << std::endl;
     }         

     return 0;
}