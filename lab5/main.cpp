#include "MyAllocator.h"

using namespace std;

int main()
{
    MyAllocator<char> allocator(10000010);

    std::basic_string<char, std::char_traits<char>, MyAllocator<char>> str(allocator);
    std::basic_string<char, std::char_traits<char>, MyAllocator<char>> string("123", allocator);

    std::vector<int, MyAllocator<int>> vector({1, 2, 3}, allocator);
    std::set<int, std::less<>, MyAllocator<int>> set({1, 2, 3}, std::less<>{}, allocator);
    std::map<int, std::string, std::less<>, MyAllocator<std::pair<const int, std::string>>> map(allocator);
    std::unordered_set<int, std::hash<int>, std::equal_to<>, MyAllocator<int>> unorderedSet(allocator);
    std::forward_list<int, MyAllocator<int>> forwardList(allocator);

    std::cout << "set: \n";
    clock_t start = clock();
    std::set<int, std::less<>, MyAllocator<int>> s(allocator);
    for (int i = 0; i < 100000; i++)
    {
        s.insert(123);
    }
    clock_t end = clock();
    printf("My alloc: %f seconds\n\n", (double) (end - start) / CLOCKS_PER_SEC);

    std::set<int, std::less<>> s1;
    for (int i = 0; i < 100000; i++)
    {
        s1.insert(123);
    }
    end = clock();
    printf("Std: %f seconds\n\n", (double) (end - start) / CLOCKS_PER_SEC);


    std::cout << "\nvector:\n";
    start = clock();
    std::vector<int, MyAllocator<int>> vector1(100000, allocator);
    end = clock();
    printf("My Alloc: %f seconds\n\n", (double) (end - start) / CLOCKS_PER_SEC);

    std::vector<int> vector2(100000);
    end = clock();
    printf("Std: %f seconds\n\n", (double) (end - start) / CLOCKS_PER_SEC);

    std::cout << "\nlist:\n";
    start = clock();
    std::forward_list<int, MyAllocator<int>> list(100000, allocator);
    end = clock();
    printf("My Alloc: %f seconds\n\n", (double) (end - start) / CLOCKS_PER_SEC);

    std::forward_list<int> list1(100000);
    end = clock();
    printf("Std: %f seconds\n\n", (double) (end - start) / CLOCKS_PER_SEC);
}