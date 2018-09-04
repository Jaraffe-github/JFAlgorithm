#pragma once

#define FORCEINLINE __forceinline

namespace JFFoundation
{
    namespace JFAlgorithm
    {
        template <class Value>
        struct JFDefaultLessComparator
        {
            FORCEINLINE bool operator () (const Value& lhs, const Value& rhs) const
            {
                return lhs < rhs;
            }
        };

        template <>
        struct JFDefaultLessComparator<void>
        {
            template <class Value>
            FORCEINLINE bool operator () (const Value& lhs, const Value& rhs) const
            {
                return lhs < rhs;
            }
        };

        template <class Value>
        struct JFDefaultLessComparator<Value*>
        {
            FORCEINLINE bool operator () (const Value* lhs, const Value* rhs) const
            {
                return (*lhs) < (*rhs);
            }
        };

        template <class T>
        FORCEINLINE void Swap(T& lhs, T& rhs)
        {
            T temp(std::move(lhs));
            lhs = std::move(rhs);
            rhs = std::move(temp);
        }

        template <class Value, class Comparator>
        FORCEINLINE void Sort3(Value& min, Value& mid, Value& max, Comparator& comparator)
        {
            if (comparator(min, mid))
            {
                if (comparator(mid, max))
                    return;

                Swap(mid, max);

                if (comparator(mid, min))
                    Swap(min, mid);

                return;
            }
            if (comparator(max, mid))
            {
                Swap(min, max);
                return;
            }
            Swap(min, mid);
            if (comparator(max, mid))
            {
                Swap(mid, max);
            }
        }

        template <class Iterator, class Comparator>
        FORCEINLINE void InsertionSort(Iterator first, Iterator end, Comparator& comparator)
        {
            Iterator i = first+1;
            for (; i != end; ++i)
            {
                Iterator j = i;
                auto t = std::move(*j);

                for (Iterator k = i; k != first && comparator(t, *--k); --j)
                {
                    *j = std::move(*k);
                }
                *j = std::move(t);
            }
        }

        template <class Iterator, class Comparator>
        FORCEINLINE Iterator Partition(Iterator first, Iterator end, Comparator& comparator)
        {
            auto count = end - first;

            Iterator min = first;
            Iterator mid = first + (count >> 1);
            Iterator max = end - 1;
            Iterator pivot = end - 2;

            Sort3(*min, *mid, *max, comparator);

            Swap(*pivot, *mid);

            Iterator left = ++min;
            Iterator right = pivot - 1;
            while (true)
            {
                while (comparator(*left, *pivot))
                    ++left;

                while (comparator(*pivot, *right))
                    --right;

                if (left >= right)
                    break;

                Swap(*left, *right);

                ++left;
                --right;
            }
            Swap(*left, *pivot);

            return left;
        }

        template <class Iterator, class Comparator = JFDefaultLessComparator<void>>
        void Sort(Iterator first, Iterator end, Comparator comparator = Comparator())
        {
            _Sort(first, end, comparator);
        }

        template <class Iterator, class Comparator>
        void _Sort(Iterator first, Iterator end, Comparator comparator)
        {
            auto count = end - first;

            switch (count)
            {
            case 0:
            case 1:
                return;
            case 2:
                if (comparator(*(first + 1), *first))
                    Swap(*first, *(first + 1));
                return;
            case 3:
                Sort3(*first, *(first+1), *(first+2), comparator);
                return;
            }

            if (count < 16)
            {
                InsertionSort(first, end, comparator);
            }
            else
            {
                Iterator pivot = Partition(first, end, comparator);
                _Sort(first, pivot, comparator);
                _Sort(pivot + 1, end, comparator);
            }
        }
    }
}