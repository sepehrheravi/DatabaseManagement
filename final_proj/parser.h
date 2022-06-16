#ifndef PARSER_H
#define PARSER_H
#include "!includes/bplustree.h"
#include "!includes/array_func.h"
#include "!includes/mpair.h"
#include "!includes/mmap.h"
#include "!includes/pair.h"
#include "!includes/map.h"
#include "stokenizer.h"


const int SELECT = 1;
const int FROM = 3;
const int STAR = 2;
const int SYMBOL = 8;
const int MAKE = 5;
const int INSERT = 5;
const int TABLE = 6;
const int INTO = 6;
const int FIELDS = 7;
const int VALUES = 7;
const int COMMA = 9;
const int WHERE = 30;
const int BATCH = 40;
const int COTATION = 50;


const int MAX_ROWS = 100;
const int MAX_COLS = 100;

class Parser
{
public:
    Parser();
    Parser(char a[MAX_BUFFER]);
    void set_string(char a[MAX_BUFFER]);
    int get_column(string token);
    void build_keyword_list();
    void make_table(int table[][MAX_COLS]);
    void mark_suc(int table[][MAX_COLS], int state);
    //mark success states
    bool get_parse_tree();

    bool fail();
    MMap<string, string> p_tree();

private:

    MMap<string,string> Ptree;
    Map<string,int> _keywords;
    char _buffer[MAX_BUFFER+1];
    static int adj_table[MAX_ROWS][MAX_COLS];
    vector<string> input;
    bool flag;

};



#endif // PARSER_H
