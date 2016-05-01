#include <iostream>
#include <string>
#include <functional>

#define _USE_MATH_DEFINES   1
#include <complex>

#define GRAPH_NODETYPE  2
#include "graph.hpp"
#include "parser.hpp"
#include "bstree.hpp"

class city_searcher
{
    struct graphelement
    {
        const std::string data;
        graphelement(const std::string &city_name) : data(city_name) {}
    };
    graph<graphelement> g;
    binary_search_tree *bst;

    static double degtorad(const double deg)
    {
        return (double)(deg * M_PI / (double)180);
    }

    static double radtodeg(const double rad)
    {
        return (double)(rad * (double)180 / M_PI);
    }

    static double calc_distance(const double lat1, const double lon1, const double lat2, const double lon2)
    {
        double theta = lon1 - lon2;

        double dist = sin(degtorad(lat1)) * sin(degtorad(lat2))
                    + cos(degtorad(lat1)) * cos(degtorad(lat2)) * cos(degtorad(theta));
        dist = acos(dist);
        dist = radtodeg(dist);
        dist = dist * 60 * 1.1515;
        dist = dist * 1.609344; /* mile to km */
        dist = dist * 1000.00; /* km to m */

        return dist;
    }

public:
    city_searcher(void) : g(35000, [] (const graphelement &a, const graphelement &b) -> bool { return a.data == b.data; }), bst(new binary_search_tree()) {}

    int load(const int argc, const char *argv[])
    {
        /***************************
         * CHECK IF IS FILE EXISTS *
         ***************************/
        if(argc < 2)
        {
            fprintf(stdout, "Warning: Resource file not loaded.\nUsage: %s [path_of_file]\n", argv[0]);
            return 1;
        }

        parser fp;
        if(fp.open(argv[1]) != true)
        {
            fprintf(stdout, "Error: File '%s' not found.\n", argv[1]);
            return 2;
        }

        /***************************
         * READ FILE               *
         ***************************/
        std::cout << "Step 1 of 2: Read a file, add to the vertex of the graph, add to the BST (together) . . . ";
        fp.parse(
            [&] (const std::string &line)
            {
                static int line_number = 0;
                if(++line_number == 1) return;

                std::string arr[5];
                fp.divide_by_delimiter(arr, line, 5, '\t');
                /*
                    arr[0] = StateAbb
                    arr[1] = PlaceName
                    arr[2] = longitude
                    arr[3] = latitude
                    arr[4] = DistancetoCapitalCity_km
                */

                std::string city_name = arr[1];
                double longitude, latitude;
                try
                {
                    longitude = stod(arr[2]);
                    latitude = stod(arr[3]);
                }
                catch(const std::invalid_argument &e)
                {
                    return; /* Invalid line, so we cannot add this line */
                }

                /* Add to graph */
                int key = g.add_vertex(graphelement(arr[1]));
                if(key == -1) /* Duplicate city name */
                {
                    char *temp = new char[5]();
                    for(int i = 1; ; ++i)
                    {
                        std::snprintf(temp, 5, "%d", i);
                        if(g.add_vertex(graphelement(std::string(city_name + " #" + temp))) != -1)
                        {
                            city_name = city_name + " #" + temp;
                            break;
                        }
                    }
                    delete temp;
                }

                /* Add to BST */
                bstelement *element = new bstelement(city_name, key, longitude, latitude);
                bst->add(element);
            }
        );
        std::cout << "Finished." << std::endl;

        std::cout << "Step 2: Add the edges to each vertex . . . ";
        double lat1, lon1, lat2, lon2;
        bst->traverse_level_order(
            [&] (bstnode *node)
            {
                lat1 = node->element->latitude;
                lon1 = node->element->longitude;

                binary_search_tree::traverse_level_order(node,
                    [&] (bstnode *n)
                    {
                        lat2 = n->element->latitude;
                        lon2 = n->element->longitude;
                        if(10000 >= calc_distance(lat1, lon1, lat2, lon2)) g.add_edge(node->element->value, n->element->value);
                    }
                );
            }
        );
        std::cout << "Finished." << std::endl;
    }

    void prompt(void)
    {
        while(true)
        {
            std::string city_name, hop;
            std::cout << "City name: "; std::getline(std::cin, city_name);
            std::cout << "Hop: "; std::getline(std::cin, hop);

            bstnode *n = bst->get_node_by_key(city_name);
            if(n == NULL)
                std::cout << "Error: City name '" << city_name << "' not found." << std::endl;
            else
            {
                int city_code = n->element->value;
                g.traverse(city_code, atoi(hop.c_str()));
            }
        }
    }
};
