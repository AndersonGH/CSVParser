#ifndef CSVFILE_H
#define CSVFILE_H
#include <iostream>
#include <vector>

class CSVFile{
public:
    CSVFile(char const *);
    void printCSV();
private:
    void parse();//searching for cells with '='
    void parse(std::string &);//calculate cell with '='
    std::string& get(std::string const &, std::string const &);
    std::string& get(std::string const &);
    std::string oper_cells(std::string const &, char const , std::string const &);
    std::vector<std::vector<std::string>> data;
};

#endif // CSVFILE_H
