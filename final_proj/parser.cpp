#include "parser.h"

int Parser::adj_table[MAX_ROWS][MAX_COLS];

Parser::Parser():Ptree(), _keywords(), input(), flag(false)
{
    //2.initialize table
    make_table(adj_table);



    //3.create list of keywords
    build_keyword_list();

}


Parser::Parser(char a[MAX_BUFFER])
{


    //2.initialize table
    make_table(adj_table);



    //3.create list of keywords
    build_keyword_list();


    //4.set string
    set_string(a);

}

void Parser::set_string(char a[MAX_BUFFER])
{
    bool debug = false;
    //1.copy to buffer
    for(unsigned int i=0; i<strlen(a); i++)
    {
        _buffer[i] = a[i];
    }

    _buffer[strlen(a)] = '\0';


    STokenizer stk(_buffer);
    Token t;
    stk>>t;

    if(t.token_str() == "\"")
    {

        string s;
        stk>>t;

        //dealing with different cases of my stokenizer with cotations
        //and puncs that comes before or after that
        while(t.token_str() != "\"" && t.token_str() != "\","
              && t.token_str() != ".\"" && t.token_str() != ".\"," && t.token_str() != "\")")
        {
            s += t.token_str();
            stk >> t;
        }

        if(t.token_str() == "\",")
        {
            input.push_back(s);
            input.push_back(",");
        }
        else if(t.token_str() == ".\",")
        {
            s += ".";
            input.push_back(s);
            input.push_back(",");
        }
        else if(t.token_str() == ".\"")
        {
            s += ".";
            input.push_back(s);
        }
        else if(t.token_str() == "\")")
        {
            input.push_back(s);
            input.push_back(")");
        }
        else
        {
            input.push_back(s);
        }


    }
    else
    {
        if(t.type_string() == "ALPHA" || t.type_string() == "PUNC" || t.type_string() == "NUMBER")
        {
            string s = t.token_str();
            //make command to lowercase
            transform(s.begin(), s.end(), s.begin(), ::tolower);
            input.push_back(s);
        }

    }
    while(!stk.done())
    {
        stk>>t;
        if(t.token_str() == "\"")
        {
            string s;
            stk>>t;
            while(t.token_str() != "\"" && t.token_str() != "\","
                  && t.token_str() != ".\"" && t.token_str() != ".\"," && t.token_str() != "\")")
            {
                s += t.token_str();
                stk >> t;
            }

            if(t.token_str() == "\",")
            {
                input.push_back(s);
                input.push_back(",");
            }
            else if(t.token_str() == ".\",")
            {
                s += ".";
                input.push_back(s);
                input.push_back(",");
            }
            else if(t.token_str() == ".\"")
            {
                s += ".";
                input.push_back(s);
            }
            else if(t.token_str() == "\")")
            {
                input.push_back(s);
                input.push_back(")");
            }
            else
            {
                input.push_back(s);
            }
        }
        else
        {
            if(t.type_string() == "ALPHA" || t.type_string() == "PUNC" || t.type_string() == "NUMBER")
            input.push_back(t.token_str());
        }
    }

    if(debug)
    {
        for(unsigned int i=0; i<input.size(); i++)
        {
            cout << input[i] << endl;
        }

        cout << "VEC SIZE AFTER TOEKNIZE: " << input.size() << endl;
    }


    flag = get_parse_tree();

}

int Parser::get_column(string token)
{
    if(_keywords.contains(token))
        return _keywords[token];
    else
        return SYMBOL;


}

void Parser::build_keyword_list()
{

    //creating keyword maps


    _keywords["select"] = SELECT;
    _keywords["from"] = FROM;
    _keywords["*"] = STAR;
    _keywords["make"] = MAKE;
    _keywords["create"] = MAKE;
    _keywords["table"] = TABLE;
    _keywords["fields"] = FIELDS;
    _keywords[","] = COMMA;
    _keywords["values"] = VALUES;
    _keywords["insert"] = INSERT;
    _keywords["into"] = INTO;
    _keywords["where"] = WHERE;
    _keywords["batch"] = BATCH;
    _keywords["\""] = COTATION;


}

