#ifndef ADD_ENTRY_H
#define ADD_ENTRY_H


#include <iostream>
#include "oned.h"

using namespace std;

template<typename T>
T* add_entry(T* list, const T& add, int& size, int&capacity);
//Precondition: list is the pointer pointing at array
//add is the element that will be added to array
//Postcondition: size is size of the array after adding the element
//capacity is the capacity of the array that changes
//Returns the new array after adding the new element
template<typename T>
T* remove_entry(T* list, const T& remove, int& size, int& capacity);
//Precondition: list is the pointer pointing at array
//remove is the element that will be removed from the array
//Postcondition: size is size of the array after adding the element
//capacity is the capacity of the array after reallocation
//Returns the new array after removing the new element
template<typename T>
T* add_at_index(T* list, const T& add, int& size, int&capacity,
                const T& pos);
//Precondition: list is the pointer pointing at array
//add is the element that will be added to array
//size and capacity are given values
//pos is the position that the item is placed on array
//Postcondition: size is  size of the array after adding the element
//capacity is the capacity of the array after reallocation
//Returns the new array after adding the new element
template<typename T>
T* remove_at_index(T* list, const T& pos, int& size, int& capacity);
//Precondition: list is the pointer pointing at array
//size and capacity are given values
//pos is the position that the item will be removed from array
//Postcondition: size is size of the array after removing the element
//capacity is the capacity of the array after reallocation
//Returns the new array after removing the element
template<typename T>
T* reallocate(T* old, int size, int capacity);
//Precondition: old is the pointer pointing at the old array before
//reallocating the array for less size
//size and capacity of the array are given values
//Returns the new array after reallocating its capacity
template<typename T>
void shift_left(T* p, T* positionP, int& size);
//Precondition: positionP is the position we start shifting
//P is a pointer pointing at the  array
//Postcondition: size decrements everytime we shift element to  left
template<typename T>
void shift_right(T* p, T* positionP, int& size);
//Precondition: positionP is the position we start shifting
//P is a pointer pointing at the  array
//Postcondition: size increments everytime we shift element to  right





//===============================DEF==================================







template<typename T>
T* reallocate(T* old, int size, int capacity)
{

    T* array = allocate_1d<T>(capacity);
    //create a new array with capacity
    copy(array, old, size);
    //copy elements from initial array to new array
    return array;                 //return array
    deallocate_1d(old);        //deallocates the initial array
}

template<typename T>
T* add_entry(T* list, const T& add, int& size, int& capacity)
{
    T* w = list;


    if(size == capacity)
    {
        capacity = 2 * capacity;
        //new capacity will be twice the old one
        T* new_list = reallocate(list, size, capacity);
        //reallocating new_list array
        T* new_w = new_list;
        //pointer new_list points at the new array with new capacity
        new_w += size;
        //move the pointer to the last position of the array
        *new_w = add;   //put the add element at the end of the array
        size++;                  //increment size of the array
        return new_list;
    }
    else
    {
        w += size;
        //move w to end of the array
        *w = add;
        //add will be added at the end of the array
        size++; //increment sizer
        return list;
    }

}

template<typename T>
T* add_at_index(T* list, const T& add, int& size, int&capacity,
                const T& pos)
{
    T* w = list;


    if(size >= capacity)
    {
       capacity = 2 * capacity;
        T* new_list = reallocate(list, size, capacity);
        //reallocating new_list array
        T* new_w = new_list;
        //pointer new_list points at the new array with new capacity
        shift_right(list, new_w, size);
        //shift everything to the right form new_w
        new_w += pos;
        //move new_w to place pos
        *new_w = add;
        //add will be added at pos
        return new_list;
    }
    else
    {

        shift_right(list, w, size);
        w += pos;
        *w = add;

        return list;
    }

}

template<typename T>
T* remove_entry(T* list, const T& remove, int& size, int& capacity)
{
   T* position = find(list, remove, size);
   //finding the position of the remove element
   shift_left(list,position, size);
   //move each element to the left starting from position
   if(size <= (capacity/4))
   {
      capacity = 0.5 * capacity;
      T* new_list = reallocate(list, size, capacity);
      //reallocate the array to half its size if the size is
      //less than 1/4 of the capacity
      return new_list;                    //return new array
   }
   else
   {
       return list;
   }
}
template<typename T>
T* remove_at_index(T* list, const T& pos, int& size, int& capacity)
{
    T* position = list + pos;
   //finding the position of the remove element
   shift_left(list,position, size);
   //move each element to the left starting from position
   if(size == (capacity/4))
   {
      capacity = 0.5 * capacity;
      T* new_list = reallocate(list, size, capacity);
      //reallocate the array to half its size if the size is
      //less than 1/4 of the capacity
      return new_list;                    //return new array
   }
   else
   {
       return list;
   }
}

template<typename T>
void shift_left(T* p, T* positionP, int& size)
{
    T* shift = (positionP + 1);
    //shift pointer will point at the element next to reported pointer
    //it copies the element from where shift is pointing at to where
    //the positionP points at
    while(shift != p + size)
    {
        *positionP = *shift;
        positionP++;
        //we will move everything forward for next elements to copy
        shift++;
    }
    size--;
    //after each time that we shift to the left, the size decrements

}

template<typename T>
void shift_right(T* p, T* positionP, int& size)
{

    size++; //increment size
    T* shift = (p + (size)); //place shift pointer at the end of array
    T* shift1 = shift - 1;  //place shift1 pointer next to shift
    while(shift1 != positionP)
        //while shift1 hasn't reached the pos for shifting right
    {
        *shift = *shift1; //copy each elemnt from shift1 in shift
        shift1--;       //decrement both pointers
        shift--;
    }


}



#endif // ADD_ENTRY_H
