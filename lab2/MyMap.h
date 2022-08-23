//
// Created by psajd on 01.03.2022.
//

#ifndef UNTITLED_MYMAP_H
#define UNTITLED_MYMAP_H

#include <iostream>
#include "string"
#include <vector>

static const int mod = 541; // prime number

template <typename Type>
class MyMap {
private:
    std::vector<std::vector<std::pair<std::string, Type>>> map{};
public:
    MyMap();

    static int hash(const std::string& x);

    void put(const std::string& x, const Type& y);

    void del(const std::string& x);

    Type& get(const std::string& x);

    Type& operator[] (const std::string& x);
};

template<typename Type>
MyMap<Type>::MyMap() {
    map.resize(mod);
}

template<typename Type>
int MyMap<Type>::hash(const std::string &x) {
    int hash = 0;
    for (char i : x) {
        hash *= 47;
        hash += i - 'a' + 1;
        hash = ((hash % mod) + mod) % mod; // avoid negative hash
    }
    return hash;
}

template<typename Type>
void MyMap<Type>::put(const std::string &x, const Type &y) {
    int d = hash(x);
    for (auto& h : map[d]) {
        if (x == h.first) {
            h.second = y;
            return;
        }
    }
    map[d].push_back(make_pair(x, y));
}

template<typename Type>
void MyMap<Type>::del(const std::string &x) {
    int d = hash(x);
    for (int i = 0; i < map[d].size(); i++) {
        if (map[d][i].first == x) {
            swap(map[d][i], map[d][map[d].size() - 1]);
            map[d].pop_back();
            return;
        }
    }
}

template<typename Type>
Type& MyMap<Type>::get(const std::string &x) {
    int d = hash(x);
    for (auto & i : map[d]){
        if (i.first == x){
            return i.second;
        }
    }
    throw std::logic_error("No matching value");
}

template<typename Type>
Type &MyMap<Type>::operator[](const std::string &x) {
    return this->get(x);
}

#endif //UNTITLED_MYMAP_H
