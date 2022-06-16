#ifndef TOKENIZE_H
#define TOKENIZE_H

#include <iostream>
#include <string.h>
#include <stdio.h>
#include "!includes/queue.h"
#include "vector"
#include "!includes/my_vector.h"
#include "stoken.h"
#include "loperator.h"
#include "coperator.h"
#include "lparen.h"
#include "rparen.h"
#include "symbol.h"

using namespace std;

class Tokenize
{
public:
    //CTOR
    Tokenize();

    //TOKENIZE and returns vec
    Vector<SToken*> tokenize(vector<string> t);

private:

    Vector<SToken*> tok_vec;
};
#endif // TOKENIZE_H
