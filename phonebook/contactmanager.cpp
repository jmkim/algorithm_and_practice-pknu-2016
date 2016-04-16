#include <string>
#include <functional>
#include <map>

#include "container/element.hpp"
#include "container/binary_tree.hpp"
#include "container/binary_search_tree.hpp"

class contact : private container::element<std::string>
{
private:
    std::map<std::string, std::string> data;

    std::string get_value(const std::string &key)
    {
        auto search = data.find(key);
        if(search == data.end()) return ""; /* Not found - Return the empty string */

        return search->second;
    }

    void insert(const std::string &key, const std::string &value)
    {
        if(key == "name") return; /* Error: Invalid key */

        remove(key); /* Remove old value first */
        data.insert(std::make_pair(key, value));
    }

    void remove(const std::string &key) { data.erase(key); }

public:
    contact(const std::string &name) : element(name) {}

    int export_as_array(std::string out_array[][2], const int array_size)
    {
        int count = 0;
        for(auto pair : data)
        {
            if(count >= array_size && array_size < data.size()) return -1; /* Warn: `array_size' is smaller than `data.size' */

            out_array[count][0] = pair.first; /* Key */
            out_array[count][1] = pair.second; /* Value */

            ++count;
        }

        return count; /* Return a count of pair of data */
    }

    void import_as_array(const std::string array[][2], const int array_size)
    {
        for(int count = 0; count < array_size; ++count)
            insert(array[count][0], array[count][1]);
    }
};

class contactnode : public container::node_p<contact> {};

class contactmanager : private container::binary_search_tree<contactnode, contact>
{
public:
    contactmanager(void) : binary_search_tree<contactnode, contact>() {}

    void add(const std::string data_array[][2], const int array_size = 15)
    {
        contact *c = new contact(data_array[0][1]);
        c->import_as_array(data_array, array_size);
    }

    void remove(const std::string &name)
    {
        const contact c_key(name);
        contactnode *c_node = search(&c_key);
        contact *element = c_node->element; /* TODO: Logic seems awful.. */

        binary_search_tree<contactnode, contact>::remove(&c_key);

        delete element;
    }

    void remove_postorder(void)
    {
        traverse_postorder(root,
            [&] (const contactnode *const c)
            {
                binary_search_tree<contactnode, contact>::remove(c->element); /* TODO: Logic seems awful 2 */
            }
        );
    }

    int lookup(const std::string &name, std::string out_array[][2], const int array_size = 15)
    {
        const contact c_key(name);
        contactnode *c_node = search(&c_key);

        if(c_node == NULL) return 0;

        return c_node->element->export_as_array(out_array, array_size); /* Return a count of pair of data */
    }

    int lookup_inorder(std::string out_array[][15][2], const int array_size = 1000)
    {
        int count = 0;
        traverse_inorder(root,
            [&] (const contactnode *const c)
            {
                c->element->export_as_array(out_array[count], 15);
                ++count;
            }
        );
        return count;
    }
};
