#ifndef MY_Vector_H
#define MY_Vector_H


#include <iostream>
#include <cassert>
#include "add_entry.h"
#include "oned.h"

using namespace  std;

template <typename T>
class Vector{
public:

    Vector(int capa = 100); //CTOR
    //Precondition: capa is the capacity of the Vector
    //Postcondition allocate capa space for Vector




    // big three:
    Vector(const Vector& other);
    //copy CTOR
    Vector& operator =(const Vector& other);
    //copy operator
    ~Vector();
    //destructor


    //member access functions:
    const T operator [](int index) const;
    //Precondition: index is where we are looking for in Vector
    //Returns a const item at position index
    T& operator [](int index);
    //Precondition: index is where we are looking for in Vector
    //Returns reference to item at position index
    T& at(int index);
    //Precondition: index is where we are looking for in Vector
    //Returns reference to item at position index
    const T at(int index) const;
    //Precondition: index is where we are looking for in Vector
    //Returns a const item at position index
    T& front() const;
    //Return item at position 0
    T& back() const;
    //Return item at the last position


    //Push and Pop functions:
    Vector& operator +=(const T& item);
    //Preconition: item is given value
    //Postcondition: pushes back the item in the Vector
    void push_back(const T& item);
    //Precondition: item is given value
    //Postcondition: append item to the end
    T pop_back();
    //Postcondition: remove last item
    //Returns the item that was removed



    //Insert and Erase:
    void insert(int insert_here, const T& insert_this);
    //Precondition: insert_this is the item we are inserting
    //insert_here is the position that we put insert_this
    //Postcondition: insert_this at position insert_here
    void erase(int erase_index);
    //Precondition: erase_index is position where we remove element
    //Postcondtion: erase item at position erase_index
    int index_of(const T& item);
    //Precondition: item is given value
    //Postcondition: search for item in Vector
    //Returns index of the item


    //size and capacity:
    void set_size(int size, const T& init_value = T());
    //Precondition: size is the desired size
    //Postcondition: initialize how_many elements of Vector to unit
    //Postcondition: initialize Vector to init_value and
    //enlarge the Vector to size
    void set_capacity(int capacity);
    //Precondition: capacity is given value
    //Postcondition: allocates space base on capacity
    int get_size() const;
    //Returns _size
    int get_capacity() const;
    //Returns _capacity


    bool empty() const;
    //Return true if Vector is empty


    //OUTPUT:
    template <class U>
    friend ostream& operator <<(ostream& outs, const Vector<U>& _a);
    //Overloads the << operator so it can be used to output values of
    //type Vector
    //puts a space between elements of the Vector
private:
    int _size;
    int _capacity;
    T* _v;

};

void test_Vector();



//=============================Def====================================

template<typename T>
Vector<T>::Vector(int capa)
{
  _capacity = capa;
  _v = allocate_1d<T>(_capacity); //alocates _capacity for Vector
  _size = 0;
}

template<typename T>
Vector<T>::Vector(const Vector& other)
{
    //copy member variables
    _capacity = other._capacity;
    _size = other._size;


    //3. allocate space for new string
     _v = allocate_1d<T>(_size+1);

    //4. copy everything over
    copy(_v, other._v, _size);
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& other)
{
    //1. check for self-reference
    if (this == &other){
        return *this;
    }
    //2. dealloate existing space;
    deallocate_1d(_v);

    //copy member variables
    _capacity = other._capacity;
    _size = other._size;

    //3. allocate space for new string
    _v = allocate_1d<T>(_size+1);
    //4. copy everything over
    copy(_v, other._v, _size);

    //5. return this object
    return *this;
}

template <typename T>
Vector<T>::~Vector()
{
    deallocate_1d(_v);
}

template <typename T>
const T Vector<T>:: operator [](int index) const
{
    assert(index < _size);  //end the program if index is out of size
    assert(index >= 0);
    return (*(_v + index)); //moves pointer _v to the index position
}

template <typename T>
T& Vector<T>:: operator [](int index)
{
    assert(index < _size); //end the program if index is out of size
    assert(index >= 0);
    return (*(_v + index)); //moves pointer _v to the index position
}

template<typename T>
T& Vector<T>:: at(int index)
{
    assert(index < _size); //end the program if index is out of size
    assert(index >= 0);
    return (*(_v + index)); //moves pointer _v to the index position
}

template<typename T>
const T Vector<T>:: at(int index) const
{
    assert(index < _size); //end the program if index is out of size
    assert(index >= 0);
    return (*(_v + index)); //moves pointer _v to the index position
}

template<typename T>
T& Vector<T>:: front() const
{
    return (*_v); //pointer points at the first element

}

template<typename T>
T& Vector<T>:: back() const
{
    return (*(_v + (_size-1))); //pointer points at the last element
}

template <typename T>
Vector<T>& Vector<T>::operator +=(const T& item){
    T* at = _v + _size; //move the pointer to the end of array
    *at = item; //insert item there
    _size++; //increment size
    return *this;

}

template <typename T>
void Vector<T>:: push_back(const T& item)
{

    _v = add_entry(_v, item, _size, _capacity);
    //check for reallocation and add item to the end of Vecotr
}

template<typename T>
T Vector<T>::pop_back()
{
    T* pos = _v + (_size-1);//moves pointer to the last item in Vector
    _v = remove_entry(_v, *pos, _size, _capacity);
    //check for reallocation and remove item from the end of Vecotr
    return *pos;
}

template <typename T>
void Vector<T>::insert(int insert_here, const T& insert_this)
{
    assert(insert_here < _size);
    //end program if index is greater than size
    _v = add_at_index(_v, insert_this, _size, _capacity, insert_here);

    //check for reallocation and add item at insert_here in Vecotr
    //shift everything to the left from pos insert_here

}

template <typename T>
void Vector<T>::erase(int erase_index)
{
    assert(erase_index < _size);
    _v = remove_at_index(_v, erase_index, _size, _capacity);
    //check for reallocation and remove item from pos
    //shift everything to the left from pos erase_index

}

template <typename T>
int Vector<T>::index_of(const T& item)
{
    T* found = find(_v, item, _size); //look for item
    return (found - _v);
    //subtract items place from the beginning of the array
    //which gives us the int index of the item found
}
template <typename T>
void Vector<T>::set_size(int size, const T& init_value)
{
     _size = size;
    if(size >= _capacity)
    {
        _capacity = _capacity *2;
        //double the capacity if size is greater than size
        _v = reallocate(_v, _size, _capacity);
        //reallocate _v to new capacity
    }
    if(size <= (_capacity/4))
    {
        _capacity = _capacity * 0.5;
        //cut the capacity in half if size is greater than size
        _v = reallocate(_v, _size, _capacity);
        //reallocate _v to new capacity
    }

    init_1d(_v, _size, init_value);
    //initialize _v and _size to init_value
}

template <typename T>
void Vector<T>::set_capacity(int capacity)
{
    _capacity = capacity;
    assert(_capacity >= _size);
    //end program if new capacity is less than _size
    _v = reallocate(_v, _size, _capacity);
    //reallocate _v to new capacity
}

template <typename T>
int Vector<T>::get_size()const
{
    return _size;
}

template<typename T>
int Vector<T>::get_capacity()const
{

    return _capacity;
}

template<typename T>
bool Vector<T>:: empty() const
{
    return (_size == 0); //returns true if array is empty
}

template <typename U>
ostream& operator<<(ostream& outs, const Vector<U>& v)
{
    print(v._v, v._size);      //print Vector
    return outs;

}

#endif // MY_Vector_H
