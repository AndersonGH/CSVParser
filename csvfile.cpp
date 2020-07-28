#include "csvfile.h"

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
    file.close();
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
    std::vector <std::string> tokens;
    std::string buff;

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

    std::string & arg1 = get(tokens[0]);
    if(arg1[0] == '=')
        parse(arg1);
    std::string & arg2 = get(tokens[2]);
    if(arg2[0] == '=')
        parse(arg2);
    cell = oper_cells(arg1,tokens[1],arg2);
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


std::string CSVFile::oper_cells(std::string const & arg1, std::string const & op, std::string const & arg2){
    int val;
    switch (op[0]){
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


