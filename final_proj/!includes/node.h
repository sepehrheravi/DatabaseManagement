#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <cassert>
using namespace std;


template <typename T>
struct node
{
  T _item;
  node<T>* _next;
  node<T>* _prev;

  node():_item(0), _next(NULL)
  {
     //blannk
      //default ctor
  }
  node(const T& item=T(), node<T>* next = nullptr, node<T>* prev = nullptr):
                    _item(item), _next(next), _prev(prev)
  {
    //blank
      //ctor
  }
    //overloading insertion operator
    friend ostream& operator<<(ostream& outs, const node<T>& n)
    {
        outs<< n._item;
        //show item stored in nodes
        return outs;
    }
};

template<typename T>
node<T>* _previous_node(node<T>* head_ptr, node<T>* mark);
template <typename T>
T _delete_node(node<T>*& head_ptr,  node<T>* mark);





template<typename T>
node<T>* _insert_head(node<T>*& head_ptr, const T& item);
//Precondition: head_ptr points at head of list
//item is the item we are inserting
//Postcondition: item gets inserted at the pos head
//Returns the new ptr pointing at head
template<typename T>
T _remove_head(node<T>*& head_ptr);
//Precondition: head_ptr points at head of list
//Postcondition: head gets removed
//Returns the item that got removed
template<typename T>
node<T>* _insert_after(node<T>*& head_ptr, node<T>* mark,
                       const T& item);
//Precondition: head_ptr points at head of list
//mark is pos where item inserted after
//item is the item we are inserting
//Postcondition: item gets inserted after the pos mark
//Returns the address of node with item
template <typename T>
node<T>* _insert_before(node<T>*& head_ptr, node<T>* mark,
                        const T& item);
//Precondition: head_ptr points at head of list
//mark is pos where item inserted before
//item is the item we are inserting
//Postcondition: item gets inserted before the pos mark
//Returns the address of node with item
template <typename T>
node<T>* copy_list(const node<T>* head_ptr, node<T>*& cpy);
//Precondition: head_ptr points at head of list
//Postcondition: list will get duplicated
//Returns the ptr pointing at duplicated list
template <typename T>
void clear_list(node<T>*& head_ptr);
//Precondition: head_ptr points at head of list
//Postcondition: all the nodes will be removed from list
template <typename T>
ostream& _print_list(node<T>* head_ptr, ostream& outs = cout);
//Precondition: head_ptr points at head of list
//Postcondition: prints the list
//Returns ostream

template <typename T>
bool is_empty(const node<T>* head_ptr);

//======================
template<typename T>
node<T>* _insert_head(node<T>*& head_ptr, const T& item)
{

     //1: create a new node:
    node<T>* temp = new node<T>(item);
    if(isempty(head_ptr))
    {
        head_ptr = temp;
    }
    else
    {
    //insert the item at the head_ptr of the list: make it the first
    //      link in the chain.


    head_ptr->_prev= temp;
    //2. point (the next field of) this new node to where head_ptr is
    //pointing to
    temp->_next = head_ptr;

//    head_ptr->_prev = temp;

    //3. point head_ptr to this new node:
    head_ptr = temp;
    }

    return head_ptr;
}

template<typename T>
T _remove_head(node<T>*& head_ptr)
{
    //1.point a pointer to node being removed
    node<T>* remove = head_ptr;
    //2.point head_ptr to next node
    if(head_ptr-> _next != NULL) //if there is next node
    {
        head_ptr = head_ptr->_next; //new head is next pos
        head_ptr->_prev = NULL;
    }
    else //new head is NULL
    {
        head_ptr = NULL;
    }
    //3.hold on to item in remove node
    T hold = remove->_item;
    //4.delete the remove node
    delete remove;
    //5.return item we held
    return hold;
}

template <typename T>
node<T>* _insert_after(node<T>*& head_ptr, node<T>* mark,
                       const T& item)
{
    //1.check if first is is_empty
    if(isempty(head_ptr) || mark == NULL)
    {
         //2.insert head if list is is_empty
        return _insert_head(head_ptr, item);
    }
    else
    {
        //3.insert head at position after mark
        return _insert_head(mark->_next, item);
    }
}

template <typename T>
node<T>* _insert_before(node<T>*& head_ptr, node<T>* mark,
                        const T& item)
{
    //1.check if list is is_empty
    if(isempty(head_ptr) || mark == NULL || mark == head_ptr)
    {
         //insert head if list is is_empty
        return _insert_head(head_ptr, item);
    }
    else
    {
        return _insert_head(mark->_prev, item);
    }
}

template <typename T>
node<T>* copy_list(const node<T>* head_ptr, node<T>*& cpy)
{
    cpy = NULL;
    const node<T>* wsrc = head_ptr;
    _insert_head(cpy,wsrc->_item);
    node<T>* wdes = cpy;
    while(wsrc != NULL)
    {
        _insert_after(cpy,wdes,wsrc->_item);
        wsrc = wsrc->_next;
        wdes = wdes->_next;
    }
    _remove_head(cpy);
    wdes->_next = NULL;
    return wdes;
}

template <typename T>
void clear_list(node<T>*& head_ptr)
{
    while(!isempty(head_ptr))
    {
        _remove_head(head_ptr);
    }
}


template<typename T>
ostream& _print_list(node<T>* head_ptr, ostream& outs)
{
    outs<<"H->";
    for (node<T>* w = head_ptr; w!=nullptr; w =w->_next)
    {
        //puts bracket over item
        outs<< "[" << *w << "]->";
    }
    outs<<"|||";
    outs << endl;
    return outs;
}

template <typename T>
bool isempty(const node<T>* head_ptr)
{

    return head_ptr == NULL;
}


template <typename T>
T _delete_node(node<T>*& head_ptr,  node<T>* mark)
{
    assert(mark != NULL);

    //1.get a walker
    node<T>* w = head_ptr;

    while(w!= mark)
    {
        w = w->_next; //2.get to pos mark
    }

    //3.get to pos before mark
    node<T>* prev = _previous_node(head_ptr, w);

    if(prev == NULL)//if there is no pos before mark
    {
        //remove head
        return _remove_head(head_ptr);
    }
    else
    {
        //prev is pointing at where w(mark) is pointing at
        prev->_next = w->_next;
        //remove at pos w
        return _remove_head(w);
    }
}


template <typename T>
node<T>* _previous_node(node<T>* head_ptr, node<T>* mark)
{
    node<T>* w = head_ptr;
    //1.check if mark is pointing at no where
    assert(mark != NULL);//includes empty list

    //2.if mark is poinitng at the head return NULL
    if(mark == head_ptr)
    {
        return NULL;
    }
    else
    {
        //3.go to position before mark and return it
        while(w->_next != mark)
        {
            w = w->_next; //get to pos beofre mark
        }
        return w;
    }
}


#endif // NODE_H
