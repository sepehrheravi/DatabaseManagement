#ifndef TABLE_H
#define TABLE_H


#include "record.h"
#include "!includes/mmap.h"
#include "!includes/map.h"
#include "rpn.h"
#include "shuntingyard.h"
#include "tokenize.h"


#include <iomanip>

class Table
{
public:

    //CTOR
    Table(const string& name, const vectorstr fields);
    Table(const string& name);

    //Insert in the table
    void insert_into(vectorstr vec);

    //select functions

    //for select all
    Table select_all();
    //for select with fields only
    Table select_col(vectorstr v);

    //for select with fields and condition
    Table select_col_cond(vectorstr v, vectorstr cond);

    //for select condition only
    Table select_cond(vectorstr cond);


    //get field_names
    vectorstr get_field();


    friend ostream& operator <<(ostream& outs, const Table& t)
    {
        fstream f;
        Record r;
        outs << endl << endl;

        //extra to know number of records
        int count = 0;
        open_fileRW(f, t._fname.c_str());
        r.read(f, count, t._field_names.size());

        while (!f.eof())
        {
            count++;
            r.read(f, count, t._field_names.size());

        }

        f.close();



        outs << "Table name: " << t._name << " - Records: " << count << endl
             << endl;
        outs << "rec";

        //inserting _field_names from field names file
        for (unsigned int i = 0; i < t._field_names.size(); i++)
        {
            outs  << setw(20) << t._field_names[i];
        }
        outs << endl << endl;



        open_fileRW(f, t._fname.c_str());

        int recno = 0;
        r.read(f, recno, t._field_names.size());

        while (!f.eof())
        {
            outs << "[" << recno << "]" << r << endl;
            recno++;
            r.read(f, recno, t._field_names.size());
        }

        f.close();

        return outs;
    }

    void reindex();
    void set_fields(vectorstr fields);


//    void check(Vector<SToken*> s);
private:

    string _name;
    string _fname;
    vector<MMap<string, long> > _indices;                             
    vectorstr _field_names;
    Map<string, int> _field_map;
    static int _serial;

};

//==================================================================

int Table::_serial;

Table::Table(const string& name, const vectorstr fields): _name(name)
{
    _serial++;
    fstream f;

    _fname = _name + ".tbl";

    //get ride of existing if we were to overwriteit
    f.open(_fname, std::ofstream::out | std::ofstream::trunc);
    f.close();



    //get ride of existing if we were to overwriteit
    f.open(_name + "_fields.txt", std::ofstream::out | std::ofstream::trunc);
    f.close();

    //crating the file
    open_fileW(f, _fname.c_str());
    f.close();

    set_fields(fields);

    open_fileRW(f, (_name + "_fields.txt").c_str());

    //put it like binary and it crashed so chaned it to txt file

//    Record r(fields);

//    r.write(f);

    //write into normal text file
    unsigned int count = 0;

    for (;count < fields.size()-1; count++)
    {
        f << fields[count] << endl;
    }

    f << fields[count];


//    for (;count < fields.size(); count++)
//    {
//        f << fields[count] << endl;
//    }


    f.close();
}

Table::Table(const string& name): _name(name)
{

    //used a tbl file to put field name but didn't quite work
//    name = name;

//   //create file name

//   _fname = _name +".tbl";

//   //create file
//   fstream f;
//   Record r;


//   open_fileRW(f, _fname.c_str());
//   int recno = 0;
//   r.read(f, recno);
//   vectorstr field = r.get_record();
//   set_fields(field);
//   reindex();
//   f.close();
    bool debug = false;
    _fname = name + ".tbl";
    fstream f;
    string field;


    open_fileW(f, (_name + "_fields.txt").c_str());


    vectorstr field_vector;

    //creating field_vector names
    //reading from .txt file
    while (!f.eof())
    {
        getline(f, field);
        field_vector.push_back(field);
    }

    set_fields(field_vector);

    //creating indices vec of MMap
    reindex();

    if(debug)cout << "IND: " << endl;
    if(debug)cout << _indices << endl;

    f.close();
}

void Table::set_fields(vectorstr fields)
{
    for (unsigned int i=0; i<fields.size(); i++)
    {
        //1. push back field names
        _field_names.push_back(fields[i]);

        //2.create _field_map
        _field_map[fields[i]] = i;

        //3.create _indices vector of Mmap
        _indices.push_back(MMap<string, long>());
    }
}

vectorstr Table::get_field()
{
    return _field_names;
}

void Table::reindex()
{
    fstream f;

    //open our binary file
    open_fileRW(f, _fname.c_str());

    Record r;
    int recno = 0;

    //read record [0]
    r.read(f, recno, _field_names.size());

    //for storing each record info
    vectorstr record_vec;

    while (!f.eof())
    {
        //store record info
        record_vec = r.get_record();

        //for the size of out _indeces vec
        //since each record has the same size as _indeices size
        for (unsigned int i=0; i<_indices.size(); i++)
        {

            //each info gets stored in one Mmap
            _indices[i][record_vec[i]] += recno;
        }

        //read next
        recno++;
        r.read(f, recno, _field_names.size());
    }

    f.close();
}

