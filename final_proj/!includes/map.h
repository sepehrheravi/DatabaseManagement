#ifndef MAP_H
#define MAP_H

#include "bplustree.h"
#include "pair.h"
#include <iostream>
using namespace std;

template <typename K, typename V>
class Map
{
public:
    class Iterator
    {
        public:
            friend class Map;
            Iterator(typename BPlusTree<Pair<K, V> >::Iterator it= typename BPlusTree<Pair<K, V> >::Iterator()):_it(it)
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
            Pair<K, V> operator *()
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
            typename BPlusTree<Pair<K, V> >::Iterator _it;
    };


    Map();
    //  Iterators
    Iterator begin();
    Iterator end();

    //  Capacity
    int size() const;
    bool empty() const;

    //  Element Access
    V& operator[](const K& key);
    V& at(const K& key);
    const V& at(const K& key) const;

    //I don't think we need lower and upper bound


    //  Modifiers
    void insert(const K& k, const V& v);
    void erase(const K& key);
    void clear();
    V get(const K& key);

    //  Operations:
    Iterator find(const K& key);
    bool contains(const Pair<K, V>& target);


    bool is_valid();

    friend ostream& operator<<(ostream& outs, const Map<K, V>& print_me)
    {
        outs << print_me.map << endl;
        return outs;
    }
private:
    int key_count;
    BPlusTree<Pair<K, V> > map;
};

//=====================================================
template<typename K, typename V>
bool Map<K, V>:: is_valid()
{
    return map.is_valid();
}



template <typename K, typename V>
Map<K, V>::Map():map()
{
    key_count = 0;
}


template <typename K, typename V>
int Map<K, V>:: size() const
{
    return map.size();

}

template <typename K, typename V>
bool Map<K, V>::empty() const
{
    return map.empty();

}

template<typename K, typename V>
V& Map<K, V>::operator[](const K& key)
{
    return map.get(Pair<K, V>(key)).value;
}

template<typename K, typename V>
V& Map<K, V>::at(const K& key)
{
    return map.get(Pair<K, V>(key)).value;
}

template<typename K, typename V>
const V& Map<K, V>::at(const K& key) const
{
   return map.get(Pair<K, V>(key)).value;
}

template<typename K, typename V>
void Map<K, V>::insert(const K& k, const V& v)
{
    //create pair object
    Pair<K, V> p(k, v);
    map.insert(p);

    //new size
    key_count = map.size();
}

template<typename K, typename V>
void Map<K, V>::erase(const K& key)
{
    map.remove(Pair<K, V>(key));
}

template<typename K, typename V>
void Map<K, V>::clear()
{
    map.clear_tree();

    //set size = 0
    key_count = 0;
}

template<typename K, typename V>
V Map<K, V>::get(const K& key)
{
    return map.get(Pair<K, V>(key)).value;
}

template<typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::find(const K& key)
{
    return Iterator(map.find(Pair<K, V>(key)));
}

template<typename K, typename V>
bool Map<K, V>::contains(const Pair<K, V>& target)
{
    return map.contains(target);
}

template<typename K, typename V>
typename Map<K, V>:: Iterator Map<K, V>::begin()
{
    return Iterator(map.begin());
}

template<typename K, typename V>
typename Map<K, V>:: Iterator Map<K, V>::end()
{
    return Iterator(map.end());
}





#endif // MAP_H
