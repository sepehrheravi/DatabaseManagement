#ifndef ONED_H
#define ONED_H

#include <iostream>
using namespace std;

template<typename T>
void copy(T* dest,T* src, int size);
//Precondition: using pointer src copy the elements from src array
//to desr array, n is the size of arrays
//Postcondition: pointer dest copies elements from array src to dest
template<typename T>
void print(T* arr, int size);
//Precondition: size is the size of the array
//Postcondotion: arr is the pointer poinitng to the array to print
template<typename T>
T* find(T* p, T target, int size);
//Precondition: target which we define and function will look fot it
//size is the elements inside array
//Postcondition: P is a pointer pointing to the  array
//Returns the location of the target found
template<typename T>
T* allocate_1d(int capacity);
//Precondition: capacity is space that new array will be allocated
//Returns the array after being allocated the desired space
template<typename T>
void deallocate_1d(T* sizes);
//Postcondition: sizes array will be deallocated
template<typename T>
void init_debug_1d(T* sizes, int size, int number);
//Precondition: size is the size of our array
//number is the number that is used to set the elements to it
//Postcondition: initializes the elements in sizes array to different
//values
template<typename T>
void init_1d(T* sizes, int size, const T& init_value = T());
//Precondition: size is the size of our array
//number is the number that is used to set the elements to it
//init_value is the value that we initialize array sizes with
//Postcondition: array sizes will be initialized with init_value
template<typename T>
T* resize(int size);
//Precondition: size is space that new array will be resized tp
//Returns the array after being resized the desired space

//===================================================================


template<typename T>
T* allocate_1d(int capacity)
{
    return new T[capacity];         //allocates a 1D dynamic array
}

template<typename T>
T* find(T* p, T target, int size)
{
    bool found = false;
    //Returns true if target found and false if
    
    while((!found)&& (p < p + size))
        
    {
       if(*p == target)
                                            
           found = true;        //returns true if target is found
        else
            p++;        //continue to search if target is not found
    }
    if(found)
        return p;    //if the target get found it returns the address
    else
        return nullptr;
    //otherwise keeps giong until reaches the end and returns nullptr
}


template<typename T>
void copy(T* dest,T* src, int size)
{
    for(int i=0; i<size; i++)
    {
        *dest = *src;
        //copying everything from src array to dest array
        src++;
        dest++;            //increment both src and dest pointers
    }
}

template<typename T>
void print(T* arr, int size)
{
    for(int i=0; i<size; i++)
    {
        cout << "[" << *arr <<  "]->";
        //using pointer arr print each elemnt in array
        arr++;
    }
    cout << "|||";
    cout << endl;
}

template<typename T>
void deallocate_1d(T* sizes)
{
    delete [] sizes;
    //deallocates the space for sizes array
}

template<typename T>
void init_1d(T* sizes, int size, const T& init_value)
{
    for(int i=0; i<size; i++)
    {
        if(*sizes != 0)
        {
            size++;  //if there is value in array keep the value
        }
        else
            *sizes = init_value; //pointer sizes points at elements in
                      //sizes array and set their values to uni_value
            sizes++;
            //move the pointer to next element

    }
}

template<typename T>
void init_debug_1d(T* sizes, int size, int number)
{
    for(int i=0; i<size; i++)
    {
        *sizes = number;        //pointer sizes points at elements in
                        //sizes array and set their values to number
        number++;
   //increment number since we want different values for each element
        sizes++;                 //move the pointer to next element
    }
}
template<typename T>
T* resize(int size)
{
    return new T[size];         //resizes a 1D dynamic array
}

#endif // ONED_H
