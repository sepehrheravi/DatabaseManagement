#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include "constants.h"
using namespace std;

class Token
{
public:
    //Default CTOR
    Token();
    //CTOR
    Token(string str, int type);
    //show tokens type
    friend ostream& operator <<(ostream& outs, const Token& t)
    {
        outs << "|";
        outs << t._token;
        outs << "|";
        return outs;
    }
    //type of token in number
    int type();
    //type of token in string
    string type_string();
    //token itself
    string token_str();
private:
    string _token;
    int _type;
};

#endif // TOKEN_H
