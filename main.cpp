#include <iostream>
#include "csvfile.h"


int main(int argc, char* argv[]) {
    CSVFile csv("test.csv");
    csv.printCSV();

    return 0;
}
