#ifndef SYMBOL_H
#define SYMBOL_H

#include <iostream>
#include "stoken.h"

using namespace std;


class Symbol : public SToken
{
public:

    //child of token
    //everything that is not vec of recno and operators
    Symbol(string s);
    int typeOf();
    int prec();
    string str();
    void print(ostream& outs = cout);

private:
    //couldn't say string weird
    string _s;

};

#endif // SYMBOL_H
