#include <iostream>
#include <ctime>
#include <fstream>
#include <stdlib.h>
#include <string>

/*INPUT:
OUTPUT:
DESCRIP: Gera um arquivo csv com as dimensões das matrizes geradas aleatoriamente entre 1 - 61*/
int main (int argc, char* argv[]){

    if(argc > 1){
        srand(time(NULL));
        int number_matrixes = atoi(argv[1]);

        int lines;
        int columns;

        lines = rand() % 61 + 1;
        columns = rand() % 61 + 1;

        std::ofstream matrix;
        std::string file_name = "../instancias/matrixes-" + std::to_string(number_matrixes) + ".csv";
        matrix.open (file_name);

        int num;
        std::string line = "";


        for(int i = 0; i < number_matrixes; i++){

            line = line + std::to_string(lines) + "," + std::to_string(columns) + "\n";

            lines = columns;
            columns = rand() % 61 + 1;

        }

        line.erase(line.end()-1);
        matrix << line;
        matrix.close();
    }

    

    return 0;
}