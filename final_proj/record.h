#ifndef RECORD_H
#define RECORD_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include "utility_funcs.h"


using namespace std;

typedef vector<string> vectorstr;

class Record
{
public:
    //when you construct a Record, it's either empty or it
    //  contains a word
    Record()
    {
        _record[0][0] = NULL;
        _num_fields = 0;
    }

    Record(const vectorstr& v)
    {
        for (int i = 0; i < MAX_ROWS; i++)
        {
            _record[i][0] = NULL;
        }
        for (int i = 0; i < v.size(); i++) {
            strcpy(_record[i], v[i].c_str());
        }
        _num_fields = v.size();
    }

    vectorstr get_record()
    {
        vectorstr v;
        for (int i = 0; i < MAX_ROWS; i++)
        {
            //change to string and push back
            v.push_back(static_cast<string>(_record[i]));
//            v.push_back(string(_record[i]));
        }

        return v;
    }

    long write(fstream& outs);
    //returns the record number
    long read(fstream& ins, long _recno, int field_num);
    //returns the number of bytes
    //      read = MAX, or zero if
    //      read passed the end of file


    friend ostream& operator<<(ostream& outs, const Record& r)
    {

        for (int i = 0; i < r._num_fields; i++)
        {
            outs   << setw(20) << r._record[i];

        }

        return outs;
    }


private:
    static const int MAX_ROWS = 20;
    static const int MAX_COLS = 50;
    int _num_fields;
    char _record[MAX_ROWS][MAX_COLS];
};

//[    |    |     |    |    |     |]
//-------------------------------------------------



long Record::write(fstream& outs)
{
    //write to the end of the file.

    outs.seekg(0, outs.end);

    long pos = outs.tellp();
    //retrieves the current position of the
    //      file pointer

    outs.write(&_record[0][0], sizeof(_record));

    return pos / sizeof(_record);
    //record number
}

long Record::read(fstream& ins, long _recno, int field_num)
{

    //need to know the num of fields to to be able to print
    _num_fields = field_num;
    long pos = _recno * sizeof(_record);

    ins.seekg(pos, ios_base::beg);

    ins.read(&_record[0][0], sizeof(_record));


    return ins.gcount();

}






#endif // RECORD_H

