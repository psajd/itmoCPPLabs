
#ifndef LAB3_CIRCULARBUFFER_H
#define LAB3_CIRCULARBUFFER_H

#include "iostream"

template<typename type>
class CircularBuffer
{

private:

    size_t size_;
    size_t capacity_;
    type *data_;

    type right_shift()
    {
        for (size_t i = size_ - 1; i != 0; --i)
        {
            data_[i] = data_[i - 1];
        }
        return data_[0];
    }

    type left_shift()
    {
        for (size_t i = 0; i < size_ - 1; ++i)
        {
            data_[i] = data_[i + 1];
        }
        return data_[size_ - 1];
    }

public:
    typedef std::iterator<std::random_access_iterator_tag, type> randIter;

    class Iterator : public randIter
    {
    private:
        type *ptr_;
    public:
        Iterator() : ptr_(nullptr) {}

        explicit Iterator(type *ptr) : ptr_(ptr) {}

        Iterator(const Iterator &iterator) : ptr_(iterator.ptr_) {}

        bool operator==(const Iterator &iterator) const
        {
            return ptr_ == iterator.ptr_;
        }

        bool operator!=(const Iterator &iterator) const
        {
            return ptr_ != iterator.ptr_;

        }

        type &operator*()
        {
            return *ptr_;
        }

        type operator*() const
        {
            return *ptr_;
        }

        type *operator->() const
        {
            return ptr_;
        }

        bool operator>(const Iterator &iterator) const
        {
            return ptr_ > iterator.ptr_;
        }

        bool operator>=(const Iterator &iterator) const
        {
            return ptr_ >= iterator.ptr_;
        }

        bool operator<(const Iterator &iterator) const
        {
            return ptr_ < iterator.ptr_;
        }

        bool operator<=(const Iterator &iterator) const
        {
            return ptr_ <= iterator.ptr_;
        }

        const int operator-(const Iterator &iterator) const
        {
            return ptr_ - iterator.ptr_;
        }

        Iterator operator+(const typename randIter::difference_type difference) const
        {
            return Iterator(ptr_ + difference);
        }

        Iterator operator-(const typename randIter::difference_type difference) const
        {
            return Iterator(ptr_ - difference);
        }

        Iterator &operator++()
        {
            ++ptr_;
            return *this;
        }

        Iterator operator++(type)
        {
            Iterator temp(*this);
            ++ptr_;
            return temp;
        }

        Iterator &operator--()
        {
            --ptr_;
            return *this;
        }

        Iterator operator--(type)
        {
            Iterator temp(*this);
            --ptr_;
            return temp;
        }

        Iterator operator+=(const typename randIter::difference_type difference)
        {
            ptr_ += difference;
            return *this;
        }

        Iterator operator-=(const typename randIter::difference_type difference)
        {
            ptr_ -= difference;
            return *this;
        }

        type &operator[](typename randIter::difference_type difference)
        {
            return ptr_[difference];
        }

    };


    CircularBuffer() : size_(0), capacity_(0), data_(nullptr) {}

    CircularBuffer(size_t capacity) : size_(0), capacity_(capacity), data_(new type[capacity]) {}

    CircularBuffer(const CircularBuffer &buffer) : size_(buffer.size_), capacity_(buffer.capacity_),
                                                   data_(new type[capacity_])
    {
        for (size_t i = 0; i < size_; ++i)
        {
            data_[i] = buffer.data_[i];
        }
    }

    ~CircularBuffer()
    {
        delete[] data_;
    }

    void swap(CircularBuffer &buffer)
    {
        std::swap(size_, buffer.size_);
        std::swap(capacity_, buffer.capacity_);
        std::swap(data_, buffer.data_);
    }

    CircularBuffer &operator=(const CircularBuffer &buffer)
    {
        if (&buffer != this)
        {
            CircularBuffer(buffer).swap(*this);
        }
        return *this;
    }

    void printBufferIt()
    {
        for (auto it = this->begin(); it != this->end(); it++)
        {
            std::cout << *it << ' ';
        }
    }

    type &operator[](size_t index) const
    {
        if (index < size_)
        {
            return data_[index];
        } else
        {
            throw std::length_error("Buffer index out of bounds");
        }
    }

    void resize(size_t nSize)
    {
        capacity_ = nSize;
        type *temp = new type[nSize];
        for (size_t i = 0; i < size_; ++i)
        {
            temp[i] = data_[i];
        }
        delete[] data_;
        data_ = temp;
    }

    void push_back(type t)
    {
        if (size_ == capacity_)
        {
            right_shift();
        } else
        {
            ++size_;
        }
        data_[size_ - 1] = t;
    }

    void push_front(type t)
    {
        if (size_ == capacity_)
        {
            left_shift();
        } else
        {
            ++size_;
        }
        data_[1] = t;
    }

    type pop_back()
    {
        --size_;
        type temp = data_[size_];
        return temp;
    }

    type pop_front()
    {
        left_shift();
        --size_;
    }

    CircularBuffer::Iterator begin()
    {
        return Iterator(data_);
    }

    CircularBuffer::Iterator end()
    {
        return Iterator(data_ + size_);
    }

    size_t size()
    {
        return size_;
    }

};


#endif //LAB3_CIRCULARBUFFER_H
