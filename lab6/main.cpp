#include <iostream>
#include "Polynomial.h"
#include "gtest/gtest.h"

TEST(PolynomialTest, test1){
    Polynomial<0, 0, 1, 1, 1, 1> x;
    EXPECT_EQ(x.eval_answer(), 0);
}



TEST(PolynomialTest, test2){
    Polynomial<0, 10, -4, 3, 2, 1> x;
    EXPECT_EQ(x.eval_answer(), 10);
}


TEST(PolynomialTest, test3){
    Polynomial<2, 1, 2, 3> x;
    EXPECT_EQ(x.eval_answer(), 17);
}

TEST(PolynomialTest, test4){
    Polynomial<8, 1, -4, 10> x;
    EXPECT_EQ(x.eval_answer(), 609);
}


int main()
{
    /*testing::InitGoogleTest();
    return RUN_ALL_TESTS();*/
    Polynomial<1, 1, 2, 3, 4, 5> polynomial;
    static constexpr auto a = polynomial.eval_answer();
    std::cout << polynomial;

    return 0;
}
