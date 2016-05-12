#include <cstddef>
#include <functional>
#include <iostream>
#include <set>
#include <queue>

#ifndef GRAPH_NODETYPE
#define GRAPH_NODETYPE 0
#endif

template<typename T> class graph
{
private:
    struct node
    {
        const int key;
        const T element;
        node *next;
        node(const int &key, const T &element) : key(key), element(element), next(NULL) {}
    };

    node **table;
    int count;
    int capacity;
    const std::function<bool(T, T)> is_equal;

    void realloc(const int &new_capacity)
    {
        node **o_table = table;
        int o_count = count;
        int o_capacity = capacity;

        table = new node*[new_capacity];
        for(int i = 0; i < capacity; ++i) table[i] = NULL;

        count = 0;
        capacity = new_capacity;

        for(int i = 0; i < o_capacity; ++i)
        {
            node *n = o_table[i];
            while(n != NULL)
            {
                add_vertex(n);
                n = n->next;
            }
        }

        delete o_table;
    }

public:
    graph(const int &initial_capacity, const std::function<bool(T, T)> &is_equal): count(0), capacity(initial_capacity), is_equal(is_equal)
    {
        table = new node*[capacity];

        for(int i = 0; i < capacity; ++i) table[i] = NULL;
    }
    ~graph(void)
    {
        for(int i = 0; i < count; ++i)
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

        delete table;
    }

    void print(void)
    {
        std::cout << "[k: v] value_of_edges" << std::endl;
        for(int tk = 0; tk < capacity; ++tk)
        {
            node *n = table[tk];
            if(n != NULL)
            {
#if GRAPH_NODETYPE == 1
                std::cout << "[" << tk << ": " << n->element << "] ";
#elif GRAPH_NODETYPE == 2
                std::cout << "[" << tk << ": " << n->element.data << "] ";
#endif
                n = n->next;

                while(n != NULL)
                {
#if GRAPH_NODETYPE == 1
                    std::cout << n->element << " -- ";
#elif GRAPH_NODETYPE == 2
                    std::cout << n->element.data << " -- ";
#endif
                    n = n->next;
                }
                std::cout << std::endl;
            }
        }
    }

    void traverse(const int &key, const int &hop)
    {
        std::set<int> visited_keys;
        traverse(table[key], 0, hop, visited_keys);
    }

    void traverse(node *n, const int &hop, const int &max_hop, std::set<int> &visited_keys)
    {
        if(hop > max_hop) return;

        std::queue<int> queue;

        if(hop == 0)
        {
            std::cout << "[" << hop << "] " << n->key << " " << n->element.data << std::endl;
            visited_keys.insert(n->key);
            queue.push(n->key);
        }
        else
            while(n != NULL)
            {
                if(visited_keys.count(n->key) == 0)
                {
                    std::cout << "[" << hop << "] " << n->key << " " << n->element.data << std::endl;
                    visited_keys.insert(n->key);
                    queue.push(n->key);
                }
                n = n->next;
            }

        while(! queue.empty())
        {
            int key = queue.front();

            traverse(table[key]->next, hop + 1, max_hop, visited_keys);
            queue.pop();
        }
    }

    int add_vertex(const T &entry)
    {
        if(contains(entry)) return -1;

        node *n = new node(count, entry);
        add_vertex(n);

        if(count >= capacity) realloc(capacity * 2);

        return n->key;
    }

    void add_vertex(node *n)
    {
        table[count] = n;
        ++count;
    }

    bool add_edge(const int &key_depart, const int &key_dest)
    {
        if(table[key_depart] == NULL || table[key_dest] == NULL) return false;

        node *n = table[key_depart];
        node *p = NULL;

        while(n != NULL)
        {
            if(n->key == key_dest) return true;

            p = n;
            n = n->next;
        }

        node *e = new node(key_dest, table[key_dest]->element);
        p->next = e;

        return true;
    }

    bool contains(const T &entry)
    {
        for(int i = 0; i < count; ++i)
        {
            node *n = table[i];
            while(n != NULL)
            {
                if(is_equal(n->element, entry)) return true;
                n = n->next;
            }
        }
        return false;
    }

    bool is_empty(void)
    {
        return count ? true : false;
    }

    int size(void) const { return count; }
    int length(void) const { return count; }
    int get_capacity(void) const { return capacity; }
    T get_element(const int key) const { return table[key]->element; }
};
