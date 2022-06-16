#include "rparen.h"

RParen::RParen() : LOperator(")") {}

int RParen::typeOf()
{
    return RPAREN;
}

void RParen::print(ostream& outs)
{
    outs << ")";
}

int RParen::prec()
{
    return 4;
}
