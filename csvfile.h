#ifndef CSVFILE_H
#define CSVFILE_H
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <regex>

class CSVFile{
public:
    CSVFile(char const *);
    void printCSV();
private:
    void parse();
    void parse(std::string &);
    std::string& get(std::string const &, std::string const &);
    std::string& get(std::string const &);
    std::string oper_cells(std::string const &, std::string const &, std::string const &);

    std::vector<std::vector<std::string>> data;
    std::vector<std::string> row_names;

};

#endif // CSVFILE_H
