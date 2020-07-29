#include <iostream>
#include "csvfile.h"
#include "myexception.h"


int main(int argc, char* argv[]) {
    try {
        CSVFile csv("test1.csv");
        csv.printCSV();
    } catch (const MyException & e) {
        std::cout << "Error: " <<e.what() << std::endl;
    }



    return 0;
}
