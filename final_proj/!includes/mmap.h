#ifndef MULTIMAP_H
#define MULTIMAP_H
#include "mpair.h"
#include "!includes/bplustree.h"
#include <vector>

template <typename K, typename V>
class MMap
{
public:
    class Iterator
    {
        public:
            friend class MMap;

            Iterator(typename BPlusTree<MPair<K, V> >::Iterator it = typename BPlusTree<MPair<K, V> >::Iterator()): _it(it)
            {

            }
            Iterator operator ++(int unused)
            {
                return ++_it;
            }
            Iterator operator ++()
            {
                return _it++;
            }
            MPair<K, V> operator *()
            {
                return *_it;
            }
            friend bool operator ==(const Iterator& lhs, const Iterator& rhs)
            {
                return lhs._it == rhs._it;
            }
            friend bool operator !=(const Iterator& lhs, const Iterator& rhs)
            {
                return !(lhs._it == rhs._it);
            }

        private:
            typename BPlusTree<MPair<K, V> >::Iterator _it;
        };

    MMap();

    //  Iterators
    Iterator begin();
    Iterator end();
    Iterator lower_bound(const K& key);
    Iterator upper_bound(const K& key);

    //  Capacity
    int size() const;
    bool empty() const;

    //  Element Access
    const vector<V>& operator[](const K& key) const;
    vector<V>& operator[](const K& key);

    //  Modifiers
    void insert(const K& k, const V& v);
    void erase(const K& key);
    void clear();

    //  Operations:
    bool contains(const K& key);
    vector<V>& get(const K& key);

    Iterator find(const K& key);


    bool is_valid();

    friend ostream& operator<<(ostream& outs, const MMap<K, V>& print_me)
    {
        outs << print_me.mmap << endl;
        return outs;
    }

private:
    BPlusTree<MPair<K, V> > mmap;
};

//============================================================================


template<typename K, typename V>
MMap<K, V>::MMap() :mmap()
{

}

template<typename K, typename V>
void MMap<K, V>::clear()
{
    mmap.clear_tree();
}

template<typename K, typename V>
int MMap<K, V>::size() const
{
    return mmap.size();
}


template<typename K, typename V>
bool MMap<K, V>::contains(const K& key)
{
    return mmap.contains(MPair<K, V>(key));
}

template<typename K, typename V>
vector<V>& MMap<K, V>::get(const K& key)
{
    return mmap.get(MPair<K, V>(key)).value_list;
}



template<typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::find(const K& key)
{
    return Iterator(mmap.find(MPair<K, V>(key)));
}


template<typename K, typename V>
bool MMap<K, V>::is_valid()
{
    return mmap.is_valid();
}


template<typename K, typename V>
bool MMap<K, V>::empty() const
{
    return mmap.empty();
}

template<typename K, typename V>
const vector<V>& MMap<K, V>::operator[](const K& key) const
{
    return mmap.get(MPair<K, V> (key)).value_list;
}

template<typename K, typename V>
vector<V>& MMap<K, V>::operator[](const K& key)
{
    return mmap.get(MPair<K, V> (key)).value_list;
}

template<typename K, typename V>
void MMap<K, V>::insert(const K& k, const V& v)
{
    mmap.insert(MPair<K, V>(k, v));
}

template<typename K, typename V>
void MMap<K, V>::erase(const K& key)
{
    mmap.remove(key);
}


template<typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::lower_bound(const K& key)
{
//    cout << "LOWER" << endl;

    return Iterator(mmap.lower_bound(key));
}
template<typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::upper_bound(const K& key)
{
//    cout << "UPPER" << endl;
    return Iterator(mmap.upper_bound(key));
}

template<typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::begin()
{
    return Iterator(mmap.begin());
}

template<typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::end()
{
    return Iterator(mmap.end());
}


#endif // MULTIMAP_H
