#include <iostream>
#include "table.h"
#include <iomanip>
#include "parser.h"
#include "sql.h"
#include "shuntingyard.h"
#include "queue"
#include "tokenize.h"
#include "test_bplus_tree.h"



using namespace std;

int main()
{
    SQL q;
    q.run();

//    q.process_batch("sample");

    cout << endl << "Tables Used: " << q.tables_vec() << endl;


//    test_bplus_tree();



    cout <<endl<<endl<<endl<< "==============END=================" << endl;
    return 0;
}


