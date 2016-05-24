/**
 *
 *  Find the shortest path from a list of cities
 *  Read more: https://github.com/kdzlvaids/algorithm_and_practice-pknu-2016/blob/master/excercise14/README.pdf
 *
 *  https://github.com/kdzlvaids/algorithm_and_practice-pknu-2016
 *
 */

/** Includes */
#include <iostream>
#include <string>
#include <cctype>   /** std::isspace definition */
#include "include/filereader.hpp"
#include "include/dijkstra.hpp"

#include <map>
#include <deque>

/** Flags */
//#define FLAG_DO_NOT_CHECK_DUPLICATES

/** Type definitions */
typedef unsigned int    CityKeyType;
typedef std::string     CityNameType;
typedef size_t          SizeType;
typedef unsigned int    WeightType;

int
main(const int argc, const char * argv[])
{
    /** Variables */
    int count_of_vertices;
    int count_of_edges;

    algorithm::FileReader<CityNameType, std::deque<CityNameType> >  fstream;    /** File stream */
    algorithm::Dijkstra<CityNameType>                               graph;      /** Graph */
    std::map<CityNameType, CityKeyType>                             tree;       /** Tree; <City name, Key of graph> */

    {
        /** Open a file and associate it to file stream */

        if(argc < 2) /** Path of the file not provided */
        {
            std::cerr << "Usage: " << argv[0] << " [path of resource file]" << std::endl;
            return 2;
        }

        fstream.Open(argv[1]); /** Open the file */

        if(fstream.IsOpen() == false) /** File is not exists */
        {
            std::cerr << "Error: File '" << argv[1] << "' not found." << std::endl;
            return 1;
        }
    }

    {
        /** Print the flags (which is applied in compile time) */

        std::cout   << "Enabled flags: "
#       ifdef          DO_NOT_CHECK_DUPLICATES
                    << "DO_NOT_CHECK_DUPLICATES "
#       endif
                    << std::endl;
    }

    {
        /** Read file line by line */

        CityNameType line;


        /** Read line which defines count of vertices */

        while(true)
        {
            if(fstream.ReadLine(line) <= 0 || line.at(0) == '#' || std::isspace(line.at(0)) == true)
                continue;
            else
            {
                count_of_vertices = stoi(line);
                break;
            }
        }
        std::cout << "Count of vertices defined in file: " << count_of_vertices << std::endl;


        /** Add vertices to graph */

        for(int i = 0; i < count_of_vertices; ++i)
        {
            if(fstream.ReadLine(line) <= 0 || line.at(0) == '#' || std::isspace(line.at(0)) == true)
            {
                --i;
                continue;
            }
            else
            {
                CityNameType city_name = line;

#ifndef FLAG_DO_NOT_CHECK_DUPLICATES
                for(int suffix = 2; ; ++suffix)
                {
                    if(tree.find(city_name) != tree.end()) /** City name duplicates */
                        city_name = line + " #" + std::to_string(suffix);
                    else
                        break;
                }
#endif /** ! FLAG_DO_NOT_CHECK_DUPLICATES */

                CityKeyType key = graph.AddVertex(city_name);
                tree.insert(std::make_pair(city_name, key));
            }
        }
        std::cout << "Count of vertices: " << graph.CountOfVertices() << std::endl;


        /** Read line which defines count of edges */

        while(true)
        {
            if(fstream.ReadLine(line) <= 0 || line.at(0) == '#' || std::isspace(line.at(0)) == true)
                continue;
            else
            {
                count_of_edges = stoi(line);
                break;
            }
        }
        std::cout << "Count of edges defined in file: " << count_of_edges << std::endl;


        /** Add edges to graph */

        for(int i = 0; i < count_of_edges; ++i)
        {
            if(fstream.ReadLine(line) <= 0 || line.at(0) == '#' || std::isspace(line.at(0)) == true)
            {
                --i;
                continue;
            }
            else
            {
                std::deque<CityNameType> tokens;
                fstream.DivideByDelimiter(tokens, line, " ");

                CityKeyType     key_src     = stoi(tokens.at(0));
                CityKeyType     key_dest    = stoi(tokens.at(1));
                WeightType      weight      = WeightType(stod(tokens.at(2)));

                graph.AddEdge(key_src,  key_dest, weight);
                graph.AddEdge(key_dest, key_src,  weight);
            }
        }

        SizeType num_edges = 0;

        for(CityKeyType vk = 0; vk < graph.CountOfVertices(); ++vk)
            num_edges += graph.CountOfEdgeOfVertices(vk);

        std::cout << "Count of edges: " << num_edges << std::endl;
    }

    {
        /** Prompt to get names of the city, and find the shortest path */

        while(true)
        {
            CityKeyType     key_depart,     key_dest;
            CityNameType    name_depart,    name_dest;


            /** Get a name of the city for starting point */

            std::cout   << "Starting point: ";
            std::getline(std::cin, name_depart);
            if(tree.find(name_depart) == tree.end()) /** Not found */
            {
                std::cout << "Error: City named '" << name_depart << "' not found." << std::endl;
                continue;
            }


            /** Get a name of the city for destination */

            std::cout   << "Destination: ";
            std::getline(std::cin, name_dest);
            if(tree.find(name_dest) == tree.end()) /** Not found */
            {
                std::cout << "Error: City named '" << name_dest << "' not found." << std::endl;
                continue;
            }


            /** Get a key of the city using its name */

            key_depart  = tree.at(name_depart);
            key_dest    = tree.at(name_dest);

            std::cout << "Starting point is ["  << key_depart   << "] " << name_depart  << std::endl;
            std::cout << "Destination is ["     << key_dest     << "] " << name_dest    << std::endl;


            /** Find the shortest path using Dijkstra algorithm */

            std::deque<CityKeyType> path;

            WeightType      distance    = graph.GetShortestPath(key_depart, key_dest, path);


            /** Print the shortest path */

            CityKeyType     key_prev    = key_depart;
            WeightType      dist_sum    = 0;

            for(auto & key : path)
            {
                dist_sum += ((key_prev != key) ? graph.GetEdgeWeight(key_prev, key) : 0);
                std::cout   << "[" << key << "] "
                            << graph.GetVertexValue(key)
                            << " ("
                            << ((key_prev != key) ? graph.GetEdgeWeight(key_prev, key) : 0) /** Weight of edge (key, key_prev) */
                            << "m/"
                            << dist_sum /** Sum of weights until this key */
                            << "m)"
                            << std::endl;
                key_prev = key;
            }

            std::cout << "Distance: " << distance << " m" << std::endl;
        }
    }

    return 0;
}
