/**
 *
 *  Graph
 *
 *  Undirected, weighted graph
 *  https://github.com/kdzlvaids/algorithm_and_practice-pknu-2016
 *
 */

#ifndef ALGORITHM_GRAPH_HPP_
#define ALGORITHM_GRAPH_HPP_ 1

/** Includes */
#include <cstddef>          /** size_t definition */
#include <vector>           /** Containers */
#include <forward_list>     /** Containers */

namespace algorithm
{

/** Undirected, weighted graph class

    \note   Vertex deletion is not implemented
    \note   Edge deletion is not implemented
    \note   Cannot use double as WeightType
*/
template<
    class       ValueType,                            /**< Vertex value type; operator== should be defined */
    class       WeightType            = unsigned int, /**< Weight type */
    WeightType  WeightDefaultValue    = 0             /**< Default value of weight */
>
class Graph
{
public:
    typedef size_t              SizeType;
    typedef unsigned int        KeyType;        /**< Key type, used to access an array */

    /** Test if two keys are equal

        \return     Return true if two keys are equal; otherwise return false
        \param[in]  key_first       First key to compare
        \param[in]  key_second      Second key to compare
    */
    bool
    IsKeyEqual(const KeyType & key_first, const KeyType & key_second)
    const
    { return key_first == key_second; }

    /** Vertex class

        Each vertex has an array for its edges as a member.
    */
    struct VertexNode
    {
        const   KeyType             key;        /**< Key of vertex; same with index in graph_ */
                ValueType           value;      /**< Value of vertex */
                std::forward_list<
                    std::pair<const KeyType, WeightType>
                > edges;                        /**< Edges of vertex
                                                    \param  KeyType     key_dest
                                                    \param  WeightType  weight
                                                */
                SizeType            edges_size; /**< Count of edges; forward_list not support size() function */

        /** Constructor */
        VertexNode(const KeyType & key, const ValueType & value)
        : key(key)
        , value(value)
        , edges_size(0)
        { }

        /** Test if two values are equal

            \return     Return true if two values are equal; otherwise return false
            \param[in]  value       Value to compare
        */
        bool
        IsValueEqual(const ValueType & value)
        const
        { return this->value == value; }
    };

private:
    std::vector<VertexNode> graph_; /**< Graph */

public:
    /** Test whether there is an edge from the vertices src to dest

        \return     Return true if the edge exists; otherwise return false
        \param[in]  key_src         Key of source (src)
        \param[in]  key_dest        Key of destination (dest)
    */
    bool
    Adjacent(const KeyType & key_src, const KeyType & key_dest)
    {
        for(auto & edge : graph_.at(key_src)->edges)
        {
            if(IsKeyEqual(edge.first, key_dest) == true) /** Found */
                return true;
        }

        return false; /** Not found */
    }

    /** Add a vertex, if a graph not have the vertex with specified value already

        \return     Return the key of vertex if added successfully; otherwise return -1
        \param[in]  value_of_vertex     Value of vertex
    */
    KeyType
    AddVertex(const ValueType & value_of_vertex)
    {
        KeyType key_of_vertex = GetVertexKey(value_of_vertex);

        if(key_of_vertex == GetVertexCount()) /** Not found */
            graph_.push_back(VertexNode(key_of_vertex, value_of_vertex));

        return key_of_vertex;
    }

    /** Add an edge to connect two vertices

        \param[in]  key_src         Key of source (src)
        \param[in]  key_dest        Key of destination (dest)
        \param[in]  weight          Weight of the edge
    */
    void
    AddEdge(const KeyType & key_src, const KeyType & key_dest, const WeightType & weight = WeightDefaultValue)
    {
        graph_.at(key_src).edges.push_front(
            std::make_pair<const KeyType, WeightType> (KeyType(key_dest), WeightType(weight))
        );
        ++graph_.at(key_src).edges_size;
    }

    /** Get a key of the vertex with specified value from a graph

        If failed to add, return the size of graph which is an invalid key (maximum key + 1).

        \return     Return the key of vertex if added successfully; otherwise return the size of graph
        \param[in]  value_of_vertex     Value of vertex
    */
    KeyType
    GetVertexKey(const ValueType & value_of_vertex)
    {
        for(const VertexNode & vertex : graph_)
        {
            if(vertex.IsValueEqual(value_of_vertex) == true)
                return vertex.key;
        }

        return GetVertexCount();
    }

    /** Get a value of the vertex with specified key from a graph

        \return     Return the value
        \param[in]  key_of_vertex       Key of vertex
    */
    inline
    ValueType
    GetVertexValue(const KeyType & key_of_vertex)
    const
    { return graph_.at(key_of_vertex).value; }

    /** Set a value of the vertex with specified key from a graph

        \param[in]  key_of_vertex       Key of vertex
        \param[in]  value_of_vertex     Value of vertex
    */
    inline
    void
    SetVertexValue(const KeyType & key_of_vertex, const ValueType & value_of_vertex)
    { graph_.at(key_of_vertex).value = value_of_vertex; }

    /** Get a count of vertices

        \return     Count of vertices
    */
    inline
    SizeType
    GetVertexCount(void)
    const
    { return graph_.size(); }

    /** Get a count of edges

        \return     Count of edges
        \param[in]  key_of_vertex       Key of vertex
    */
    inline
    SizeType
    GetVertexEdgeCount(const KeyType & key_of_vertex)
    const
    { return graph_.at(key_of_vertex).edges_size; }
};

} /** ns: algorithm */

#endif /** ! ALGORITHM_GRAPH_HPP_ */
