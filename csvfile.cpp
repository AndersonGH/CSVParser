#include "csvfile.h"
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <regex>

CSVFile::CSVFile(char const * file_name){
    std::ifstream file(file_name);
    std::string buff;
    std::vector <std::string> row;
    bool first_enter;
    if(file)
        while(std::getline(file,buff)){
            std::stringstream s(buff);
            first_enter = true;
            while(std::getline(s,buff,',')){
                if(first_enter)
                    row_names.push_back(buff);
                first_enter = false;
                row.push_back(buff);
            }
            data.push_back(row);
            row.clear();
        }
    //std::string str("B2");
    //std::string & val = get("B2");
    //std::string & val = get("B","2");
    //std::cout << val;
    parse();
}


std::string& CSVFile::get(std::string const & column, std::string const & row){
    size_t col_it = std::find(data.front().begin(), data.front().end(), column) - data.front().begin();
    size_t r_it = std::find(row_names.begin(), row_names.end(), row)- row_names.begin();
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
    /*
    std::vector <std::string> tokens;
    std::regex e ("([A-Za-z\\d])+");
    std::sregex_iterator rend;
    std::sregex_iterator it( cell.begin(), cell.end(), e );
    while (it!=rend) {
        tokens.push_back(it->str());
        ++it;
    }
    tokens.push_back(std::string(1, cell[tokens[0].size() + 1]));
    */
    auto index_op = std::find_if(cell.begin(),cell.end(), [](const char & ch){
        return ch == '+' || ch == '-' || ch == '*' || ch == '/';
    }) - cell.begin();
    /*
    for (char const &c: cell){
        if(c == '=')
            continue;
        if(c == '+' || c == '-' || c == '*' || c == '/'){
            tokens.push_back(buff);
            buff.clear();
            buff.push_back(c);
            tokens.push_back(buff);
            buff.clear();
            continue;
        }
        buff.push_back(c);
    }
    tokens.push_back(buff);
    */
    std::string & arg1 = get(cell.substr(1,index_op - 1));
    if(arg1[0] == '=')
        parse(arg1);
    std::string & arg2 = get(cell.substr(index_op + 1,cell.size() - 1));
    if(arg2[0] == '=')
        parse(arg2);
    cell = oper_cells(arg1,cell[index_op],arg2);
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


std::string CSVFile::oper_cells(std::string const & arg1, char const & op, std::string const & arg2){
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
            val = std::stoi(arg1) / std::stoi(arg2);
            break;
        }
    return std::to_string(val);
}


