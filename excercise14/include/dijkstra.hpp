/**
 *
 *  Graph with Dijkstra algorithm
 *
 *  An inherited class for searching the shortest path
 *  https://github.com/kdzlvaids/algorithm_and_practice-pknu-2016
 *
 */

#ifndef ALGORITHM_DIJKSTRA_HPP_
#define ALGORITHM_DIJKSTRA_HPP_ 1

/** Includes */
#include "graph.hpp"
#include <deque>
#include <map>
#include <set>
#include <queue>

namespace algorithm
{

/** Graph with Dijkstra algorithm

    \note   Depends deeply with algorithm::Graph
*/
template<
    class       ValueType,                                  /**< Vertex value type; operator== should be defined */
    class       WeightType          = unsigned int,         /**< Weight type */
    WeightType  WeightDefaultValue  = 0,                    /**< Default value of weight */
    class       KeyType             = unsigned int,         /**< Key type */
    class       KeyArrayType        = std::deque<KeyType>   /**< Array of Key type */
>
class Dijkstra : public Graph<ValueType, WeightType, WeightDefaultValue, KeyType, KeyArrayType>
{
public:
    /** Get a shortest distance with Dijkstra algorithm

        Overrides GetShortestPath(const KeyType &, const KeyType &, KeyArrayType &)

        \return     Distance
        \param[in]  key_src     Key of source (src)
        \param[in]  key_dest    Key of destination (dest)
    */
    WeightType
    GetShortestPath(const KeyType & key_src, const KeyType & key_dest)
    {
        KeyArrayType dummy; /** Dummy array for calling */
        return GetShortestPath(key_src, key_dest, dummy);
    }

    /** Get a shortest distance with Dijkstra algorithm

        \return     Distance
        \param[in]  key_src     Key of source (src)
        \param[in]  key_dest    Key of destination (dest)
        \param[out] out_path    Array to store the path (Optional)
    */
    WeightType
    GetShortestPath(const KeyType & key_src, const KeyType & key_dest, KeyArrayType & out_path)
    {
        std::map<KeyType, WeightType>   edge_distance_;         /**< Record distance from key_src */
        std::map<KeyType, KeyType>      edge_src_;              /**< Record source of edge (`from' vertex) */
        std::set<KeyType>               vertex_determined_;     /**< Record determined vertex */
        std::priority_queue<
            std::pair<WeightType, KeyType>
        > vertex_pqueue_;                                       /**< Vertex to visit; minimum heap */

        edge_distance_.insert(
            std::make_pair<KeyType, WeightType>
            (
                KeyType(key_src),
                0
            ));

        vertex_pqueue_.push(
            std::make_pair<WeightType, KeyType>
            (
                0,
                KeyType(key_src)
            ));

        edge_src_.erase(key_src);
        edge_src_.insert(
            std::make_pair<KeyType, KeyType>
            (
                KeyType(key_src),
                KeyType(key_src)
            ));

        while(vertex_pqueue_.empty() != true && vertex_pqueue_.top().first != key_dest)
        {
            std::pair<WeightType, KeyType> kwpair = vertex_pqueue_.top();
            vertex_pqueue_.pop();

            KeyType     key     = kwpair.second;
            WeightType  weight  = kwpair.first;  /** Not used */

            vertex_determined_.insert(key);

            for(auto & edge : Graph<ValueType, WeightType, WeightDefaultValue, KeyType, KeyArrayType>::graph_.at(key).edges)
            {
                KeyType     k   = edge.first;
                WeightType  w   = edge.second;

                if(vertex_determined_.find(k) != vertex_determined_.end()) /** Visited vertex -> skip */
                    continue;

                vertex_determined_.insert(k);
                
                WeightType distance = edge_distance_.at(key) + w;

                if(edge_distance_.find(k) == edge_distance_.end()
                    || edge_distance_.at(k) > distance)
                {
                    edge_distance_.insert(
                        std::make_pair<KeyType, WeightType>
                        (
                            KeyType(k),
                            WeightType(distance)
                        ));
                    vertex_pqueue_.push(
                        std::make_pair<WeightType, KeyType>
                        (
                            WeightType(w),
                            KeyType(k)
                        ));

                    edge_src_.erase(k);
                    edge_src_.insert(
                        std::make_pair<KeyType, KeyType>
                        (
                            KeyType(k),
                            KeyType(key)
                        ));

                    /** operator< for pair -- http://en.cppreference.com/w/cpp/utility/pair/operator_cmp */
                }
            }
        }

        KeyType key = key_dest;
        while(key != key_src)
        {
            out_path.push_front(key);
            key = edge_src_.at(key);
        }
        out_path.push_front(key);   /** Departure */

        return edge_distance_.at(key_dest);
    }
};

} /** ns: algorithm */

#endif /** ! ALGORITHM_DIJKSTRA_HPP_ */
