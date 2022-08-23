#ifndef LAB3_ALGORITHMS_HPP
#define LAB3_ALGORITHMS_HPP
namespace algo
{
    template<class InputIt, class UnaryPredicate>
    bool all_of(InputIt begin, InputIt end, UnaryPredicate predicate)
    {
        for (; begin != end; begin++)
        {
            if (!predicate(*begin))
            {
                return false;
            }
        }
        return true;
    }

    template<class InputIt, class UnaryPredicate>
    bool any_of(InputIt begin, InputIt end, UnaryPredicate predicate)
    {
        for (; begin != end; begin++)
        {
            if (predicate(*begin))
            {
                return true;
            }
        }
        return false;
    }

    template<class InputIt, class UnaryPredicate>
    bool none_of(InputIt begin, InputIt end, UnaryPredicate predicate)
    {
        for (; begin != end; begin++)
        {
            if (predicate(*begin))
            {
                return false;
            }
        }
        return true;
    }

    template<class InputIt, class UnaryPredicate>
    bool one_of(InputIt begin, InputIt end, UnaryPredicate predicate)
    {
        bool flag = false;
        for (; begin != end; ++begin)
        {
            if (predicate(*begin) and !flag)
            {
                flag = true;
            } else if (predicate(*begin))
            {
                return false;
            }
        }
        return flag;
    }

    template<class InputIt, class Compare>
    bool is_sorted(InputIt begin, InputIt end, Compare compare)
    {
        if (begin == end) { return true; }
        InputIt next = begin;

        for (; ++next != end; ++begin)
        {
            if (compare(*next, *begin)) { return false; }
        }
        return true;
    }

    template<class InputIt, class UnaryPredicate>
    bool is_partitioned(InputIt begin, InputIt end, UnaryPredicate predicate)
    {
        while (begin != end && predicate(*begin)) { ++begin; }

        for (; begin != end; ++begin)
        {
            if (predicate(*begin)) { return false; }
        }
        return true;
    }

    template<class InputIt, class Object>
    InputIt find_not(InputIt begin, InputIt end, const Object &value)
    {
        for (; begin != end; ++begin)
        {
            if (*begin != value) { return begin; }
        }
        return end;
    }

    template<class InputIt, class Object>
    InputIt find_backward(InputIt begin, InputIt end, const Object &value)
    {
        for (; begin != end; --end)
        {
            if (*end == value) { return end; }
        }
        return begin;
    }

    template<class InputIt, class UnaryPredicate>
    bool is_palindrome(InputIt begin, InputIt end, UnaryPredicate predicate)
    {
        for (auto it1 = begin, it2 = prev(end); it1 != end; it1++, it2--)
        {
            if (predicate(*it1) ^ predicate(*it2))
            {
                return false;
            }
        }
        return true;
    }
}
#endif //LAB3_ALGORITHMS_HPP
