#ifndef STACK_H
#define STACK_H
#include"../../!includes/node/node.h"

template <class T>
class Stack
{
public:
    class Iterator
        {
        public:
            friend class Stack;
            Iterator(node<T>* p = NULL): _ptr(p)
            {
               //default ctor
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
                it.next();
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
            //pointer being encapsulated

        };
        Stack();

        ~Stack();
        Stack(const Stack<T>& other);
        Stack<T>& operator =(const Stack<T>& rhs);

        Iterator begin()const;
        //Returns Iterator to the head node
        Iterator end()const;
        //Returns Iterator points at NULL

        void push(T item);
        T pop();
        T top();
        bool empty();
        friend ostream& operator << (ostream& outs, const Stack& s)
        {
            outs<<"[F]";
            for(Iterator it=s.begin(); it!=s.end(); it++)
            {

                outs<< "<-[" << *it <<"]";
            }
            outs << "<-[END]";
            return outs;
//            return _print_list(s._top, outs);
        }
private:
    node<T>* _top;
};



template<typename T>
typename Stack<T>:: Iterator Stack<T>::begin()const
{
    return Iterator(_top);
}

template<typename T>
typename Stack<T>:: Iterator Stack<T>::end()const
{
    return Iterator(NULL);
}

template<typename T>
Stack<T>::Stack(const Stack<T>& copy_this)
{
    copy_list(copy_this._top,_top);
}

template<typename T>
Stack<T>& Stack<T>::operator =(const Stack& rhs)
{
    //1. check for self-reference
    if (this == &rhs)
    {
        return *this;
    }
    //2. dealloate existing space;
    clear_list(_top);

   //3. allocate space and copy everything over
   copy_list(rhs._top,_top);

    //4. return this object
    return *this;
}

template<typename T>
Stack<T>::~Stack()
{
    clear_list(_top);
    //dealloate existing space;
}


template<typename T>
Stack<T>::Stack():_top(NULL)
{
}

template<typename T>
void Stack<T>::push(T item)
{
    //insert at head since it's a stack
    _insert_head(_top,item);
}

template<typename T>
T Stack<T>::pop()
{
    //make sure it's not empty
    assert(!empty());
    return _remove_head(_top);
}

template<typename T>
T Stack<T>::top()
{
    assert(!empty());
    return _top->_item;
}

template<typename T>
bool Stack<T>::empty()
{
    return _top == NULL;
}



#endif // STACK_H
