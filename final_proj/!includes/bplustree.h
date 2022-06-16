#ifndef BPLUSTREE_H
#define BPLUSTREE_H
#include <iostream>
#include <iomanip>
#include <cassert>
#include <stack>
#include "array_func.h"


using namespace std;


template <class T>
class BPlusTree
{
public:
    class Iterator
    {
        public:
            friend class BPlusTree;
            Iterator(BPlusTree<T>* _it=NULL, int _key_ptr = 0):it(_it),
                key_ptr(_key_ptr)
            {

            }

            T operator *()
            {
                assert(key_ptr<it->data_count);
                return it->data[key_ptr];
            }

            Iterator operator++(int un_used)
            {
                assert(key_ptr<it->data_count);

                if(key_ptr == it->data_count-1)
                {
                    it=it->next;
                    key_ptr = 0;
                }
                else
                {
                    key_ptr++;
                }
                return(*this);
            }

            Iterator operator++()
            {
                assert(key_ptr<it->data_count);
                Iterator hold(it, key_ptr);
                if(key_ptr == it->data_count-1)
                {
                    it=it->next;
                    key_ptr = 0;
                }
                else
                {
                    key_ptr++;
                }
                return hold;


            }
            friend bool operator ==(const Iterator& lhs, const Iterator& rhs)
            {
                return (lhs.it == rhs.it) && (lhs.key_ptr == rhs.key_ptr);
            }

            friend bool operator !=(const Iterator& lhs, const Iterator& rhs)
            {
                return !(lhs == rhs);
            }
            void print_Iterator()
            {
                cout << it->data[key_ptr];
            }
            bool is_null()
            {
                return !it;
            }
    private:
        BPlusTree<T>* it;
        int key_ptr;
    };

    //CTOR
    BPlusTree();
    //big three:
    BPlusTree(const BPlusTree<T>& other);
    ~BPlusTree();
    BPlusTree<T>& operator =(const BPlusTree<T>& rhs);

    void insert(const T& entry);
    //insert entry into the tree
    void remove(const T& entry);
    //remove entry from the tree

    void clear_tree();
    //clear this object
    void copy_tree(const BPlusTree<T>& other);
    void copy_tree(const BPlusTree<T>& other, BPlusTree<T>*& last = nullptr);
    //copy other into this object
    bool contains(const T& entry);
    //true if entry can be found in the array

    T& get(const T& entry);
    //return a reference to entry in the tree
    const T& get(const T& entry)const;
    //return a reference to entry in the tree
    T& get_existing(const T& entry);
    //return a reference to entry in the tree

    Iterator find(const T& entry);
    //return an iterator to this key. NULL if not there.


    Iterator lower_bound(const T& key);
    //return first that goes NOT BEFORE
    // key entry or next if does not
   // exist >= entry
    Iterator upper_bound(const T& key);
    //return first that goes AFTER key

    int size() const;
    //count the number of elements in the tree
    bool empty() const;
    //true if the tree is empty

    void print_tree(int level = 0,ostream& outs = cout) const;
    //print a readable version of the tree
    friend ostream& operator<<(ostream& outs, const BPlusTree<T>& print_me)

    {
        print_me.print_tree(0, outs);
        return outs;
    }
    bool is_valid();

    Iterator begin();
    Iterator end();

private:
    static const int MINIMUM = 1;
    static const int MAXIMUM = 2 * MINIMUM;

    int data_count;
    //number of data elements
    T data[MAXIMUM + 1];
    //holds the keys
    int child_count;
    //number of children
    BPlusTree* subset[MAXIMUM + 2];
    //subtrees
    BPlusTree* next;
    int _size;

    bool is_leaf() const
    {
        return child_count == 0;
    }

    T* find_ptr(const T& entry);
    //return a pointer to this key. NULL if not there.

    //insert element functions
    void loose_insert(const T& entry);
    //allows MAXIMUM+1 data elements in the root
    void fix_excess(int i);
    //fix excess of data elements in child i

    //remove element functions:
    void loose_remove(const T& entry);
    //allows MINIMUM-1 data elements in the root

