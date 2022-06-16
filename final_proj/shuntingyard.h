#ifndef SHUNTINGYARD_H
#define SHUNTINGYARD_H


#include "stoken.h"
#include "loperator.h"
#include "coperator.h"
#include "lparen.h"
#include "rparen.h"
#include "symbol.h"
#include "!includes/stack.h"
#include "!includes/my_vector.h"


class Shunting_yard
{
public:
    //DEfualt CTOR
    Shunting_yard();
    //CTOR
    Shunting_yard(Vector<SToken*> infix);

    //Returns the postfix Vec
    Vector<SToken*> postfix();



private:
    Vector<SToken*> _postfix;
    //Returns the postfix vector

    Vector<SToken*> _get_post_fix(Vector<SToken*> infix);



};

#endif // SHUNTINGYARD_H
