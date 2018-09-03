#pragma once

namespace JFFoundation
{
    template <typename Value>
    struct JFDefaultLessComparator
    {
        __forceinline bool operator () (const Value& lhs, const Value& rhs) const
        {
            return lhs < rhs;
        }
    };

    template <typename Value>
    struct JFDefaultLessComparator<Value*>
    {
        __forceinline bool operator () (const Value* lhs, const Value* rhs) const
        {
            return (*lhs) < (*rhs);
        }
    };

    template <typename T>
	__forceinline void Swap(T& lhs, T& rhs)
    {
        T temp = lhs;
        lhs = rhs;
        rhs = temp;
    }

	template <typename Value, typename Comparator = JFDefaultLessComparator<Value>>
	void InsertionSort(Value* dataSet, size_t startIndex, size_t endIndex, Comparator& comparator)
	{
		Value temp;

		for (size_t i = startIndex+1; i <= endIndex; ++i)
		{
			temp = dataSet[i];
			size_t j = i;
			while (j > startIndex && comparator(temp, dataSet[j-1]))
			{
				dataSet[j] = dataSet[j-1];
				--j;
			}
			dataSet[j] = temp;
		}
	}

    template <typename Value, typename Comparator = JFDefaultLessComparator<Value>>
    size_t Partition(Value* dataSet, size_t startIndex, size_t endIndex, Comparator& comparator)
    {
		size_t pivot = endIndex-1;
        size_t count = endIndex - startIndex;
        size_t midIndex = startIndex + (count >> 1);

        if (comparator(dataSet[midIndex], dataSet[startIndex]))
        {
            Swap(dataSet[midIndex], dataSet[startIndex]);
        }
        if (comparator(dataSet[endIndex], dataSet[midIndex]))
        {
            Swap(dataSet[endIndex], dataSet[midIndex]);
        }
        if (comparator(dataSet[midIndex], dataSet[startIndex]))
        {
            Swap(dataSet[midIndex], dataSet[startIndex]);
        }

        Swap(dataSet[pivot], dataSet[midIndex]);
		
        size_t leftPos = startIndex+1;
        size_t rightPos = endIndex-2;
		while (true)
		{
			while (comparator(dataSet[leftPos], dataSet[pivot]))
				++leftPos;
        
			while (comparator(dataSet[pivot], dataSet[rightPos]))
				--rightPos;
        
            if (leftPos >= rightPos)
                break;
			
            Swap(dataSet[leftPos], dataSet[rightPos]);
        
            ++leftPos;
            --rightPos;
		}
		Swap(dataSet[leftPos], dataSet[pivot]);

		return leftPos;
    }

    template <typename Value, typename Comparator = JFDefaultLessComparator<Value>>
    void Sort(Value* dataSet, size_t startIndex, size_t endIndex, Comparator comparator = Comparator())
    {
        if (startIndex >= endIndex)
            return;

		size_t count = endIndex - startIndex;
		if (count < 32)
		{
		    InsertionSort(dataSet, startIndex, endIndex, comparator);
		}
		else
		{
			size_t pivot = Partition(dataSet, startIndex, endIndex, comparator);
            Sort(dataSet, startIndex, pivot - 1, comparator);
            Sort(dataSet, pivot + 1, endIndex, comparator);
		}
    }
}