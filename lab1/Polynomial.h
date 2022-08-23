
#ifndef LAB1_POLYNOMIAL_H
#define LAB1_POLYNOMIAL_H

#include <iostream>
#include <vector>
#include <algorithm>

template<typename Type>
class Polynomial {

private:
    std::vector<Type> coefficients_;
    size_t size_;

public:

    explicit Polynomial(int size = 0) {
        coefficients_.resize(size);
        size_ = size;
    }

    explicit Polynomial(std::vector<Type> coefficients) {
        size_ = coefficients.size();
        coefficients_.resize(size_);
        for (size_t i = 0; i < size_; ++i) {
            coefficients_[i] = coefficients[i];
        }
    }


    Polynomial(Polynomial const &p) : Polynomial(p.coefficients_) {};

    ~Polynomial() = default;

    size_t get_size() {
        return size_;
    }

    void swap(Polynomial &p) {
        std::swap(p.size_, size_);
        std::swap(p.coefficients_, coefficients_);
    }

    Polynomial &operator=(Polynomial const &p) {
        if (this != &p) {
            Polynomial(p).swap(*this);
        }
        return *this;
    }

    bool operator==(Polynomial const &p) {
        if (this->size_ != p.size_) {
            return false;
        } else {
            for (size_t i = 0; i < p.size_; ++i) {
                if (this->coefficients_[i] != p.coefficients_[i]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(Polynomial const &p) {
        return !(*this == p);
    }

    Polynomial &operator+=(Polynomial const &p) {
        size_t min_size = p.size_;
        if (size_ < p.size_) {
            coefficients_.resize(p.size_);
            size_ = p.size_;
            min_size = size_;
        }

        for (size_t i = 0; i < min_size; ++i) {
            coefficients_[i] += p.coefficients_[i];
        }
        return *this;
    }

    Polynomial &operator-=(Polynomial const &p) {
        size_t min_size = p.size_;
        if (size_ < p.size_) {
            coefficients_.resize(p.size_);
            size_ = p.size_;
            min_size = size_;
        }
        for (size_t i = 0; i < min_size; ++i) {
            coefficients_[i] -= p.coefficients_[i];
        }
        return *this;
    }

    Polynomial &operator*=(Polynomial const &p) {
        std::vector<Type> temp = coefficients_;
        coefficients_.clear();
        coefficients_.resize(p.size_ + size_ - 1, 0);
        for (size_t i = 0; i < size_; ++i) {
            for (size_t j = 0; j < p.size_; ++j) {
                coefficients_[i + j] += temp[i] * p.coefficients_[j];
            }
        }
        size_ += p.size_ - 1;
        return *this;
    }

    Polynomial &operator/=(int k) {
        for (size_t i = 0; i < size_; ++i) {
            coefficients_[i] /= k;
        }
        return *this;
    }

    Polynomial operator-() {
        Polynomial res(*this);
        for (size_t i = 0; i < size_; ++i) {
            res.coefficients_[i] *= -1;
        }
        return res;
    }

    Type &operator[](int i) {
        return coefficients_[i];
    }
};

template<class T>
Polynomial<T> operator+(Polynomial<T> p1, Polynomial<T> const &p2) {
    return p1 += p2;
}

template<class T>
Polynomial<T> operator-(Polynomial<T> p1, Polynomial<T> const &p2) {
    return p1 -= p2;
}

template<class T>
Polynomial<T> operator*(Polynomial<T> p1, Polynomial<T> const &p2) {
    return p1 *= p2;
}

template<class T>
Polynomial<T> operator/(Polynomial<T> p1, int i) {
    return p1 /= i;
}

template<class T>
std::istream &operator>>(std::istream &is, Polynomial<T> &p) {
    for (int i = 0; i < p.get_size(); i++) {
        is >> p[i];
    }
    return is;
}


template<class T>
std::ostream &operator<<(std::ostream &os, Polynomial<T> p) {
    bool isNull = true;
    for (size_t i = p.get_size(); i > 0; --i) {
        if (p[i-1] != 0) {
            std::cout << (p[i - 1] > 0 ? "+ " : "")  << p[i - 1] << "x^" << i - 1 << ' ';
            isNull = false;
        }
    }
    if (isNull) {
        os << '0';
    }
    return os;
}


#endif //LAB1_POLYNOMIAL_H