    void get_biggest(T& entry);
    //entry := rightmost leaf
    BPlusTree<T>* fix_shortage(int i);
    //fix shortage of data elements in child i
    BPlusTree<T>* get_smallest_node();
    // and return the smallest key in this subtree
    void get_smallest(T& entry);
    //entry := leftmost leaf
    void transfer_left(int i);
    //transfer one element LEFT from child i
    void transfer_right(int i);
    //transfer one element RIGHT from child i
    BPlusTree<T>* merge_array_with_next_subset(int i);
    //merge subset i with subset i+1
    

};

template<class T>
BPlusTree<T>::BPlusTree()
{
    _size = 0;
    data_count = 0;
    child_count = 0;
    next = NULL;

    //set all vars to NULL
    for(int i=0; i<MAXIMUM+1; i++)
    {
        data[i] = T();

    }

    //set all subsets to NULL
    for(int i=0; i<MAXIMUM+2; i++)
    {
        subset[i] = NULL;
    }
}

template<class T>
BPlusTree<T>::BPlusTree(const BPlusTree<T>& other)
{
    BPlusTree* bpt = nullptr;
    copy_tree(other, bpt);
}

template<class T>
BPlusTree<T>::~BPlusTree()
{
    clear_tree();
//    cout << "DTOR GETS CALLED" << endl;

}

template<class T>
BPlusTree<T>& BPlusTree<T>::operator=(const BPlusTree<T>& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    //2.clear
    clear_tree();

    //3.copy
    BPlusTree* temp = nullptr;
    copy_tree(rhs, temp);
//    cout << "ASSIGNMENT OPERATOR GETS CALLED" << endl;

    return *this;
}

template<class T>
void BPlusTree<T>::insert(const T& entry)
{
    // keep track of number of data
    if(!contains(entry))
    {
         _size++;
    }

    //call loose insert on entry
    loose_insert(entry);

    //grow tree if needed
    if(data_count > MAXIMUM)
    {
        BPlusTree* grow = new BPlusTree();

        //copy elements to grow
        copy_array(grow->data, data, grow->data_count, data_count);
        copy_array(grow->subset, subset, grow->child_count, child_count);


        //now gorw has 0 elemtns and 1 child
        data_count = 0;
        child_count = 1;

        //point this to grow
        subset[0] = grow;

        //call fix excess on only subset
        fix_excess(0);
    }
}


template<class T>
void BPlusTree<T>::clear_tree()
{
    //clearing all subtrees
    for(int i=0; i<child_count; i++)
    {
        subset[i]->clear_tree();
    }
    //for each sub tree get rid of eveything
    for(int i=0; i<child_count; i++)
    {
        subset[i]->child_count = 0;
        subset[i]->data_count = 0;
        subset[i]->_size = 0;
        subset[i]->next = nullptr;
        delete subset[i];
        subset[i] = NULL;
    }
    _size = 0;
    data_count = 0;

    child_count = 0;

    next = NULL;

}



template<class T>
void BPlusTree<T>::copy_tree(const BPlusTree<T>& other)
{
    //had to write a this version
    //I was getting error when I was initializing last_leaf = NULL by default
    BPlusTree* last = nullptr;
    copy_tree(other, last);
}
template<class T>
void BPlusTree<T>::copy_tree(const BPlusTree<T>& other, BPlusTree<T>*& last)
{
    //for all subsets create a new tree and copy eberything over
    for (int i = other.child_count - 1; i >= 0; i--)
    {
        subset[i] = new BPlusTree();
        subset[i]->copy_tree(*other.subset[i], last);
    }

    //if leaf
    if (other.is_leaf())
    {
        //point next to lsat last to this
        next = last;
        last = this;
    }

    //copy over all sizes
    data_count = other.data_count;
    child_count = other.child_count;
    _size = other._size;

    //once back up, copy everything else in data
    for (int i = 0; i <= data_count; i++)
    {
        data[i] = other.data[i];
    }
}

template<class T>
bool BPlusTree<T>::contains(const T& entry)
{
    return find_ptr(entry) != nullptr;
}
template<class T>
T* BPlusTree<T>::find_ptr(const T& entry)
{
    int i = first_ge(data, data_count, entry);

    bool found = i < data_count && data[i] == entry;

    if (found)
    {
        //found nad leaf
        if (is_leaf())
            return &data[i];

        //found and not leaf
        else
            return subset[i+1]->find_ptr(entry);
    }

    //not found and leaf
    else if (is_leaf())
    {
        return nullptr;
    }

    //not found and not leaf
    else
    {
        return subset[i]->find_ptr(entry);
    }

}


