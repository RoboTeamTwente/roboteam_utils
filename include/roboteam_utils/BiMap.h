#pragma once

#include <set>
#include <utility>
#include <functional>

namespace rtt {
    
template <typename T, typename U>
class BiMap {
    public:
    typedef std::pair<T, U*> LeftPair;
    typedef std::pair<U, T*> RightPair;

    bool insert(T& left, U& right);
    
    bool containsLeft(const T& key);
    bool containsRight(const U& key);
    
    bool removeByLeft(const T& key);
    bool removeByRight(const U& key);
    
    U* lookupLeft(const T& key) const;
    T* lookupRight(const U& key) const;
    
    unsigned int size() const;
    /*
    class Iterator {
        public:
        typedef std::pair<T, U> Pair;
        Iterator();
        Iterator(const Iterator& other);
        Iterator& operator=(const Iterator& other);
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
        Pair& operator*();
        Pair* operator->();
        Iterator& operator++();
        Iterator operator++(int);
        
        private:
        typename std::set<LeftPair>::iterator it;
    };
    */
    
    typedef struct LeftComp : std::binary_function<LeftPair, LeftPair, bool> {
        bool operator()(const LeftPair& a, const LeftPair& b) const;
    } LeftComp;
    
    typedef struct RightComp : std::binary_function<RightPair, RightPair, bool> {
        bool operator()(const RightPair& a, const RightPair& b) const;
    } RightComp;
       
    typename std::set<LeftPair, LeftComp>::const_iterator begin() const;
    typename std::set<LeftPair, LeftComp>::const_iterator end() const;
    
    private:
    std::set<LeftPair, LeftComp> leftSet;
    std::set<RightPair, RightComp> rightSet;    
    
}; 
    
}

#include "BiMap.tpp"