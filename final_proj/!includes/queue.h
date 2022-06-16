#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "!includes/linked_list_iterator.h"

using namespace std;
template <typename T>
class Queue
{
public:
    class Iterator
    {
    public:
        friend class Queue;
        Iterator(node<T>* p = NULL): _ptr(p)
        {
           //ctor
        }
        Iterator(typename List<T>::Iterator it): _ptr(it.get_ptr())
        {
           //ctor

            //all the function in List class return List::Iterator
            //which is different than Queue::Iterator so I defined a
            //ctor to return a Queue::Iterator using List::Iterator

        }

        Iterator next()
        {
            assert(_ptr);
            return Iterator(_ptr = _ptr->_next);
            //return an iterator to the next location in the list
        }

        T& operator *()
        {
            assert(_ptr);
            return _ptr->_item;
        }
        //do not give outsiders access to alter anything


        const T& operator *()const
        {
            assert(_ptr);
            return _ptr->_item;
            //returns the item where iterator points at
        }

        T* operator ->()
        {
            assert(_ptr);
            return &(_ptr->_item);
        }
        //do not give outsiders access to alter anything

        const T* operator ->()const
        {
            assert(_ptr);
            return &(_ptr->_item);
            //returns the address of the item where iterator points at
        }

        //true if _ptr is NULL
        bool is_null()
        {
            return (_ptr == NULL);
        }

        const T& operator[](int index)const
        {
            assert(_ptr);
            //call at function
           return at(_ptr, index);
           //return item at index
        }

        //friend operator: it++
        friend Iterator operator ++(Iterator& it, int unused)
        {
            assert(it._ptr);
            Iterator hold;
            hold = it;
//            it.next();
             it._ptr = it._ptr->_next;
            return hold;
        }

        //member operator: ++it
        Iterator& operator ++()
        {
            assert(_ptr);
           _ptr = _ptr->_next;
           return *this;
        }

        //true if left != right
        friend bool operator !=(const Iterator& left,
                                const Iterator& right)
        {
            return left._ptr != right._ptr;
        }

        //true if left == right
        friend bool operator ==(const Iterator& left,
                                const Iterator& right)
        {
            return left._ptr == right._ptr;
        }

    private:
        node<T>* _ptr;

    };

    Queue();
    //default ctor

    //big 3 functions:
    Queue(const Queue<T>& copy_this);
    //copy ctor
    Queue& operator =(const Queue& rhs);
    //assignment operator
    ~Queue();
    //dtor
    Iterator begin()const;
    //Returns Iterator to the head node
    Iterator end()const;
    //Returns Iterator points at NULL
    Iterator push(const T& item);
    //Precondition: item to insert
    //Postcondition: item will be inserted in Queue
    //Returns Iterator at item
    T pop();
    //Postcondition: top item will be removed fronm Queue
    //Returns removed item
    T front();
    //Returns front of the Queue
    bool empty()const;
    //Returns true if list is empty

    //overloading insertion operator
    friend ostream& operator <<(ostream& outs, const Queue<T>& q)
    {
        outs<<"[F]";
        for(Queue<T>::Iterator it=q.begin(); it!=q.end(); it++)
        {

            outs<< "<-[" << *it <<"]";
        }
        outs << "<-[END]";
        return outs;
    }
private:
    List<T> _q;
    typename List<T>::Iterator _rear;
};

//=========================Definition================================

template <typename T>
Queue<T>::Queue(): _q()
{
    _rear = NULL;
    //blank
}

template<typename T>
Queue<T>::Queue(const Queue<T>& copy_this)
{
    List<T> c = copy_this._q;
     //2. dealloate existing space;


    _q = c.copy_list_i();
    _rear = _q.last_node_i();
}

template<typename T>
Queue<T>& Queue<T>::operator =(const Queue& rhs)
{
    //1. check for self-reference
    if (this == &rhs)
    {
        return *this;
    }
    //2. dealloate existing space;
    _q.clear_list_i();

    List<T> c = rhs._q;

   //3. allocate space and copy everything over
   _q = c.copy_list_i();
   _rear = _q.last_node_i();

    //4. return this object
    return *this;
}

template<typename T>
Queue<T>::~Queue()
{
    _q.clear_list_i();
//dealloate existing space;
}

template<typename T>
typename Queue<T>:: Iterator Queue<T>::begin()const
{
    return Iterator(_q.begin_i());
}

template<typename T>
typename Queue<T>:: Iterator Queue<T>::end()const
{
    return Iterator(_q.end_i());
}

template<typename T>
typename Queue<T>:: Iterator Queue<T>::push(const T& item)
{
    if(_q.begin_i() == NULL)
    {

        return  Iterator(_rear = _q.insert_head_i(item));
    }
    else
    {
        return  Iterator(_rear = _q.insert_after_i(item, _rear));
    }

}

template<typename T>
T Queue<T>::pop()
{
    assert(!empty());
    T hold = _q.remove_head();
    if(_q.empty())
    {
        _rear = typename List<T>::Iterator(NULL);
    }
    return hold;
}


template<typename T>
T Queue<T>::front()
{
    assert(!empty());
    return *(_q.begin_i());
}

template<typename T>
bool Queue<T>::empty()const
{
    if(_q.begin_i() == NULL)
        return true;
    else
        return false;
}

#endif // QUEUE_H