template<class T>
void BPlusTree<T>::loose_insert(const T& entry)
{
    //get first greater or equal index
    int i = first_ge(data, data_count, entry);
     // find the item
    bool found = (i < data_count && data[i]==entry);
    //if found and leaf overwrite
    if(is_leaf() && found)
    {
        data[i] = entry;
        return;
    }

    //if not leaf and found recursively call loose insert on subset[i+1]
    else if(!is_leaf() && found)
    {
        return subset[i+1]->loose_insert(entry);
        if(subset[i]->data_count > MAXIMUM)
        {
            //fix excess
            fix_excess(i);
        }

    }

    //if leaf and not found insert item
    else if(is_leaf() && !found)
    {
        insert_item(data, i, data_count, entry);

    }

    //if not leaf and not found recursively call loose insert on subset[i+]
    else if(!is_leaf() && !found)
    {
        subset[i]->loose_insert(entry);
        if(subset[i]->data_count > MAXIMUM)
        {
            //fix excess
            fix_excess(i);
        }

    }
}

template<class T>
void BPlusTree<T>::fix_excess(int i)
{
    if(!(i<child_count))
    {
        cout << "Index in fix excess is greater than child_count" << endl;
        return;
    }

    T remove;

    //create new subset
    BPlusTree<T>* n = new BPlusTree<T>();

    //split data from subset i into new subset
    split(subset[i]->data, subset[i]->data_count, n->data, n->data_count);

    //split children from subset i into new subset
    split(subset[i]->subset, subset[i]->child_count, n->subset, n->child_count);

    //detach item
    detach_item(subset[i]->data, subset[i]->data_count, remove);

    //insert it at place i
    insert_item(data, i, data_count, remove);

    //insert subset at i+1 child
    insert_item(subset, i+1, child_count, n);

    //if not leaf
    if(subset[i]->is_leaf())
    {
        //transfer middle entry to the i+1 child first data
        insert_item(subset[i+1]->data, 0, subset[i+1]->data_count, data[i]);

        subset[i+1]->next = subset[i]->next;
        subset[i]->next = subset[i+1];
    }
}



template<class T>
BPlusTree<T>* BPlusTree<T>::get_smallest_node()
{
    if (child_count != 0)
        return subset[0]->get_smallest_node();

    return this;
}


template <typename T>
void BPlusTree<T>::get_smallest(T& entry)
{
    if(empty())
    {
        return;
    }
    //if gets to leaf index 0 is the smallest item
    if(is_leaf())
    {
        entry = data[0];
    }

    else
    {
        //recursively call get_smallest
        subset[0]->get_smallest(entry);

    }

}


template<class T>
T& BPlusTree<T>::get(const T& entry)
{
    //insert if not found
    if (!contains(entry))
        insert(entry);
    //return pointer value
    return *find_ptr(entry);
}

template<class T>
const T& BPlusTree<T>::get(const T& entry) const
{
    return get(entry);
}

template<class T>
T& BPlusTree<T>::get_existing(const T& entry)
{
    return *find_ptr(entry);
}

template<class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::find(const T& entry)
{
    //if tree is empty
    if(empty())
    {
        return NULL;
    }
    int i = first_ge(data, data_count, entry);

    bool found = i < data_count && data[i] == entry;

    if (found)
    {
        //leaf and found
        if (is_leaf())
            return BPlusTree<T>::Iterator(this, i);
        //not leaf and found
        else
            return subset[i+1]->find(entry);

    }
    //leaf and not found
    else if (is_leaf())
        return BPlusTree<T>::Iterator();

    //not found and not leaf
    else
        return subset[i]->find(entry);
}


template<class T>
int BPlusTree<T>::size() const
{
    //size
    return _size;
}

template<class T>
bool BPlusTree<T>::empty() const
{
    return _size == 0;
}

template<class T>
void BPlusTree<T>::print_tree(int level, ostream& outs) const
{
    if(!is_leaf())
        subset[data_count]->print_tree(level+1);
    for(int i= data_count-1; i>=0; i--)
    {
        outs << setw(4 * level) << "" << "[" << data[i] << "]"
//        outs << "I: " << i << " D: " << data_count << " C: " << child_count
             << endl;

        if(!is_leaf())
            subset[i]->print_tree(level+1);
    }
}

