#ifndef ARRAY_FUNC
#define ARRAY_FUNC

#include <iostream>
#include <vector>

using namespace std;

template <typename T>
T maximal(const T& a, const T& b);
//return the larger of the two items

template <typename T>
void swap_item(T& a, T& b);
//swap the two items

template <typename T>
int index_of_maximal(T data[ ], int n);
//return index of the largest item in data

template <typename T>
void ordered_insert(T data[ ], int& n, T entry);
//insert entry into the sorted array
//data with length n
template <typename T>
int first_ge(const T data[ ], int n, const T& entry);
//return the first element in data that is
//not less than entry
template <typename T>
void attach_item(T data[ ], int& n, const T& entry);
//append entry to the right of data

template <typename T>
void insert_item(T data[ ], int index, int& n, T entry);
//insert entry at index i in data

template <typename T>
void detach_item(T data[ ], int& n, T& entry);
//remove the last element in data and place
//it in entry

template <typename T>
void delete_item(T data[ ], int index, int& n, T& entry);
//delete item at index i and place it in entry

template <typename T>
void merge_array(T data1[ ], int& n1, T data2[ ], int& n2);
//append data2 to the right of data1

template <typename T>
void split(T data1[ ], int& n1, T data2[ ], int& n2);
//move n/2 elements from the right of data1
//and move to data2

template <typename T>
void copy_array(T dest[], const T src[],
                int& dest_size, int src_size);
//copy src[] into dest[]

template <typename T>
void print_array(const T data[], int n, int pos = -1);
//print array data

template <typename T>
bool is_gt(const T data[], int n, const T& item);
//item > all data[i]

template <typename T>
bool is_le(const T data[], int n, const T& item);
//item <= all data[i]
//-------------- Vector Extra operators: ---------------------

template <typename T>
ostream& operator <<(ostream& outs, const vector<T>& list); //print vector list

template <typename T, typename V>
vector<T>& operator +=(vector<T>& list, const V& addme); //list.push_back addme
//-----------------------------------------------------------
template<class T>
T maximal(const T& a, const T& b)
{
    if (a > b)
        return a;
    else
        return b;
}

template<class T>
void swapVals(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

template<class T>
int index_of_maximal(T data[], int n)
{
    T m = data[0];
    int index = 0;
    for(int i=1; i<n; i++)
    {
        if(data[i] > m)
        {
            m = data[i];
            index = i;
        }
    }
    return index;
}

template<class T>
void ordered_insert(T data[], int& n, T entry)
{
    int index = 0;
    //find index of insertion
    while(data[index] < entry && index < n)
    {
        index++;

    }
    insert_item(data, index, n, entry);
}

template<class T>
int first_ge(const T data[], int n, const T& entry)
{
    for (int i = 0; i < n; i++)
    {
        if (data[i] >= entry)
            return i;
    }

    return n;
}

template<class T>
void attach_item(T data[], int& n, const T& entry)
{
    //append to the end
    data[n++] = entry;
}

template<class T>
void insert_item(T data[], int i, int& n, T entry)
{
    if (i != n)
    {

        T hold = data[i];
        data[i++] = entry;

        while (i < n) {
            swapVals(hold, data[i++]);
        }

        data[n++] = hold;

    }
    else
    {
        data[n++] = entry;
    }
}

template<class T>
void detach_item(T data[], int& n, T& entry)
{
    entry = data[--n];
}

template<class T>
void delete_item(T data[], int i, int& n, T& entry)
{
    entry = data[i];

    while (i < n - 1)
    {
        swap(data[i], data[i + 1]);
        i++;
    }

    n--;
}

template<class T>
void merge_array(T data1[], int& n1, T data2[], int& n2)
{
    int size = n1 + n2;
    int i = 0;

    while (n1 < size)
        data1[n1++] = data2[i++];

    //n2 will be zero at this point

}

template<class T>
void split(T data1[], int& n1, T data2[], int& n2)
{
    for (int i = (n1 + 1) / 2; i < n1; i++)
        data2[n2++] = data1[i];
    n1 = (n1 + 1) / 2;
}

template<class T>
void copy_array(T dest[], const T src[], int& dest_size, int src_size)
{
    for (dest_size = 0; dest_size < src_size; dest_size++) {
        dest[dest_size] = src[dest_size];
    }
}

template<class T>
void print_array(const T data[], int n, int pos)
{
    if(n > 0)
    {
        cout << "[";
        for(int i=0; i<n-1; i++)
        {
            cout << data[i] << " ";
        }
        cout << data[n-1] << "]" << endl;
    }
}

template<class T>
bool is_gt(const T data[], int n, const T& item)
{
    for(int i=0; i<n; i++)
    {
        if(item <= data[i])
        {
            return false;
        }
    }
    return true;
}

template<class T>
bool is_le(const T data[], int n, const T& item)
{
    for(int i=0; i<n; i++)
    {
        if(item > data[i])
        {
            return false;
        }
    }
    return true;
}







template<typename T>
ostream& operator<<(ostream& outs, const vector<T>& list)
{
    for (int i = 0; i < list.size(); i++)
    {
        outs << list[i] << " ";
    }

    return outs;
}

template<typename T, typename V>
vector<T>& operator+=(vector<T>& list, const V& addme)
{
    list.push_back(static_cast<T>(addme));
    //list.push_back(addme); might be the issue
    return list;
}
#endif // ARRAY_FUNC
