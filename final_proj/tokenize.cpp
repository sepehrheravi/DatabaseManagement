#include "tokenize.h"

Tokenize::Tokenize(): tok_vec()
{
    //blank
}


Vector<SToken*> Tokenize::tokenize(vector<string> t)
{
    //goes through vectorstr and gets each item
    for (unsigned int i = 0; i < t.size(); i++)
    {
        if (t[i] == "(")
        {
            tok_vec.push_back(new LParen());
        }
        else if (t[i] == ")")
        {
            tok_vec.push_back(new RParen());
        }
        else if (t[i] == "and" || t[i] == "or")
        {
            tok_vec.push_back(new LOperator(t[i]));
        }
        else if (t[i] == "=" ||
                 t[i] == ">" ||
                 t[i] == "<" ||
                 t[i] == ">=" ||
                 t[i] == "<=")
        {
            tok_vec.push_back(new COperator(t[i]));
        }

        else
        {
            tok_vec.push_back(new Symbol(t[i]));
        }
    }

    return tok_vec;

}



