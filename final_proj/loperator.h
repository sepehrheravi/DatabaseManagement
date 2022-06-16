#ifndef LOPERATOR_H
#define LOPERATOR_H

#include <iostream>
#include "stoken.h"

using namespace std;

class LOperator : public SToken
{
public:
    //child of stoken
    LOperator(string op);
    int typeOf();
    virtual string oper();
    virtual void print(ostream& outs);
    virtual int prec();

private:
    string op;
};
#endif // LOPERATOR_H
