#include "libs/common.h"

// TODO:->Fazer o nosso codigo
// TODO:->Fazer leitura das instancias - OK
// TODO:->Fazer uma estrutura de arvore - OK
// TODO:->Escrever numa string a ordem dos parenteses

// TODO:->Fazer o algoritmo comparativo
// TODO:->executar os testes
// TODO:->finalizar o relatorio

struct stop_watch final {
     stop_watch() : Start_(now()) {}

     std::chrono::seconds elapsed_s() const {
          using std::chrono::seconds;
          return std::chrono::duration_cast<seconds>(elapsed());
     }

     std::chrono::milliseconds elapsed_ms() const {
          using std::chrono::milliseconds;
          return std::chrono::duration_cast<milliseconds>(elapsed());
     }

     std::chrono::microseconds elapsed_us() const {
          using std::chrono::microseconds;
          return std::chrono::duration_cast<microseconds>(elapsed());
     }

     std::chrono::nanoseconds elapsed_ns() const {
          using std::chrono::nanoseconds;
          return std::chrono::duration_cast<nanoseconds>(elapsed());
     }

     void restart() { Start_ = now(); }

     stop_watch(const stop_watch &) = delete;
     stop_watch &operator=(const stop_watch &) = delete;

    private:
     static std::chrono::high_resolution_clock::time_point now() {
          return std::chrono::high_resolution_clock::now();
     }

     std::chrono::duration<double> elapsed() const {
          return (now() - Start_);
     }

     std::chrono::high_resolution_clock::time_point Start_;
};

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

int **opMatriz;
int **locParentesis;

int main(int argc, char *argv[]) {

     double vmInit, rssInit;              // Armazena a memória utilizada ao inicio da execucao
     double vmEnd, rssEnd;                // Armazena a memória utilizada ao final da execucao
     //process_mem_usage(vmInit, rssInit);  // Calcula a memoria utilizada e seta no inicio Only in linux

     std::vector<int> dimensions;
     int n;

     // Global Variables to store test results:
     int numIterations = 5;
     int instanceSize = 0;
     std::string algorithm = "";
     int numberOfOp = 0;
     long long int timeSpent = 0;
     double memorySpent = 0.0;

     if (argc < 4) {
          std::cout << "\n- Error: Arguments missing!" << std::endl;

          std::cout << "\n- Use the following pattern to run the program properly on Windows:" << std::endl;

          std::cout << "\n.\\dynamicProgMulMatrix.exe <path_to_instance_file> <algorithm_code> <print_type> <print_sol>" << std::endl;

          std::cout << "\nWhere:" << std::endl;

          std::cout << " - Algorithm Code: use 1 for Brute Force and 2 for Dynamic Programming." << std::endl;
          std::cout << " - Print Type: use 1 for easy terminal reading and 2 for csv output file formatting" << std::endl;
          std::cout << " - Print sol: use 1 to write the solution into a file" << std::endl;

          return 0;
     }

     if (argc > 1) {
          bool wasRead = readFile(argv[1], dimensions, &n);
          
          if (wasRead) {
               initMatrixes(n);
               std::string str(argv[2]);

               if (str == "1") {
                    //std::cout << "\nRunning brute force tests, please wait... \n" << std::endl;

                    algorithm = "BruteForce";
                    instanceSize = dimensions.size() - 1;

                    for (int i = 0; i < numIterations; i++) {

                         stop_watch sw;

                         int numOps = recursiveAlgo(dimensions, 1, n - 1);

                         auto m = sw.elapsed_ns().count();

                         numberOfOp += opMatriz[1][n - 1];
                         timeSpent += m;
                         memorySpent += 0.0;
                    }

               }

               else if (str == "2") {
                    // std::cout << "\nRunning dynamic programming tests, please wait...\n" << std::endl;

                    algorithm = "Dynamic Programming";
                    instanceSize = dimensions.size() - 1;

                    for (int i = 0; i < numIterations; i++) {
                         int j, min, q;

                         stop_watch sw;

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

                         auto m = sw.elapsed_ns().count();

                         numberOfOp += opMatriz[1][n - 1];
                         timeSpent += m;
                         memorySpent += 0.0;
                    }
               }

               // process_mem_usage(vmEnd, rssEnd);  // Calcula a memoria utilizada e seta no final Only in linux
               // memorySpent = rssEnd - rssInit;    // Calcula a dif de memoria entre o final e no inicio

               if(argc == 5 && std::string(argv[4]) == "1")
                    writeSolution(instanceSize);

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
          } else
               std::cout << "No valid output method choosed. Please, check arguments." << std::endl;
     }         

     return 0;
}