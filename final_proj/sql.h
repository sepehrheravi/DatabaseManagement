#ifndef SQL_H
#define SQL_H
#include "parser.h"
#include "table.h"

class SQL
{
public:
    SQL();

    //call run command in a loop
    void run();

    void run_command(string input);

    void run_batch();

    void insert(string name, vectorstr field);

    void create_table(string name, vectorstr field);

    void process_batch(string name);

    //table names
    vectorstr tables_vec()
    {
        return _table_names;
    }

    //map for searching table names
    Map<string, int> tables_map()
    {
       return _tables;
    }


private:

    Map<string, int> _tables;
    vectorstr _table_names;

};

//===================================

SQL::SQL(): _tables(), _table_names()
{

}

void SQL::run()
{
    string input;
    cout << endl << "[exit] ?: ";
    getline(cin, input);

    while(input != "exit")
    {
        if(input != "")
            run_command(input);
        cout << endl << "[exit] ?: ";
        getline(cin, input);

    }
}

void SQL::run_command(string input)
{
    char a[MAX_BUFFER];
    strcpy(a, input.c_str());
    Parser p(a);
    MMap<string, string> mp = p.p_tree();


    if(mp["command"][0] == "make" || mp["command"][0] == "create")
    {
        create_table(mp["table"][0], mp["field"]);
    }
    else if(mp["command"][0] == "insert")
    {

        insert(mp["table"][0], mp["field"]);
    }
    else if(mp["command"][0] == "select")
    {
        if(mp["where"][0] == "No")
        {
            if(mp["field"][0] == "*")
            {
                Table t(mp["table"][0]);

                cout << t.select_all();

            }
            else
            {
                Table t(mp["table"][0]);
                cout << t.select_col(mp["field"]);

            }
        }
        else
        {
            if(mp["field"][0] == "*")
            {
                Table t(mp["table"][0]);

                cout << t.select_cond(mp["condition"]);

            }
            else
            {
                Table t(mp["table"][0]);

                cout << t.select_col_cond(mp["field"], mp["condition"]);
            }


        }
    }
    else if(mp["command"][0] == "batch")
    {
        process_batch(mp["table"][0]);
    }

}


void SQL::insert(string name, vectorstr field)
{
    Table t(name);
    t.insert_into(field);
    cout << "Inserted: " <<  field << "into " << name
            << endl;
}

void SQL::create_table(string name, vectorstr field)
{
    Table t(name, field);
    if(!_tables.contains(name))
    {
        _tables[name] = 1;
        _table_names.push_back(name);
    }
    cout << "Created table: " <<  name << endl;

}

void SQL:: process_batch(string name)
{
    int count = 0;
    string s;
    fstream f;
    string filename = name + ".txt";
    open_fileRW(f, filename.c_str());
    getline(f, s);
    while(!f.eof())
    {
        if(s[0] == '/')
        {
            cout << endl <<  s << endl;
        }

        else if(s != "")
        {
            cout << endl << endl << "[" << count << "] " << s << endl << endl;
            count++;
            run_command(s);
        }

        getline(f, s);
    }

    f.close();
}






#endif // SQL_H
