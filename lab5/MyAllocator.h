//
// Created by днс on 11.05.2022.
//

#ifndef LAB5_MYALLOCATOR_H
#define LAB5_MYALLOCATOR_H

#include <cassert>
#include "bits/stdc++.h"

template<class T>
class MyAllocator
{
public:

    using value_type = T;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using pointer = T *;
    using const_pointer = const T *;
    using reference = T &;
    using const_reference = const T &;

    MyAllocator(size_type n)
    {
        size = n * sizeof(T);
        chunks_ = static_cast<unsigned char *>(new unsigned char[size]);
        end = &chunks_[size - 1];
        bytes_allocated = 0;
    }

    template<class U>
    MyAllocator(const MyAllocator<U> &x)
    {
        chunks_ = x.chunks_;
        end = x.end;
        size = x.size;
        bytes_allocated = x.bytes_allocated;
    }

    template<class U>
    struct rebind
    {
        using other = MyAllocator<U>;
    };

    T *allocate(size_t n)
    {
        if (size < n * sizeof(T) + bytes_allocated)
        {
            throw std::bad_alloc();
        }
        auto mem = &chunks_[bytes_allocated + 1];
        bytes_allocated += (n * sizeof(T));
        return (T*)(mem);
    }

    void deallocate(T *p, size_t n)
    {
        if (bytes_allocated - n * sizeof(T) < 0)
        {
            throw std::runtime_error("huita");
        }else if( p < (void*)chunks_ or p > end){
            throw std::runtime_error("huita2");
        }
        else
        {
            bytes_allocated -= n * sizeof(T);
        }
    }

    unsigned char *chunks_;
    void *end;
    size_t size;
    size_t bytes_allocated;
};

template<class T, class U>
bool operator==(const MyAllocator<T> &x1, const MyAllocator<U> &x2)
{
    return x1 == x2;
}

template<class T, class U>
bool operator!=(const MyAllocator<T> &x1, const MyAllocator<U> &x2)
{
    return x1 != x2;
}


#endif //LAB5_MYALLOCATOR_H
