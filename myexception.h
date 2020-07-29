#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H
#include <exception>
#include <iostream>

class MyException: public std::exception{
public:
    MyException(const char* msg): msg(msg){}
    virtual const char* what() const noexcept{
        return msg;
    }
private:
    const char* msg;
};


#endif // MYEXCEPTION_H
