#ifndef LAB1_POLYNOMIAL_H
#define LAB1_POLYNOMIAL_H

#include <iostream>
#include <algorithm>
#include "iostream"


template<int x, int...c>
class Polynomial
{

public:

    constexpr static int eval_answer()
    {
        int sex_arr = 0;
        for (int i = 0; i < sizeof...(c); i++){
            int ans = 1;
            for (int j = 0; j < i; ++j)
            {
                ans *= x;
            }
            sex_arr += coefficients_[i] * ans;
        }

        return sex_arr;
    }


    Polynomial() = default;


    size_t get_size()
    {
        return size_;
    }

    int operator[](int i) const
    {
        return coefficients_[i];
    }

    friend std::ostream& operator<<(std::ostream &os, const Polynomial<x,c...>& p){
        os << "x = " << x << std::endl;
        bool isNull = true;
        for (size_t i = p.size_; i > 0; --i) {
            if (p[i-1] != 0) {
                std::cout << (p[i - 1] > 0 ? "+ " : "")  << p[i - 1] << "x^" << i - 1 << ' ';
                isNull = false;
            }
        }
        if (isNull) {
            os << '0';
        }
        os << "= " << res_arr;
        return os;
    }

private:
    static constexpr int coefficients_[] = {c...};
    static constexpr size_t size_ = sizeof...(c);
    static constexpr int x_ = x;
    static constexpr int res_arr = eval_answer();
};



#endif //LAB1_POLYNOMIAL_H