#include "coperator.h"


COperator::COperator(string op) : op(op)
{

}

int COperator::prec()
{
    return 3;
}

int COperator::typeOf()
{
    return COPERATOR;
}

string COperator::oper()
{
    return op;
}


void COperator::print(ostream &outs)
{
    outs << op;
}

