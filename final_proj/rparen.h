#ifndef RPAREN_H
#define RPAREN_H

#include <iostream>
#include "loperator.h"
using namespace std;

class RParen : public LOperator
{
public:
    //child of Loperator
    RParen();
    int typeOf();
    void print(ostream& outs);
    int prec();
};

#endif // RPAREN_H
