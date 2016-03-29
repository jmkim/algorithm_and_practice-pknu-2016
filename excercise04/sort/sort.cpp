#include <iostream>
#include <cstring> /* memcpy() */

namespace sort
{
    template <typename T> class data_wrapper
    {
    protected:
        T *data;
        int capacity;   /* Max capacity of data */
        int amount;      /* Current amount of data */
        bool resizable; /* Is data resizable */

        int resize(const int capacity)
        {
            T *data_new = new T[capacity];
            std::memcpy(data_new, data, sizeof(T) * this->capacity);

            delete data;
            data = data_new;

            this->capacity = capacity;
            return this->capacity;
        }
        void do_swap(T &first, T &second)
        {
            T temp = first;
            first = second;
            second = temp;
        }

    public:
        T get(const int index) const { return data[index]; }
        int get_amount(void) const { return amount; }
        int get_capacity(void) const { return capacity; }
        bool is_resizable(void) const { return resizable; }

        virtual T compare(const int first, const int second) = 0;
        void swap(const int first, const int second) { do_swap(data[first], data[second]); }
        int add(const T src)
        {
            if(amount >= capacity && resizable) resize(capacity * 2);
            if(amount >= capacity) return capacity;

            data[amount++] = src;
            return amount;
        }
        void print(void)
        {
            std::cout
                    << "capacity  = " << capacity << std::endl
                    << "amount    = " << amount << std::endl
                    << "resizable = " << std::boolalpha << resizable << std::endl;

            for(int i = 0; i < amount; ++i) std::cout << "data[" << i << "]= " << data[i] << std::endl;
        }


        data_wrapper(void) : capacity(10), amount(0), resizable(true)
        {
            data = new T[capacity];
        }
        data_wrapper(const int capacity) : capacity(capacity), amount(0), resizable(false)
        {
            data = new T[capacity];
        }
        data_wrapper(T *data, const int capacity, const int amount) : capacity(capacity), amount(amount), resizable(false)
        {
            this.data = data;
        }
        ~data_wrapper(void)
        {
            delete data;
        }
    };

    struct int_wrapper : public data_wrapper<int>
    {
        int compare(const int first, const int second) { return (int)(data[first] - data[second]); }
    };

    template <typename T> class sorting_algorithm
    {
    protected:
        virtual void sort(void) = 0;
    };

    template <typename T> class bubble_sort : public sorting_algorithm<T>
    {
    private:
        static void do_sort(data_wrapper<T> *data, const int end)
        {
            if(end <= 0) return;

            for(int i = 0; i + 1 < end; ++i)
                if(data->compare(i, i + 1) > 0) data->swap(i, i + 1);

            return do_sort(data, end - 1);
        }

    public:
        static void sort(data_wrapper<T> *data)
        {
            do_sort(data, data->get_amount());
        }
    };
}
