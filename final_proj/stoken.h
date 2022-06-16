#ifndef STOKEN_H
#define STOKEN_H


#include <iostream>

const int TOKEN = 1;
const int LPAREN = 2;
const int SYM = 8;
const int RPAREN = 3;
const int LOPERATOR = 4;
const int COPERATOR = 5;
const int RECORDNUMBERS = 6;


using namespace std;


class SToken
{
public:
    SToken();
    virtual int typeOf();
    virtual void print(ostream& outs = cout);
};
#endif // STOKEN_H
