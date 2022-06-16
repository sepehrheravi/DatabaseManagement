#include "loperator.h"


LOperator::LOperator(string op) : op(op)
{

}

int LOperator::typeOf()
{
    return LOPERATOR;
}

string LOperator::oper()
{
    return op;
}

void LOperator::print(ostream& outs)
{
    outs << op;
}

int LOperator::prec()
{
    if (op == "or")
    {
        return 1;
    }
    else if (op == "and")
    {
        return 2;
    }
    return 0;
}
