#ifndef RPN_H
#define RPN_H


#include <cmath>
#include <iostream>
#include "!includes/mmap.h"
#include "!includes/map.h"
#include "stoken.h"
#include "loperator.h"
#include "coperator.h"
#include "lparen.h"
#include "rparen.h"
#include "symbol.h"
#include "recno.h"
#include "!includes/stack.h"
#include "!includes/my_vector.h"
#include <algorithm>

using namespace std;

template<typename T>
std::vector<T> Intersection(std::vector<T> &v1,std::vector<T> &v2)

{
    std::vector<T> v3;

    std::set_intersection(v1.begin(),v1.end(),
                          v2.begin(),v2.end(),
                          back_inserter(v3));
    return v3;
}

template<typename T>
std::vector<T> Union(std::vector<T> &v1, std::vector<T> &v2)

{
    std::vector<T> v3;

    std::set_union(v1.begin(),v1.end(),
                          v2.begin(),v2.end(),
                         back_inserter(v3));
    return v3;
}




class RPN
{
public:

    //purpose is to get the recno desired
    RPN(Vector<SToken*> postFix);

    vector<long> get_record(Map<string, int>& fields, vector<MMap<string, long>>& indices);

private:
    Vector<SToken*> postfix;
};




#endif // RPN_H
