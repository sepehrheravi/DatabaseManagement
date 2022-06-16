#include "recno.h"


Recno::Recno(vector<long> v)
{
    _v = v;
}

int Recno::typeOf()
{
    return RECORDNUMBERS;
}

int Recno::prec()
{
    return 3;
}

vector<long> Recno::rec_vec()
{
    return _v;
}

void Recno::print(ostream& outs)
{
    for (unsigned int i = 0; i < _v.size(); i++)
    {
        outs << _v[i] << "|";
    }
}
