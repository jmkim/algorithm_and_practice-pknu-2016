#include "priority_queue.hpp"
#include "../../excercise04/sort/heap.hpp"
#include "../../excercise04/sort/swap.hpp"

int push_priority_queue(int *data, const int capacity, int count, const int input)
{
    if(count >= capacity) return capacity;

    data[count++] = input;
    for(int k = count; k > 0; k = (k - 1) / 2)
        if(data[count] > data[(k - 1) / 2]) swap(data[count], data[(k - 1) / 2]);

    return count;
}

int pop_priority_queue(int *data, int count)
{
    int k = 0;
    int output = data[k];
    swap(data[k], data[count--]);
    if(2 * k + 2 < count) /* Have two child nodes */
    {
        if(data[k] < data[2 * k + 1] && data[2 * k + 1] >= data[2 * k + 2])
        {
            swap(data[k], data[2 * k + 1]);
            k = 2 * k + 1;
        }
        else if(data[k] < data[2 * k + 2])
        {
            swap(data[k], data[2 * k + 2]);
            k = 2 * k + 2;
        }
    }
    else if(2 * k + 1 < count && data[k] < data[2 * k + 1]) /* Have one leaf node */
    {
        swap(data[k], data[2 * k + 1]);
        k = 2 * k + 1;
    }

    return output;
}

int peak_priority_queue(int *data)
{
    return data[0];
}
