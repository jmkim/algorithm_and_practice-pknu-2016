#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_ 1

#include <iostream>
#include <functional>

template<typename T> class hash_set
{
private:
    struct node
    {
        node(T element) : element(element), next(NULL) {}
        T element;
        node *next;
    };

    node **table;
    int count;
    int capacity;
    const float load_factor;
    const std::function<unsigned int(T)> hash_code;

    void realloc(const int new_capacity)
    {
        node **o_table = table;
        int o_count = count;
        int o_capacity = capacity;

        table = new node*[new_capacity];
        count = 0;
        capacity = new_capacity;

        for(int tk = 0; tk < o_capacity; ++tk)
        {
            node *n = o_table[tk];
            node *p = NULL;
            while(n != NULL)
            {
                p = n->next;
                add(n);
                n = p;
            }
        }

        delete o_table;
    }

public:
    hash_set(const int initial_capacity, const float load_factor, const std::function<unsigned int(T)> hash_code) : count(0), capacity(initial_capacity), load_factor(load_factor), hash_code(hash_code)
    { table = new node*[initial_capacity]; }

    ~hash_set(void) { delete table; }

    void print(std::function<void(int, T)> output)
    {
        for(int tk = 0; tk < capacity; ++tk)
        {
            std::cout << "[" << capacity << "] ";
            node *n = table[tk];
            while(n != NULL)
            {
                output(tk, n->element);
                n = n->next;
            }
        }
    }

    void print(void)
    {
        std::cout << "[k: v] value_of_edges" << std::endl;
        for(int tk = 0; tk < capacity; ++tk)
        {
            node *n = table[tk];
            if(n != NULL)
            {
                std::cout << "[" << tk << ": " << n->element << "] ";
                n = n->next;

                while(n != NULL)
                {
                    std::cout << n->element << " -- ";
                    n = n->next;
                }
                std::cout << std::endl;
            }
        }
    }

    bool add(const T entry)
    {
        if(contains(entry)) return false;

        add(new node(entry));

        if((double)count >= capacity * load_factor)
            realloc((int)(capacity * load_factor * 2));

        return true;
    }

    void add(node *n)
    {
        unsigned int hash = hash_code(n->element) % capacity;

        n->next = table[hash];
        table[hash] = n;

        ++count;
    }

    void clear(void)
    {
        for(int i = 0; i < capacity; ++i)
        {
            node *n = table[i];
            while(n != NULL)
            {
                node *f = n->next;
                delete n;

                --count;
                n = f;
            }
        }
    }

    bool contains(const T entry)
    {
        node *n = table[hash_code(entry) % capacity];
        while(n != NULL)
        {
            if(n->element == entry) return true;
            n = n->next;
        }
        return false;
    }

    bool is_empty(void)
    {
        return count ? true : false;
    }

    bool remove(const T entry)
    {
        node *n = table[hash_code(entry) % capacity];
        node *p = NULL;
        while(n != NULL)
        {
            if(n->element == entry)
            {
                if(p != NULL) p->next = n->next;
                delete n;
                
                --count;
                return true;
            }
            p = n;
            n = n->next;
        }
        return false;
    }

    int size(void) { return count; }
    int length(void) { return count; }
    int get_capacity(void) { return capacity; }
};

#endif /* ! HASH_TABLE_H_ */
