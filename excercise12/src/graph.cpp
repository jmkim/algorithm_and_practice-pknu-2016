template<typename T> class graph
{
private:
    struct node
    {
        node(const int key, const T value) : key(key), value(value), next(NULL) {}
        const int key;
        const T value;
        node *next;
    };
    int *table;
    int size;
public:
};
