#include "token.h"

Token::Token(): _token(""), _type(0)
{
}

Token::Token(string str, int type): _token(str), _type(type)
{
}

int Token:: type()
{
    return _type;
}

string Token:: token_str()
{
    return _token;
}


string Token:: type_string()
{
    //type of token
    switch (_type)
    {
    case NUMBER:
        return "NUMBER";
        break;
    case ALPHA:
        return "ALPHA";
        break;
    case SPACE:
        return "SPACE";
        break;
    case PUNC:
        return "PUNC";
        break;
    default:
        return "UNKNOWN";
        break;
    }
}
