#ifndef STOKENIZER_H
#define STOKENIZER_H

#include <iostream>
#include "token.h"
#include "constants.h"


using namespace std;

class STokenizer
{
public:
    STokenizer();
    STokenizer(char str[]);
    bool done();            //determines that there are no more tokens
//    bool more();

    //extract one token (very similar to the way cin >> works)
    friend STokenizer& operator >> (STokenizer& s, Token& t)
    {
        //1.have a string
        string t_str ="";
        //2. to get the state no.
        int y = 0;
        //3.get the state number
        y = s.get_token(0, t_str);
        //4.create a token with specific name
        t = Token(t_str, y);
        return s;
    }

    //set a new string as the input string
    void set_string(char str[]);


    //for test purposes returns position
    int posit()
    {
        return _pos;
    }

private:

    //define the state machine and initialize the table
    void make_table(int _table[][CMAX]);

    //token gets extracted and the state no will be returned
    int get_token(int start_state, string& token);


    //---------------------------------
    char _buffer[MAX_BUFFER+1];
    //input string
    int _pos;
    //current position in the string
    static int _table[RMAX][CMAX];
    //table
};


void mark_success(int _table[][CMAX], int state);
//mark success states
void mark_cell(int _table[][CMAX], int from, int to, int state, int mark);
//mark all cells

#endif // STOKENIZER_H
