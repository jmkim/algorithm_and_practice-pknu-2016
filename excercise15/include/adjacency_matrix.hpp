/**
 *
 *  Adjacency Matrix
 *
 *  Weighted graph,
 *  implementation with adjacency matrix
 *
 *  https://github.com/kdzlvaids/algorithm_and_practice-pknu-2016
 *
 */

#ifndef ALGORITHM_ADJACENCYMATRIX_HPP_
#define ALGORITHM_ADJACENCYMATRIX_HPP_ 1

/** Includes */
#include <cstddef>      /** size_t definition */
#include <climits>      /** UINT_MAX definition */
#include <vector>       /** Containers */
#include <array>        /** Containers */

namespace algorithm
{

/** Graph implementation with adjacency matrix

    \note   Vertex deletion is not implemented
    \note   Edge deletion is not implemented
    \note   Cannot use double as WeightType
*/
template<
    size_t          MatrixSize,
    class           ValueType,                              /**< Vertex value type; operator== should be defined */
    class           WeightType      = unsigned int,         /**< Weight type */
    WeightType      WeightInitValue = UINT_MAX,             /**< Initial value for weight (should not use this value as data) */
    class           KeyType         = unsigned int,         /**< Key type, used to access an array */
    class           KeyArrayType    = std::vector<KeyType>  /**< Array of Key type */
>
class AdjacencyMatrix
{
public:
    typedef size_t  SizeType;

protected:
    std::array<ValueType, MatrixSize>                           vertices_;  /**< Vertices */
    std::array<std::array<WeightType, MatrixSize>, MatrixSize>  edges_;     /**< Edges */

public:
    /** Constructor */
    AdjacencyMatrix(void)
    { edges_.fill(WeightInitValue); }

    /** Add an edge to connect two vertices

        \param[in]  key_src         Key of source (src)
        \param[in]  key_dest        Key of destination (dest)
        \param[in]  weight          Weight of the edge
    */
    void
    AddEdge(const KeyType & key_src, const KeyType & key_dest, const WeightType & weight)
    { edges_.at(key_src).at(key_dest) = weight; }

    /** Test whether there is an edge from the vertices src to dest

        \return     Return true if the edge exists; otherwise return false
        \param[in]  key_src         Key of source (src)
        \param[in]  key_dest        Key of destination (dest)
    */
    inline
    bool
    IsEdgeExist(const KeyType & key_src, const KeyType & key_dest)
    const
    { return edges_.at(key_src).at(key_dest) != WeightInitValue; }

    /** Get a key of the vertex with specific value

        If failed to add, return the size of matrix which is an invalid key (maximum key + 1).

        \return     Return the key of vertex if added successfully; otherwise return the size of matrix 
        \param[in]  value_of_vertex     Value of vertex
    */
    KeyType
    GetVertexKey(const ValueType & value_of_vertex)
    {
        for(KeyType key = 0; key < MatrixSize; ++key)
        {
            if(vertices_.at(key) == value_of_vertex)
                return key;
        }

        return (KeyType)MatrixSize;
    }

    /** Get a value of the vertex with specific key

        \return     Value of vertex
        \param[in]  key_of_vertex       Key of vertex
    */
    inline
    ValueType
    GetVertexValue(const KeyType & key_of_vertex)
    const
    { return vertices_.at(key_of_vertex); }

    /** Set a value of the vertex with specific key

        \param[in]  key_of_vertex       Key of vertex
        \param[in]  value_of_vertex     Value of vertex
    */
    inline
    void
    SetVertexValue(const KeyType & key_of_vertex, const ValueType & value_of_vertex)
    { vertices_.at(key_of_vertex) = value_of_vertex; }

    /** Get a weight of the edge

        \return     Weight of edge
        \param[in]  key_src         Key of source (src)
        \param[in]  key_dest        Key of destination (dest)
    */
    inline
    WeightType
    GetEdgeWeight(const KeyType & key_src, const KeyType & key_dest)
    const
    { return edges_.at(key_src).at(key_dest); }

    /** Set a weight of the edge

        \param[in]  key_src         Key of source (src)
        \param[in]  key_dest        Key of destination (dest)
        \param[in]  weight          Weight of edge
    */
    inline
    void
    SetEdgeWeight(const KeyType & key_src, const KeyType & key_dest, const WeightType & weight)
    { edges_.at(key_src).at(key_dest) = weight; }

    /** Get a count of edges

        \return     Count of edges
        \param[in]  key_of_vertex       Key of vertex
    */
    inline
    SizeType
    CountOfEdges(const KeyType & key_of_vertex)
    { return ListOfEdges(KeyArrayType(), key_of_vertex); }

    /** Get the list of edges

        \return     Size of list
        \param[out] out_edges       List of edges
        \param[in]  key_of_vertex   Key of vertex
    */
    SizeType
    ListOfEdges(KeyArrayType & out_edges, const KeyType & key_of_vertex)
    {
        out_edges.clear();

        for(auto & weight : edges_.at(key_of_vertex))
        {
            if(weight != WeightInitValue)
                out_edges.push_back(weight);
        }

        return out_edges.size();
    }
};

} /** ns: algorithm */

#endif /** ! ALGORITHM_ADJACENCYMATRIX_HPP_ */
