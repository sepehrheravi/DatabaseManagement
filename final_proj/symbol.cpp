#include "symbol.h"

Symbol::Symbol(std::string str):_s(str)
{

}

int Symbol::typeOf()
{
    return SYM;
}

int Symbol::prec()
{
    return 3;
}

string Symbol::str()
{
    return _s;
}

void Symbol::print(ostream& outs)
{
    outs << _s;
}
