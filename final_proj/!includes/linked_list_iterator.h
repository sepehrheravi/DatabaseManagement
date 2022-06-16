#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include "node.h"

using namespace std;

template <typename T>
class List
{
public:
    class Iterator
    {
    public:
        friend class List;
        //give access to list to access _ptr

        Iterator(): _ptr(NULL)
        {
            //def ctor
        }

        Iterator(node<T>* p): _ptr(p)
        {
            //ctor
        }

        Iterator next()
        {
            return Iterator(_ptr = _ptr->_next);
            //return an iterator to the next location in the list
        }

        T& operator *()
        {
            assert(_ptr);
            return _ptr->_item;
            //returns the item where iterator points at
        }

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
            //returns the address of the item where iterator points at
        }

        const T* operator ->()const
        {
            assert(_ptr);
            return &(_ptr->_item);
            //returns the address of the item where iterator points at
        }

        const T& operator[](int index)const
        {
            assert(_ptr);
            //call at function
           return at(_ptr, index);
           //return item at index
        }

        T& operator[](int index)
        {
            assert(_ptr);
            //call at function
           return at(_ptr, index);
           //return item at index
        }

        //true if _ptr is NULL
        bool is_null()
        {
            return (_ptr == NULL);
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

//        member operator: ++it; or ++it = new_value
        Iterator& operator++()
        {
           _ptr = _ptr->_next;
           return *this;
        }

        //friend operator: it++
        friend Iterator operator++(Iterator& it,int unused)
        {
            Iterator hold;
            hold = it;
            it.next();
            return hold;
        }

        node<T>* get_ptr()
        {
           return _ptr;
        }

    private:
        node<T>* _ptr;
        //pointer being encapsulated
    };

    List();
    //default ctor
    List(Iterator it);

    //big 3 functions:
    List(const List<T>& copy_this);
    //copy ctor
    List& operator =(const List& rhs);
    //assignment operator
    ~List();
    //dtor

    Iterator begin_i()const;
    //Returns Iterator at the head of the List
    Iterator end_i()const;
    //Returns Iterator to NULL
    Iterator insert_head_i(const T& item);
    //Precondition: item to insert at head
    //Postcondition: insert item at the head of List
    //Reutnrs Iterator to item
    Iterator insert_after_i(const T& item, Iterator mark);
    //Precondition: item to insert at head
    //item get inserted after mark
    //Postcondition: insert item after mark
    //Reutnrs Iterator to item
    Iterator insert_before_i(const T& item, Iterator mark);
    //Precondition: item to insert at head
    //item get inserted before mark
    //Postcondition: insert item before mark
    //Reutnrs Iterator to item
    Iterator insert_sorted_i(const T& item);
    //Precondition: item to insert in sorted matter
    //item get inserted in sorted matter
    //Postcondition: insert item in sorted matter
    //Reutnrs Iterator to item
    T delete_node_i(List<T>::Iterator mark);
    //Precondition: delete at mark
    //Postcondition: delete node at mark
    //Reutnrs deleted item
    Iterator search_list_i(const T& key);
    //Precondition: key to find
    //Postcondition: find key
    //Reutnrs Iterator to key
    Iterator next_node_i(Iterator mark);
    //Precondition: next node after mark
    //Postcondition: next node after mark
    //Reutnrs Iterator to next node
    Iterator previous_node_i(Iterator mark);
    //Precondition: prev node after mark
    //Postcondition: prev node after mark
    //Reutnrs Iterator to prev node
    Iterator last_node_i();
    //Returns Iterator to last node
    bool empty()const;
    //Returns true if empty
    T remove_head();
    //Postcondition: deletes head
    //Returns deleted item
    T& operator[](int index);
    //Precondition:index is position in the list
    //Postcondition: finds the item at index in the list
    //Returns the item at index
    //Postcondition: head will get removed
    //Returns the item that was removed
    ostream& print_list(ostream& outs = cout);
    //Postcondition: prints the list
    //Returns ostream
    void clear_list_i();
    Iterator copy_list_i();


//    overloading insertion operator
    friend ostream& operator <<(ostream& outs, const List<T>& l){
    for(Iterator it=l.begin_i(); it!=l.end_i(); it++)
    {
        outs<< *it<<"|";
    }
    return outs;
    }





private:
    node<T>* insert_head(const T& item);
    //Precondition: item is the item we are inserting
    //Postcondition: item gets inserted at the pos head
    //Returns the new ptr pointing at head  
    node<T>* insert_after(const T& item, node<T>* mark);
    //Precondition: mark is pos where item inserted after
    //item is the item we are inserting
    //Postcondition: item gets inserted after the pos mark
    //Returns the address of node with item
    node<T>* insert_before(const T& item, node<T>* mark);
    //Precondition: mark is pos where item inserted before
    //item is the item we are inserting
    //Postcondition: item gets inserted before the pos mark
    //Returns the address of node with item
    node<T>* insert_sorted(const T& item);
    //Precondition: item is the item we are inserting
    //Postcondition: item gets inserted in order of the list
    //Returns address of node item got inserted in
    T delete_node(node<T>* mark);
    //Precondition: mark is pos where we want to delete the node
    //Postcondition: remove the item at mark
    //Returns the item removed
    node<T>* search_list(const T& key);
    //Precondition: key is the item we are looking for
    //Postcondition: finds the key
    //Returns the address for node with item or NULL if not found
    node<T>* next_node(node<T>* mark);
    //Precondition: mark is pos where we want the node after
    //Postcondition: next node will be gotten
    //Returns the ptr pointing at next node
    node<T>* previous_node(node<T>* mark);
    //Precondition: mark is pos where we want the node before
    //Postcondition: previous node will be gotten
    //Returns the ptr pointing at previous node
    node<T>* last_node_l();
    node<T>* begin() const;
    //Postcondition: finds the head in the list
    //Returns the location of last item
    node<T>* end() const;
    //Postcondition: finds the tail in the list
    //Returns the location of last item