template<class T>
bool BPlusTree<T>::is_valid()
{
    if(!is_leaf())
    {
        if(child_count != data_count+1)
        {
            cout << "CHILD_COUNT != DATA_COUNT+!" << endl;
            return false;
        }
    }
    if(data_count > MAXIMUM)
    {
        cout << "DATA COUND >= MAXIMUM" <<endl;
        return false;
    }
    if(child_count > MAXIMUM+1)
    {
        cout << "CHILD COUND >= MAXIMUM+1" <<endl;
        return false;
    }
    for(int i=0; i<data_count-1; i++)
    {
        if(data[i+1] < data[i])
        {
            cout << "DATA NOT ASCENDING" << endl;
            return false;
        }
    }

    for(int i=0; i<data_count; i++)
    {
        if(!contains(data[i]))
        {
            cout << "DATA NOT in leaf" << endl;
            return false;
        }
    }

    if(!is_leaf())
    {

        for(int i=0; i<data_count; i++)
        {
            for(int j=0; j<subset[i]->data_count; j++)
            {
                if(data[i] < subset[i]->data[j])
                {
                    cout << "DATA LESS THAN LEFT CHILD DATA" << endl;
                    return false;
                }

            }
        }
    }
    if(!is_leaf())
    {

        for(int i=0; i<data_count; i++)
        {
            for(int j=0; j<subset[i+1]->data_count; j++)
            {
                if(data[i] > subset[i+1]->data[j])
                {
                    cout << "DATA GREATER THAN RIGHT CHILD DATA" << endl;
                    cout << data[i] << endl;
                    cout <<  subset[i+1]->data[j] << endl;
                    return false;
                }

            }
        }
    }


    bool valid;
    for(int i=0; i<child_count; i++)
    {
        valid = subset[i]->is_valid(false);
        if(!valid)
            return false;
    }
    return true;
}

template<class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::begin()
{
    if (!empty())
        //getting the smallest node
        return BPlusTree<T>::Iterator(get_smallest_node());
    //if empty just return iterator to null
    return Iterator(NULL);
}

template<class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::end()
{
    return Iterator(NULL);
}

template <typename T>
void BPlusTree<T>::remove(const T& entry)
{
    loose_remove(entry);
    _size--;
    if(data_count == 0 && child_count == 1)
    {
        cout << "SHRINK" << endl;
        BPlusTree<T>* shrink = subset[0];

        data_count = 0;
        child_count = 0;

        merge_array(data, data_count, shrink->data, shrink->data_count);
        merge_array(subset, child_count, shrink->subset, shrink->child_count);

        shrink->data_count = 0;
        shrink->child_count = 0;

        delete shrink;

    }

}



template <typename T>
BPlusTree<T>* BPlusTree<T>:: fix_shortage(int i)
{
    cout << "FIX SHORTAGE" << endl;
    if( i<child_count-1 && subset[i+1]->data_count > MINIMUM)
    {
        cout << "Transfer Left" << endl;
        transfer_left(i+1);
    }
    else if(i>0 && subset[i-1]->data_count > MINIMUM)
    {
        cout << "Transfer Right" << endl;
        transfer_right(i-1);
    }
    else if(i>0)
    {
        cout << "merge_array Left" << endl;
        merge_array_with_next_subset(i-1);
    }
    else
    {
        cout << "merge_array Right" << endl;
        merge_array_with_next_subset(i);
    }

    return subset[i];

}
template <typename T>
void BPlusTree<T>::transfer_left(int i)
{
    if(!subset[i]->is_leaf())
    {
            //holding to data[i-1]
            T hold = data[i-1];
            //FIRST item of subset[i]->data moves up to data to replace data[i-1]
            T first;
            BPlusTree<T>* first_child;
            delete_item(subset[i]->data, 0, subset[i]->data_count, first);

            if(subset[i]->child_count > 0)
                delete_item(subset[i]->subset, 0, subset[i]->child_count, first_child);

            data[i-1] = first;

            //data[i-1] moves down to the RIGHT of subset[i-1]->data and
            //subset[i] first child gets move over
            attach_item(subset[i-1]->data, subset[i-1]->data_count, hold);

            if(subset[i]->child_count > 0)
                attach_item(subset[i-1]->subset, subset[i-1]->child_count, first_child);

    }

    else
    {
        T removed;
        //transfer subset[i]->data[0] to end of subset[i-1]
        delete_item(subset[i]->data, 0, subset[i]->data_count, removed);
        attach_item(subset[i-1]->data, subset[i-1]->data_count, removed);

        //update parent of the transfered subset: data[i-1] = subset[i]->data[0]
        data[i-1] = subset[i]->data[0];
    }

}

