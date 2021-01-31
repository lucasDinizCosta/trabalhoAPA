#include <iostream>
#include <ctime>
#include <fstream>
#include <stdlib.h>
#include <string>


int main (int argc, char* argv[]){
    
    srand(time(NULL));
    int number_matrixes = atoi(argv[1]);

    int lines;
    int columns;

    lines = rand() % 61;
    columns = rand() % 61;

    std::ofstream matrix;
    std::string file_name = "instancias/matrixes-" + std::to_string(number_matrixes) + ".csv";
    matrix.open (file_name);

    int num;
    std::string line = "";

    for(int i = 0; i < number_matrixes; i++){

        std::cout << lines << "|" << columns << std::endl;
        line = line + std::to_string(lines) + "," + std::to_string(columns) + "\n";
        
        /*std::string line;

        for(int j = 0; j < lines; j++){
            
            line = "";

            for(int k = 0; k < columns; k++){
                num = ((rand() % 101) - 50);
                line = line + std::to_string(num) + ",";
            }

            line.erase(line.end()-1);
            matrix << line + "\n";

        }*/

        lines = columns;
        columns = rand() % 61;

    }

    line.erase(line.end()-1);
    matrix << line;
    matrix.close();

    return 0;
}