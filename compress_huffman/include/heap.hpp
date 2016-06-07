#ifndef ALGORITHM_HEAP_H_
#define ALGORITHM_HEAP_H_ 1

#include <functional>
#include <utility>
#include <vector>

namespace algorithm
{

template<
    typename ElementType,
    typename ElementCompareFunc = std::less<ElementType>,
    typename HeapType           = std::vector<ElementType>
>
class Heap
{
protected:
//    HeapType heap_;

public:
    HeapType heap_;

    void
    Heapify(void)
    {
        for(int i = heap_.size() - 1; i > 0; --i)
        {
            for(int j = i; j > 0; j = (j - 1) / 2)
            {
                if(ElementCompareFunc()( heap_.at(i), heap_.at((j - 1) / 2) ))
                {
                    std::swap( heap_.at(i), heap_.at((j - 1) / 2) );
                }
            }
        }
    }

    void
    Push(const ElementType & element)
    {
        heap_.push_back(element);

        for(int i = heap_.size() - 1; i > 0; i = (i - 1) / 2)
        {
            if(ElementCompareFunc()( heap_.at(heap_.size() - 1), heap_.at((i - 1) / 2) ))
                std::swap(heap_.at(heap_.size() - 1), heap_.at((i - 1) / 2));
        }
    }

    void
    Pop(void)
    {
        int i = 0;
        std::swap(heap_.at(i), heap_.at(heap_.size() - 1));
        heap_.pop_back();

        if(2 * i + 2 < heap_.size()) /* Have two child nodes */
        {
            if(heap_.at(i) < heap_.at(2 * i + 1) && heap_.at(2 * i + 1) >= heap_.at(2 * i + 2))
            {
                std::swap(heap_.at(i), heap_.at(2 * i + 1));
                i = 2 * i + 1;
            }
            else if(heap_.at(i) < heap_.at(2 * i + 2))
            {
                std::swap(heap_.at(i), heap_.at(2 * i + 2));
                i = 2 * i + 2;
            }
        }
        else if(2 * i + 1 < heap_.size() && heap_.at(i) < heap_.at(2 * i + 1)) /* Have one leaf node */
        {
            std::swap(heap_.at(i), heap_.at(2 * i + 1));
            i = 2 * i + 1;
        }
    }

    ElementType
    Peek(void)
    const
    { return heap_.back(); }
};

}

#endif /** ! ALGORITHM_HEAP_H_ */