template<class T>
void BPlusTree<T>::loose_remove(const T& entry)
{
    int i = first_ge(data, data_count, entry);
    bool found = (i < data_count) && (data[i] == entry);
    T remove;
    if (found)
    {
        if (is_leaf())
        {
            delete_item(data, i, data_count, remove);
        }
        //if not leaf and found
        else
        {
            subset[i + 1]->loose_remove(entry);

            if (subset[i + 1]->data_count < MINIMUM)
            {
                fix_shortage(i+1);
            }

        }
    }
    //if leaf and not found
    else if (is_leaf())
    {

        return;
    }

    //not leaf not found
    else
    {
        subset[i]->loose_remove(entry);

        if (subset[i]->data_count < MINIMUM)
        {
            fix_shortage(i);
        }
    }
}


template <typename T>
void BPlusTree<T>::transfer_right(int i)
{
    if(!subset[i]->is_leaf())
    {
//           LAST item of subset[i]->data moves up to data to replace data[i],
            T hold = data[i];
            T removed;
            detach_item(subset[i]->data, subset[i]->data_count, removed);
            data[i] = removed;

            //data[i] moves down to the LEFT of subset[i+1]->data
            insert_item(subset[i+1]->data, 0, subset[i+1]->data_count, hold);

            //move child if necessary
            BPlusTree<T>* child;
            if(subset[i]->child_count > 0)
            {
                detach_item(subset[i]->subset, subset[i]->child_count, child);
                insert_item(subset[i+1]->subset, 0, subset[i+1]->child_count, child);
            }
    }

    else
    {
        T detach;

        //transfer subset[i(1)]->data[last item] to left of subset[i+1]->data
        detach_item(subset[i]->data, subset[i]->data_count, detach);
        insert_item(subset[i+1]->data, 0, subset[i+1]->data_count, detach);

        //update parent of the transfered subset: data[i] = subset[i+1]->data[0]
        data[i] = subset[i+1]->data[0];
    }

}

template <typename T>
BPlusTree<T>* BPlusTree<T>:: merge_array_with_next_subset(int i)
{
    T remove;
    //remove data[i] from this object
    delete_item(data, i, data_count, remove);

    //if not a leaf, append it to child[i]->data:
    if(!subset[i]->is_leaf())
    {
        attach_item(subset[i]->data, subset[i]->data_count, remove);
    }

    //Move all data items from subset[i+1]->data to right of subset[i]->data
    if(subset[i+1]->data_count > 0)
        merge_array(subset[i]->data, subset[i]->data_count,
                    subset[i+1]->data, subset[i+1]->data_count);

    //Move all subset pointers from subset[i+1]->subset to right of
    //subset[i]->subset
    if(subset[i+1]->child_count > 0)
        merge_array(subset[i]->subset, subset[i]->child_count,
                    subset[i+1]->subset, subset[i+1]->child_count);

    //delete subset[i+1] (store in a temp)
    BPlusTree* temp = nullptr;
    subset[i+1]->data_count = 0;
    subset[i+1]->child_count = 0;
    delete_item(subset, i+1, child_count, temp);
    //if a leaf, point subset[i]->next to temp->next
    if(subset[i]->is_leaf())
    {
        subset[i]->next = temp->next;

    }
    //delete temp
    delete temp;

    return subset[i];
}

template<class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::lower_bound(const T& key)
{
    BPlusTree<T>::Iterator it = begin();

    while (it != end() && *it < key)
    {
        it++;
    }

    return it;
}

template<class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::upper_bound(const T& key)
{
    BPlusTree<T>::Iterator it = begin();

    while (it != end() && *it <= key)
    {
        it++;
    }

    return it;
}


template <typename T>
void BPlusTree<T>::get_biggest(T& entry)
{
    if(empty())
    {
        return;
    }
    //if gets to leaf index 0 is the smallest item
    if(is_leaf())
    {
        entry = data[data_count-1];
    }

    else
    {
        //recursively call get_smallest
        subset[data_count]->get_biggest(entry);

    }

}





#endif // BPLUSTREE_H

