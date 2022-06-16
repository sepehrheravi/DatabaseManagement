#include "lparen.h"


LParen::LParen() : LOperator("(")
{

}

int LParen::typeOf()
{
    return LPAREN;
}

void LParen::print(ostream& outs)
{
    outs << "(";
}

int LParen::prec()
{
    return 0;
}
