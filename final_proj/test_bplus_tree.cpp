#include "test_bplus_tree.h"

const int SIZEMAX = 300;
void test_bplus_tree()
{
    BPlusTree<int> bpt;
    int a[SIZEMAX];
    int how_many = 200;
    for (int i= 0; i< how_many; i++)
    {
            a[i] = i;
            bpt.insert(i);
    }
    cout << bpt << endl;
    //shuffle a[ ]: Put this in a function!
    for (int i = 0; i< how_many; i++)
    {
        int from = Random(0, how_many-1);
        int to = Random(0, how_many -1);
        int temp = a[to];
        a[to] = a[from];
        a [from] = temp;
    }

    for(int i=0; i<how_many; i++)
    {
        cout << "Removing: " << a[i] << endl << endl;
        bpt.remove(a[i]);
        cout << bpt << endl;
    }

    if(bpt.empty())
    {
        cout << "Tree fully removed" << endl;
    }


}


int Random(int lo, int hi)
{
    int r = rand()%(hi-lo+1)+lo;

    return r;
}
