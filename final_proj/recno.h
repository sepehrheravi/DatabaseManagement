#ifndef RECNO_H
#define RECNO_H


#include <iostream>
#include <vector>
#include "stoken.h"
using namespace std;

class Recno : public SToken
{
public:
    //child of stoken
    Recno(vector<long> v);
    int typeOf();
    int prec();

    //give us vector of recno
    vector<long> rec_vec();
    void print(ostream& outs);

private:
    vector<long> _v;
};
#endif // RECNO_H
