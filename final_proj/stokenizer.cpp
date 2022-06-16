#include "stokenizer.h"

int STokenizer::_table[RMAX][CMAX];

STokenizer::STokenizer(): _pos(0)
{
    make_table(_table);
    _buffer[0] = '\0';

}

STokenizer::STokenizer(char str[])
{
    _pos = 0;
    make_table(_table);
    //copy char str into buffer
    for(unsigned int i=0; i<strlen(str); i++)
    {
        _buffer[i] = str[i];
    }
    //mark last place with '\0'
    _buffer[strlen(str)] = '\0';

}

void mark_success(int _table[][CMAX], int state)
{
    //determines success states by marking 1
    _table[state][0] = 1;
}

void mark_cell(int _table[][CMAX], int from, int to, int state, int mark)
{
    //mark cells
    for(int i=from; i<=to; i++)
    {
        _table[state][i] = mark;
    }
}

void STokenizer::set_string(char str[])
{
    _pos = 0;
    for(unsigned int i=0; i<strlen(str); i++)
    {
        _buffer[i] = str[i];
    }
    _buffer[strlen(str)] = '\0';
}


void STokenizer::make_table(int _table[][CMAX])
{
    //set all table to -1
    for(int i=0; i<RMAX; i++)
        for(int j=0; j<CMAX; j++)
            _table[i][j] = -1;
    //mark other parts of the table
    mark_cell(_table, int('a'), int('z'), 0, ALPHA);
    mark_cell(_table, int('A'), int('Z'), 0, ALPHA);
    mark_cell(_table, int('0'), int('9'), 0, NUMBER);
    mark_cell(_table, int('a'), int('z'), ALPHA, ALPHA);
    mark_cell(_table, int('A'), int('Z'), ALPHA, ALPHA);
    mark_cell(_table, int('0'), int('9'), NUMBER, NUMBER);
    mark_cell(_table, int('0'), int('9'), DPOINT, NUMBER);
    mark_cell(_table, int('!'), int('/'), PUNC, PUNC);
    mark_cell(_table, int('!'), int('/'), 0, PUNC);
    mark_cell(_table, int(':'), int('@'), PUNC, PUNC);
    mark_cell(_table, int(':'), int('@'), 0, PUNC);
    _table[NUMBER][int('.')] = DPOINT;
    _table[0][9] = SPACE;
    _table[0][10] = SPACE;
    _table[0][11] = SPACE;
    _table[0][32] = SPACE;
    _table[0][13] = SPACE;
    _table[SPACE][9] = SPACE;
    _table[SPACE][10] = SPACE;
    _table[SPACE][11] = SPACE;
    _table[SPACE][32] = SPACE;
    _table[SPACE][13] = SPACE;

    mark_success(_table, ALPHA);
    mark_success(_table, NUMBER);
    mark_success(_table, SPACE);
    mark_success(_table, PUNC);

}

int STokenizer::get_token(int start_state, string &token)
{
    int col = 0;
    int last = _pos;
    int success = 0;
    //1. get char in _pos and find its value in ascii
    col = int(_buffer[_pos]);
    if(col > 127 || col < 0)
    {
        token = _buffer[_pos];
        _pos++;
        return -1;
    }
    //2.make sure we dont land in -1 and we don't end up at the end of cstr
    while(_table[start_state][col] != -1 && _buffer[_pos] != '\0')
    {
        //3. new state is whatever number is at _table
        start_state = _table[start_state][col];
        if(_table[start_state][0] == 1)
        {
            //4.remembering success state
            success = start_state;
        }
        //4.move to next _pos
        _pos++;
        //5. get next int value
        col = int(_buffer[_pos]);
    }

    // if fail state move the pos back
    if(_table[start_state][0] != 1)
    {
        _pos -= 1;
        //put from last pos till new _pos into token
        for(int i=last; i<_pos; i++)
        {
            token += _buffer[i];
        }
//        start_state = success;
        return success;
    }

    else
    {
        for(int i=last; i<_pos; i++)
        {
            token += _buffer[i];
        }
        return success;
    }

}

bool STokenizer::done()
{
    //true if reaches end
    return (_buffer[_pos] == '\0');
}
