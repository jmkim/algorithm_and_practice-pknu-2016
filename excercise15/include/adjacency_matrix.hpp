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
#include <algorithm>    /** fill_n definition */
#include <vector>       /** Containers */

namespace algorithm
{

/** Graph implementation with adjacency matrix

    \note   Vertex deletion is not implemented
    \note   Edge deletion is not implemented
    \note   Cannot use double as WeightType
*/
template<
    class           ValueType,                              /**< Vertex value type; operator== should be defined */
    class           WeightType      = unsigned int,         /**< Weight type */
    WeightType      WeightInitValue = UINT_MAX,             /**< Initial value for weight (should not use this value as data) */
    class           KeyType         = unsigned int,         /**< Key type, used to access an array */
    class           KeyArrayType    = std::vector<KeyType>  /**< Array of Key type */
>
class AdjacencyMatrix
{
public:
    typedef size_t      SizeType;

protected:
    const   SizeType        size_;
            WeightType **   edges_;     /**< Edges */
            ValueType *     vertices_;  /**< Vertices */

public:
    /** Constructor */
    AdjacencyMatrix(const SizeType & size_of_matrix)
    : size_(size_of_matrix)
    {
        edges_ = new WeightType *[size_];
        for(KeyType i = 0; i < size_; ++i)
        {
            edges_[i] = new WeightType[size_];

            for(KeyType j = 0; j < size_; ++j)
                edges_[i][j] = WeightInitValue;
        }
    }

    /** Destructor */
    ~AdjacencyMatrix(void)
    {
        for(KeyType i = 0; i < size_; ++i)
            delete[] edges_[i];

        delete edges_;
    }


    /** Test whether there is an edge from the vertices src to dest

        \return     Return true if the edge exists; otherwise return false
        \param[in]  key_src         Key of source (src)
        \param[in]  key_dest        Key of destination (dest)
    */
    inline
    bool
    IsEdgeExist(const KeyType & key_src, const KeyType & key_dest)
    const
    { return edges_[key_src][key_dest] != WeightInitValue; }

    /** Get a key of the vertex with specific value

        If failed to add, return the size of matrix which is an invalid key (maximum key + 1).

        \return     Return the key of vertex if added successfully; otherwise return the size of matrix 
        \param[in]  value_of_vertex     Value of vertex
    */
    KeyType
    GetVertexKey(const ValueType & value_of_vertex)
    {
        for(KeyType key = 0; key < size_; ++key)
        {
            if(vertices_[key] == value_of_vertex)
                return key;
        }

        return size_;
    }

    /** Get a value of the vertex with specific key

        \return     Value of vertex
        \param[in]  key_of_vertex       Key of vertex
    */
    inline
    ValueType
    GetVertexValue(const KeyType & key_of_vertex)
    const
    { return vertices_[key_of_vertex]; }

    /** Set a value of the vertex with specific key

        \param[in]  key_of_vertex       Key of vertex
        \param[in]  value_of_vertex     Value of vertex
    */
    inline
    void
    SetVertexValue(const KeyType & key_of_vertex, const ValueType & value_of_vertex)
    { vertices_[key_of_vertex] = value_of_vertex; }

    /** Get a weight of the edge

        \return     Weight of edge
        \param[in]  key_src         Key of source (src)
        \param[in]  key_dest        Key of destination (dest)
    */
    inline
    WeightType
    GetEdgeWeight(const KeyType & key_src, const KeyType & key_dest)
    const
    { return edges_[key_src][key_dest]; }

    /** Set a weight of the edge

        \param[in]  key_src         Key of source (src)
        \param[in]  key_dest        Key of destination (dest)
        \param[in]  weight          Weight of edge
    */
    inline
    void
    SetEdgeWeight(const KeyType & key_src, const KeyType & key_dest, const WeightType & weight)
    { edges_[key_src][key_dest] = weight; }

    /** Get a count of vertices

        \return     Count of vertices
    */
    inline
    SizeType
    CountOfVertices(void)
    const
    { return size_; }

    /** Get a count of edges

        \return     Count of edges
        \param[in]  key_of_vertex       Key of vertex
    */
    inline
    SizeType
    CountOfEdges(const KeyType & key_of_vertex)
    {
        KeyArrayType dummy;
        return ListOfEdges(dummy, key_of_vertex); }

    /** Get the list of edges

        \return     Size of list
        \param[out] out_edges       List of edges
        \param[in]  key_of_vertex   Key of vertex
    */
    SizeType
    ListOfEdges(KeyArrayType & out_edges, const KeyType & key_of_vertex)
    {
        out_edges.clear();

        WeightType weight;
        for(KeyType key = 0; key < size_; ++key)
        {
            weight = edges_[key_of_vertex][key];
            if(weight != WeightInitValue)
                out_edges.push_back(weight);
        }

        return out_edges.size();
    }
};

} /** ns: algorithm */

#endif /** ! ALGORITHM_ADJACENCYMATRIX_HPP_ */
