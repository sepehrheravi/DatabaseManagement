#ifndef COPERATOR_H
#define COPERATOR_H

#include <string>
#include "stoken.h"

using namespace std;

class COperator : public SToken
{
public:
    //child of stoken
    COperator(string op);
    string oper();
    int prec();
    int typeOf();
    void print(ostream &outs = cout);

private:
    string op;
};


#endif // COPERATOR_H
