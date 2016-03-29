#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../excercise04/make_random_data/make_random_data.hpp"
#include "../excercise04/sort/heap.hpp"
#include "../excercise04/sort/swap.hpp"
#include "priority_queue/priority_queue.hpp"

#define MIN_SIZE    100
#define MAX_SIZE    100000
#define SIZE_STEP   10

#define M   100

int main(void)
{
    srand(time(NULL));
    int *original = make_random_data(MAX_SIZE);

    for(int size_of_data = MIN_SIZE; size_of_data <= MAX_SIZE; size_of_data *= SIZE_STEP)
    {
        printf("SIZE OF DATA: %d\n", size_of_data);

        {
            const int capacity = size_of_data * 3;

            int data[capacity];
            memcpy(data, original, sizeof(int) * size_of_data);

            convert_to_binary_max_heap(data, size_of_data);

            clock_t before = clock();

            int count = size_of_data;
            for(int i = 0; i < M; ++i)
            {
                if(rand() % 2 == 0)
                    push_priority_queue(data, capacity, count, original[count]);
                else
                    pop_priority_queue(data, count);
            }

            clock_t after = clock();

            printf("Using heap:\t\t%lf\n", (double)(after - before)/CLOCKS_PER_SEC);
        }
        {
            int data[size_of_data];
            memcpy(data, original, sizeof(int) * size_of_data);

            clock_t before = clock();

            int count = size_of_data;
            for(int i = 0; i < M; ++i)
            {
                int max = data[0];
                if(rand() % 2 == 0) /* Push */
                {
                    data[count] = original[count++];
                }
                else /* Pop */
                {
                    for(int i = 0; i < count; ++i)
                        if(data[i] > max)
                        {
                            max = data[i];
                            swap(data[i], data[count--]);
                        }
                }
            }

            clock_t after = clock();

            printf("Not using heap:\t\t%lf\n", (double)(after - before)/CLOCKS_PER_SEC);
        }

        putchar('\n');
    }

    free_random_data(original);

    return 0;
}
