#include <iostream>
#include "algorithms.h"
#include "CircularBuffer.h"
#include "Point.h"
#include <vector>
#include "ctime"

using namespace std;

bool one(int a)
{
    return a == 1;
}

bool two(int a)
{
    return a == 2;
}


void test_algo_int()
{
    vector<int> all1 = {1, 1, 1, 2};
    cout << "all_of:\n\t 1)  {1, 1, 1, 2} all_of(==1) == " << algo::all_of(all1.begin(), all1.end(), one) << endl;

    vector<int> all2 = {1, 1, 1, 1};
    cout << "all_of:\n\t 2)  {1, 1, 1, 1} all_of(==1) == " << algo::all_of(all2.begin(), all2.end(), one) << endl
         << endl;


    vector<int> any1 = {1, 1, 1, 2};
    cout << "any_of:\n\t 1)  {1, 1, 1, 2} any_of(==2) == " << algo::any_of(any1.begin(), any1.end(), two) << endl;

    vector<int> any2 = {1, 1, 1, 1};
    cout << "any_of:\n\t 2)  {1, 1, 1, 1} any_of(==2) == " << algo::any_of(any2.begin(), any2.end(), two) << endl
         << endl;


    vector<int> none1 = {1, 1, 1, 2};
    cout << "none_of:\n\t 1)  {1, 1, 1, 2} none_of(==2) == " << algo::none_of(none1.begin(), none1.end(), two) << endl;

    vector<int> none2 = {1, 1, 1, 1};
    cout << "none_of:\n\t 2)  {1, 1, 1, 1} none_of(==2) == " << algo::none_of(none2.begin(), none2.end(), two) << endl
         << endl;


    vector<int> one1 = {1, 2, 2, 2};
    cout << "one_of:\n\t 1)  {1, 2, 2, 2} one_of(==2) == " << algo::one_of(one1.begin(), one1.end(), one) << endl;

    vector<int> one2 = {1, 1, 1, 1};
    cout << "one_of:\n\t 2)  {1, 1, 1, 1} one_of(==2) == " << algo::one_of(one2.begin(), one2.end(), one) << endl
         << endl;

    vector<int> arr = {1, 2, 3, 4};
    cout << "is_sorted:\n\t 1)  {1, 2, 3, 4} is_sorted(<) == "
         << algo::is_sorted(arr.begin(), arr.end(), [](int a, int b) { return a < b; }) << endl << endl;

    cout << "is_partitioned:\n\t 1)  {1, 2, 3, 4} is_partitioned(< 2) == "
         << algo::is_partitioned(arr.begin(), arr.end(), [](int a) { return a < 2; }) << endl << endl;

    cout << "find_not:\n\t 1)  {1, 2, 3, 4} find_not(1) == " << *algo::find_not(arr.begin(), arr.end(), 1) << endl
         << endl;

    vector<int> arr1 = {1, 2, 2, 1};
    cout << "is_palindrome:\n\t 1)  {1, 2, 2, 1} is_palindrome(==1) == "
         << algo::is_palindrome(arr1.begin(), arr1.end(), one);
}

bool cmp(Point t)
{
    Point x(1, 2);
    return (t.get_y() == x.get_y()) and (t.get_x() == x.get_x());
}

bool cmp1(Point t)
{
    Point x(2, 2);
    return (t.get_y() == x.get_y()) and (t.get_x() == x.get_x());
}

void test_algo_CPoint()
{
    Point x1(1, 2), x2(2, 3), x3(3, 2), x4(2, 1);
    vector<Point> a = {x1, x2, x3, x4};

    cout << "all_of:\n\t 1)  {x1(1, 2), x2(2, 3), x3(3, 2), x4(2, 1)} all_of( == (1, 2)) == " << algo::all_of(a.begin(), a.end(), cmp) << endl << endl;
    cout << "any_of:\n\t 1)  {x1(1, 2), x2(2, 3), x3(3, 2), x4(2, 1)} any_of( == (1, 2)) == " << algo::any_of(a.begin(), a.end(), cmp) << endl << endl;
    cout << "none_of:\n\t 1)  {x1(1, 2), x2(2, 3), x3(3, 2), x4(2, 1)} none_of( == (1, 2)) == " << algo::none_of(a.begin(), a.end(), cmp1) << endl << endl;
    cout << "is_sorted:\n\t 1)  {1, 2, 3, 4} is_sorted(<) == " << algo::is_sorted(a.begin(), a.end(), [](Point a, Point b) { return a.get_y() < b.get_y(); }) << endl << endl;

}

void test_buffer()
{
    srand(time(nullptr));
    CircularBuffer<int> buffer(4);
    int n = 10;
    for (size_t i = 0; i < n; ++i)
    {
        cout << i + 1 <<") ";
        buffer.push_back(i + rand() % 23);
        buffer.printBufferIt();
        cout << endl;
    }
    cout << "first: " << *buffer.begin() << "   last: " << *(buffer.end() - 1);
    cout << endl;
    sort(buffer.begin(), buffer.end());
    cout << "sorted buffer: ";
    buffer.printBufferIt();

}

int main()
{
    //test_algo_int();
    //test_buffer();
    test_algo_CPoint();

}