void Parser::make_table(int table[][MAX_COLS])
{
    //set all table to -1
    for(int i=0; i<MAX_ROWS; i++)
        for(int j=0; j<MAX_COLS; j++)
            table[i][j] = -1;

    //bash
    table[0][BATCH] = BATCH;
    table[BATCH][SYMBOL] = 4;

    //select fields and select star
    table[0][SELECT] = 1;
    table[1][STAR] = 2;
    table[1][SYMBOL] = 10;
    table[10][FROM] = 3;
    table[10][COMMA] = 1;
    table[2][FROM] = 3;
    table[3][SYMBOL] = 4;
    table[4][WHERE] = WHERE;

    //making table
    table[0][MAKE] = 5;
    table[5][TABLE] = 6;
    table[6][SYMBOL] = 7;
    table[7][FIELDS] = 8;
    table[8][SYMBOL] = 9;
    table[9][COMMA] = 8;

    //inserting into
    table[0][INSERT] = 5;
    table[5][INTO] = 6;
    table[7][VALUES] = 8;




    for(int i=0; i<4; i++)
    {
        table[i][0] = 0;
    }

    mark_suc(table, 4);
    mark_suc(table, 9);
    mark_suc(table, WHERE);

}

void Parser::mark_suc(int table[][MAX_COLS], int state)
{
    //determines success states by marking 1
    table[state][0] = 1;

}

bool Parser::get_parse_tree()
{
    int col = 0;
    bool debug = false;
    int start_state = 0;
    unsigned int count = 0;
    unsigned int pos = input.size()-1;

    //find pos "where" exists
    for(unsigned int i=0; i<input.size(); i++)
    {
        if(input[i] == "where")
        {
            pos = i;
        }
    }

    while(adj_table[start_state][col] != -1 || count <= pos)
    {

        col = get_column(input[count]);
        if(debug)
        {
            cout << "POP VECTOR=> " << input[count] << endl;
            cout << "ROW: " << start_state << endl;
            cout << "COL: " << col <<endl;
        }
        start_state = adj_table[start_state][col];
        switch (start_state)
        {
        case 1:
            if(debug)
                cout << "command" << endl;
            //had to put this to prevent commas
            if(input[count] != ",")
                Ptree["command"] += input[count];
            break;
        case 2:
            if(debug)
                cout << "field" << endl;
            Ptree["field"] += input[count];
            break;
        case 3:
            if(debug)
                cout << "for" << endl;
            break;
        case 4:
            if(debug)
                cout << "table name" << endl;
            Ptree["table"] += input[count];
            break;

        case 5:
            if(debug)
                cout << "make" << endl;
            Ptree["command"] += input[count];
            break;
        case 6:
            if(debug)
                cout << "table" << endl;
            break;
        case 7:
            if(debug)
                cout << "table name" << endl;
            Ptree["table"] += input[count];
            break;
        case 8:
            if(debug)
                cout << "fields" << endl;
            break;
        case 9:
            if(debug)
                cout << "field names" << endl;
            Ptree["field"] += input[count];
            break;
        case 10:
            if(debug)
                cout << "field names" << endl;
            Ptree["field"] += input[count];
            break;
        case WHERE:
            if(debug)
                cout << "where" << endl;
            Ptree["where"] += "Yes";
            break;
        case BATCH:
            if(debug)
                cout << "batch" << endl;
            Ptree["command"] += "batch";
            break;


        }
        if(debug)
            cout << Ptree << endl;
        count++;


    }


    //dea with where so we know if it exists
    if(!Ptree.contains("where"))
    {
        Ptree["where"] += "No";
    }

    //if condition put all in condition
    else
    {
        for(unsigned int i=count; i<input.size(); i++)
        {

            Ptree["condition"] += input[i];

        }
    }

    if(debug)
    {
        cout << "COMMAND " << Ptree["command"].size() << endl;
        cout << "TABLE NAME " << Ptree["table"].size() << endl;
        cout << "FIELD " << Ptree["field"].size() << endl;
        cout << "condition " << Ptree["condition"].size() << endl;
        cout << endl;
    }


    if(adj_table[start_state][0] == 1)
        return true;
    else
        return false;

}

bool Parser:: fail()
{
    return !flag;
}
MMap<string, string> Parser:: p_tree()
{
   return Ptree;
}
