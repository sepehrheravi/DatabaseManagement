#include "stoken.h"

SToken::SToken()
{

}

int SToken::typeOf()
{
     return TOKEN;

}

void SToken::print(ostream& outs)
{
    outs << "STUFF" << endl;
}