void Table::insert_into(vectorstr vec)
{
    fstream f;

    open_fileRW(f, _fname.c_str());

    Record r(vec);

    //writing into tbl file
    int recno = r.write(f);

    //we just know the size of _indices which is size of vector of fields
    for (unsigned int i = 0; i < _indices.size(); i++)
    {
        //insert each info of record into its own Mmap
        _indices[i][vec[i]] += recno;
    }

    f.close();
}


Table Table::select_all()
{
    fstream f;

    open_fileRW(f, _fname.c_str());

    int recno = 0;

    //new table with ++ serial
    string new_file = _name + to_string(_serial);
    vectorstr new_field = _field_names;

    Table temp(new_file, new_field);

    Record r;
    r.read(f, recno, _field_names.size());

    while (!f.eof())
    {
        //inserting each item into new table
        //it gets written into table file a well
        temp.insert_into(r.get_record());

        //write next record
        recno++;
        r.read(f, recno, _field_names.size());
    }

    f.close();

    return temp;
}




Table Table::select_col(vectorstr v)
{
    bool debug = false;
    fstream f;
    Record r;

    string tname = _name + to_string(_serial);


    open_fileRW(f, _fname.c_str());

    int recno = 0;



    vector<long> field_vec;
    for(unsigned int i=0; i<v.size(); i++)
    {
        //push back indices or cols that you want into new vec
        field_vec.push_back(_field_map[v[i]]);
        if(debug) cout << field_vec << endl;
    }
    Table temp(tname, v);

    r.read(f, recno, _field_names.size());

    while (!f.eof())
    {
        vectorstr rec;
        for(unsigned int i=0; i<field_vec.size(); i++)
        {
            rec.push_back(r.get_record()[field_vec[i]]);

        }

        //insert items we want into temp file not putting the field
        temp.insert_into(rec);
        recno++;
        r.read(f, recno, get_field().size());
    }

    f.close();

    return temp;

}


//void Table::check(Vector<SToken*> s)
//{

//    RPN r(s);
//    for(int i=0; i<s.get_size(); i++)
//    {
//        s[i]->print(cout);
//    }
//    cout << endl;

//    cout << r.get_record(_field_map, _indices);

//}

Table Table::select_col_cond(vectorstr v, vectorstr cond)
{
    bool debug = false;
    Tokenize tk;

    //get tokenied vector of SToken*
    Vector<SToken*> q = tk.tokenize(cond);

    //using shunting yard algo getting post_fix vector
    Shunting_yard sh(q);
    Vector<SToken*> post = sh.postfix();

    //using rpn turning postfix into vector of recnos
    RPN rp(post);
    vector<long> condition_recno = rp.get_record(_field_map, _indices);
    if(debug) cout << condition_recno << endl;


    fstream f;
    Record r;

    string tname = _name + to_string(_serial);


    open_fileRW(f, _fname.c_str());


    vector<long> field_vec;
    for(unsigned int i=0; i<v.size(); i++)
    {
        //push back indices or cols that you want into new vec
        field_vec.push_back(_field_map[v[i]]);
        if(debug) cout << field_vec << endl;
    }

    if(debug) cout << field_vec << endl;
    Table temp(tname, v);



    for(unsigned int i=0; i<condition_recno.size(); i++)
    {
        r.read(f, condition_recno[i], _field_names.size());
        vectorstr rec;
        for(unsigned int i=0; i<field_vec.size(); i++)
        {
            rec.push_back(r.get_record()[field_vec[i]]);

        }

        //insert items we want into temp file not putting the field
        temp.insert_into(rec);

    }

    f.close();
    return temp;

}


Table Table::select_cond(vectorstr cond)
{
    //same process as select_cond_col but
    //this time there is no specific field requested so we output all records
    bool debug = false;
    Tokenize tk;
    Vector<SToken*> q = tk.tokenize(cond);
    Shunting_yard sh(q);
    Vector<SToken*> post = sh.postfix();
    RPN rp(post);

    vector<long> condition_recno = rp.get_record(_field_map, _indices);
    if(debug) cout << condition_recno << endl;


    fstream f;
    Record r;

    string tname = _name + to_string(_serial);


    open_fileRW(f, _fname.c_str());


    vector<long> field_vec;
    for(unsigned int i=0; i<_field_names.size(); i++)
    {
        //push back indices or cols that you want into new vec
        field_vec.push_back(_field_map[_field_names[i]]);
        if(debug) cout << field_vec << endl;
    }

    if(debug) cout << field_vec << endl;
    Table temp(tname, _field_names);



    for(unsigned int i=0; i<condition_recno.size(); i++)
    {
        r.read(f, condition_recno[i], _field_names.size());
        vectorstr rec;
        for(unsigned int i=0; i<field_vec.size(); i++)
        {
            rec.push_back(r.get_record()[field_vec[i]]);

        }

        //insert items we want into temp file not putting the field
        temp.insert_into(rec);

    }

    f.close();
    return temp;

}




#endif // TABLE_H

