#include "csvfile.h"
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <regex>
#include "myexception.h"

CSVFile::CSVFile(char const * file_name){
    std::ifstream file(file_name);
    std::string buff;
    std::vector <std::string> row;
    if(file)
        while(std::getline(file,buff)){
            std::stringstream s(buff);
            while(std::getline(s,buff,','))
                row.push_back(buff);
            data.push_back(row);
            row.clear();
        }
    else
        throw MyException("File not found");
    try {
        parse();
    } catch (const MyException & e) {
        throw;
    }
}

std::string& CSVFile::get(std::string const & column, std::string const & row){
    size_t col_it = std::find(data.front().begin(), data.front().end(), column) - data.front().begin();
    size_t r_it = std::find_if(data.begin(),data.end(), [&row](std::vector<std::string> const & vec){
        return vec[0] == row;
        }) - data.begin();
    return data[r_it][col_it];
}

std::string& CSVFile::get(std::string const & cell){
    std::string column, row;
    for (char const &c: cell)
        if(isalpha(c))
            column.push_back(c);
        else
            row.push_back(c);
    return get(column,row);
}

void CSVFile::parse(std::string & cell){
    auto index_op = std::find_if(cell.begin(),cell.end(), [](const char & ch){
        return ch == '+' || ch == '-' || ch == '*' || ch == '/';
    }) - cell.begin();
    std::string & arg1 = get(cell.substr(1,index_op - 1));
    if(arg1[0] == '=')
        parse(arg1);
    std::string & arg2 = get(cell.substr(index_op + 1,cell.size() - 1));
    if(arg2[0] == '=')
        parse(arg2);
    try {
        cell = oper_cells(arg1,cell[index_op],arg2);
    } catch (const MyException & e) {
        throw;
    }
}

void CSVFile::parse(){
    for (auto &column : data)
        for (auto &row : column)
            if(row[0] == '=')
                parse(row);
}

void CSVFile::printCSV(){
    for (size_t i =0; i < data.size(); ++i){
        for (size_t j = 0; j < data.front().size(); ++j){
            std::cout << data[i][j];
            if(j + 1 != data.front().size())
                std::cout << ',';
        }
        std::cout << std::endl;
    }
}

std::string CSVFile::oper_cells(std::string const & arg1, char const op, std::string const & arg2){
    int val;
    switch (op){
        case '+':
            val = std::stoi(arg1) + std::stoi(arg2);
            break;
        case '-':
            val = std::stoi(arg1) - std::stoi(arg2);
            break;
        case '*':
            val = std::stoi(arg1) * std::stoi(arg2);
            break;
        case '/':
            if(std::stoi(arg2) == 0)
                throw MyException("Division by zero");
            val = std::stoi(arg1) / std::stoi(arg2);
            break;
        }
    return std::to_string(val);
}


