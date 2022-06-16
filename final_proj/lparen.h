#ifndef LPAREN_H
#define LPAREN_H


#include <iostream>
#include "loperator.h"

using namespace std;

class LParen : public LOperator
{
public:
    //child of LOprator
    LParen();
    int typeOf();
    void print(ostream& outs);
    int prec();
};
#endif // LPAREN_H
