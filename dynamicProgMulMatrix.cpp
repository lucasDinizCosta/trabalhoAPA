#include <chrono>
#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream>
#include <ios>

#include "common.h"

// TODO:->Fazer o nosso codigo
// TODO:->Fazer leitura das instancias - OK
// TODO:->Fazer uma estrutura de arvore - OK
// TODO:->Escrever numa string a ordem dos parenteses

// TODO:->Fazer o algoritmo comparativo
// TODO:->executar os testes
// TODO:->finalizar o relatorio

void mem_usage(double &vm_usage, double &resident_set) {
     vm_usage = 0.0;
     resident_set = 0.0;
     ifstream stat_stream("/proc/self/stat", ios_base::in);  //get info from proc
     directory
         //create some variables to get info
         string pid,
         comm, state, ppid, pgrp, session, tty_nr;
     string tpgid, flags, minflt, cminflt, majflt, cmajflt;
     string utime, stime, cutime, cstime, priority, nice;
     string O, itrealvalue, starttime;
     unsigned long vsize;
     long rss;
     stat_stream >> pid >> comm >> state >> ppid >> pgrp >> session >> tty_nr >> tpgid >> flags >> minflt >> cminflt >> majflt >> cmajflt >> utime >> stime >> cutime >> cstime >> priority >> nice >> O >> itrealvalue >> starttime >> vsize >> rss;  // don't care
     about the rest
         stat_stream.close();
     long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024;  // for x86-64 is configured
     to use 2MB pages
         vm_usage = vsize / 1024.0;
     resident_set = rss * page_size_kb;
}

int main(int argc, char *argv[]) {
     std::vector<int> dimensions;
     int **opMatriz;
     int **locParentesis;
     int n;

     // Global Variables to store test results:
     int numIterations = 5;
     int instanceSize = 0;
     std::string algorithm = "";
     int numberOfOp = 0;
     std::chrono::duration<double> timeSpent;
     double memorySpent = 0.0;

     if (argc < 4) {
          std::cout << "\n- Error: Arguments missing!" << std::endl;

          std::cout << "\n- Use the following pattern to run the program properly on Windows:" << std::endl;

          std::cout << "\n.\\dynamicProgMulMatrix.exe <path_to_instance_file> <algorithm_code> <print_type>" << std::endl;

          std::cout << "\nWhere:" << std::endl;

          std::cout << " - Algorithm Code: use 1 for Brute Force and 2 for Dynamic Programming." << std::endl;
          std::cout << " - Print Type: use 1 for easy terminal reading and 2 for csv output file formatting.\n"
                    << std::endl;

          return 0;
     }

     if (argc > 1) {
          bool wasRead = readFile(argv[1], dimensions, &n);

          if (wasRead) {
               initMatrixes(opMatriz, locParentesis, n);
               std::string str(argv[2]);

               if (str == "1") {
                    //std::cout << "\nRunning brute force tests, please wait... \n" << std::endl;

                    algorithm = "BruteForce";
                    instanceSize = dimensions.size() - 1;

                    clock_t tStart;
                    std::chrono::duration<double> elapsed_seconds;

                    for (int i = 0; i < numIterations; i++) {
                         tStart = clock();
                         auto start = std::chrono::steady_clock::now();

                         int numOps = recursiveAlgo(opMatriz, dimensions, 1, n - 1);

                         auto end = std::chrono::steady_clock::now();
                         elapsed_seconds = end - start;

                         numberOfOp += opMatriz[1][n - 1];
                         timeSpent += elapsed_seconds;
                         memorySpent += 0.0;
                    }

               }

               else if (str == "2") {
                    // std::cout << "\nRunning dynamic programming tests, please wait...\n" << std::endl;

                    algorithm = "Dynamic Programming";
                    instanceSize = dimensions.size() - 1;

                    clock_t tStart;
                    std::chrono::duration<double> elapsed_seconds;

                    for (int i = 0; i < numIterations; i++) {
                         int j, min, q;

                         tStart = clock();
                         auto start = std::chrono::steady_clock::now();

                         for (int d = 1; d < n - 1; d++) {
                              for (int i = 1; i < n - d; i++) {
                                   j = i + d;
                                   min = INT_MAX;

                                   for (int k = i; k <= j - 1; k++) {
                                        q = opMatriz[i][k] + opMatriz[k + 1][j] + dimensions[i - 1] * dimensions[k] * dimensions[j];

                                        if (q < min) {
                                             min = q;
                                             locParentesis[i][j] = k;
                                        }
                                   }

                                   opMatriz[i][j] = min;
                              }
                         }

                         auto end = std::chrono::steady_clock::now();
                         elapsed_seconds = end - start;

                         numberOfOp += opMatriz[1][n - 1];
                         timeSpent += elapsed_seconds;
                         memorySpent += 0.0;
                    }
               }

               for (int i = 0; i < n; i++) {
                    delete[] opMatriz[i];
                    delete[] locParentesis[i];
               }
               delete[] opMatriz;
               delete[] locParentesis;
          }

          if (std::string(argv[3]) == "1") {
               printResults(numIterations, instanceSize, algorithm, numberOfOp, timeSpent, memorySpent);
          } else if (std::string(argv[3]) == "2") {
               resultsToCSV(numIterations, instanceSize, algorithm, numberOfOp, timeSpent, memorySpent);
          } else {
               std::cout << "No valid output method choosed. Please, check arguments." << std::endl;
          }
     }

     return 0;
}