    node<T>* _head_ptr;
};

template<typename T>
typename List<T>:: Iterator List<T>::begin_i()const
{
    return Iterator(begin());
}

template<typename T>
typename List<T>:: Iterator List<T>::end_i()const
{
    return Iterator(NULL);
}

template<typename T>
typename List<T>:: Iterator List<T>::insert_head_i(const T& item)
{
    return Iterator(insert_head(item));
}

template<typename T>
typename List<T>:: Iterator List<T>::insert_after_i(const T& item,
                                                  Iterator mark)
{
    return Iterator(insert_after(item, mark._ptr));

}

template<typename T>
typename List<T>:: Iterator List<T>::insert_before_i(const T& item,
                                                   Iterator mark)
{
    return Iterator(insert_before(item, mark._ptr));
}


template<typename T>
T List<T>::delete_node_i(List<T>::Iterator mark)
{
    return delete_node(mark._ptr);
}

template<typename T>
typename List<T>:: Iterator List<T>::insert_sorted_i(const T& item)
{
    return Iterator(insert_sorted(item));
}

template<typename T>
typename List<T>:: Iterator List<T>::search_list_i(const T& key)
{
    return Iterator(search_list(key));
}

template<typename T>
typename List<T>:: Iterator List<T>::next_node_i(Iterator mark)
{
    return Iterator(next_node(mark._ptr));
}

template<typename T>
typename List<T>:: Iterator List<T>::previous_node_i(Iterator mark)
{
    return Iterator(previous_node(mark._ptr));
}

template<typename T>
typename List<T>:: Iterator List<T>:: last_node_i()
{
    return Iterator(last_node_l());
}

template<typename T>
typename List<T>::Iterator List<T>::copy_list_i()
{
    return(Iterator(copy_list(_head_ptr)));
}

template <typename T>
List<T>::List(Iterator it)
{
    _head_ptr = it._ptr;
}

template <typename T>
List<T>::List():_head_ptr(NULL)
{
    //blank
}

template<typename T>
List<T>::List(const List<T>& copy_this)
{
     //2. dealloate existing space;
    _head_ptr = copy_list(copy_this._head_ptr);
}

template<typename T>
List<T>& List<T>::operator =(const List& rhs)
{
    //1. check for self-reference
    if (this == &rhs)
    {
        return *this;
    }
    //2. dealloate existing space;
    clear_list(_head_ptr);

   //3. allocate space and copy everything over
   _head_ptr = copy_list(rhs._head_ptr);

    //4. return this object
    return *this;
}

template<typename T>
List<T>::~List()
{
    clear_list(_head_ptr);
//dealloate existing space;
}

template <typename T>
node<T>* List<T>::insert_head(const T& item)
{
    //call _insert_head function
    return _insert_head(_head_ptr, item);
}

template <typename T>
T List<T>::remove_head()
{
    //call _remove_head function
    return _remove_head(_head_ptr);
}

template <typename T>
node<T>* List<T>::insert_after(const T& item, node<T>* mark)
{
    //call _insert_after function
    return _insert_after(_head_ptr, mark, item);
}

template <typename T>
node<T>* List<T>::insert_before(const T& item, node<T>* mark)
{
    //call _insert_before function
    return _insert_before(_head_ptr, mark, item);
}

template <typename T>
node<T>* List<T>::insert_sorted(const T& item)
{
    //call _insert_sorted function
    return _insert_sorted(_head_ptr, item);
}

template <typename T>
T List<T>::delete_node(node<T>* mark)
{
    //call _delete_node function
    return _delete_node(_head_ptr, mark);
}

template <typename T>
node<T>* List<T>::search_list(const T& key)
{
    //call _search_list function
    return _search_list(_head_ptr, key);
}

template <typename T>
node<T>* List<T>::next_node(node<T>* mark)
{
    //call _next_node function
    return _next_node(_head_ptr, mark);
}

template <typename T>
node<T>* List<T>::previous_node(node<T>* mark)
{
    //call _previous_node function
    return _previous_node(_head_ptr, mark);
}

template <typename T>
T& List<T>::operator[](int index)
{
    //call at function
   return at(_head_ptr, index);
}

template <typename T>
node<T>* List<T>:: begin() const
{
    //return head of list
    return _head_ptr;
}

template <typename T>
node<T>* List<T>:: end() const
{
    //call last_node function
    return last_node(_head_ptr);
}

template<typename T>
bool List<T>::empty()const
{
    if(_head_ptr == NULL)
        return true;
    else
        return false;
}


template <typename T>
ostream& List<T>::print_list(ostream& outs)
{
    //call print function
   return _print_list(_head_ptr,outs);
}

template <typename T>
node<T>* List<T>:: last_node_l()
{
    return last_node(_head_ptr);
}

template <typename T>
void List<T>::clear_list_i()
{
   clear_list(_head_ptr);
}


#endif // LINKED_LIST_H
