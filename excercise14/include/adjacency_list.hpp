/**
 *
 *  Adjacency List
 *
 *  Weighted graph,
 *  implementation with adjacency list
 *
 *  https://github.com/kdzlvaids/algorithm_and_practice-pknu-2016
 *
 */

#ifndef ALGORITHM_ADJACENCYLIST_HPP_
#define ALGORITHM_ADJACENCYLIST_HPP_ 1

/** Includes */
#include <cstddef>      /** size_t definition */
#include <vector>       /** Containers */
#include <map>          /** Containers */

namespace algorithm
{

/** Graph implementation with adjacency list

    \note   Vertex deletion is not implemented
    \note   Edge deletion is not implemented
    \note   Cannot use double as WeightType
*/
template<
    class       ValueType,                                  /**< Vertex value type; operator== should be defined */
    class       WeightType          = unsigned int,         /**< Weight type */
    WeightType  WeightDefaultValue  = 0,                    /**< Default value of weight */
    class       KeyType             = unsigned int,         /**< Key type, used to access an array */
    class       KeyArrayType        = std::vector<KeyType>  /**< Array of Key type */
>
class AdjacencyList
{
public:
    typedef size_t                              SizeType;
    typedef std::map<const KeyType, WeightType> EdgeType;   /**< Edges of vertex
                                                                \param  KeyType     key_dest
                                                                \param  WeightType  weight
                                                            */

    /** Vertex class

        Each vertex has an array for its edges as a member.
    */
    struct VertexNode
    {
        const   KeyType             key;        /**< Key of vertex; same with index in vertices_ */
                ValueType           value;      /**< Value of vertex */
                EdgeType            edges;      /**< Edges */
                //SizeType            edges_size; /**< Count of edges; forward_list not support size() function */

        /** Constructor */
        VertexNode(const KeyType & key, const ValueType & value)
        : key(key)
        , value(value)
        { }
    };

protected:
    std::vector<VertexNode> vertices_; /**< Vertices */

public:
    /** Add a vertex, if a list not have the vertex with specific value already

        \return     Return the key of vertex if added successfully; otherwise return -1
        \param[in]  value_of_vertex     Value of vertex
    */
    KeyType
    AddVertex(const ValueType & value_of_vertex)
    {
        KeyType key_of_vertex = GetVertexKey(value_of_vertex);

        if(key_of_vertex == CountOfVertices()) /** Not found */
            vertices_.push_back(VertexNode(key_of_vertex, value_of_vertex));

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
        vertices_.at(key_src).edges.insert(
            std::make_pair<const KeyType, WeightType> (KeyType(key_dest), WeightType(weight))
        );
    }

    /** Test whether the key of vertex less than its maximum bound

        \return     Return true if the vertex exists; otherwise return false
        \param[in]  key_of_vertex   Key of vertex
    */
    inline
    bool
    IsVertexExist(const KeyType & key_of_vertex)
    const
    {
        try
        { vertices_.at(key_of_vertex); } /** .at() throws exception */
        catch(std::out_of_range & e)
        { return false; /** key_of_vertex is over the maximum bound */ }

        return true;
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
    { return vertices_.at(key_src).edges.find(key_dest) != vertices_.at(key_src).edges.end(); }

    /** Get a key of the vertex with specific value

        If failed to add, return the size of list which is an invalid key (maximum key + 1).

        \return     Return the key of vertex if added successfully; otherwise return the size of list
        \param[in]  value_of_vertex     Value of vertex
    */
    KeyType
    GetVertexKey(const ValueType & value_of_vertex)
    {
        for(const VertexNode & vertex : vertices_)
        {
            if(vertex.value == value_of_vertex)
                return vertex.key;
        }

        return CountOfVertices();
    }

    /** Get a value of the vertex with specific key

        \return     Value of vertex
        \param[in]  key_of_vertex       Key of vertex
    */
    inline
    ValueType
    GetVertexValue(const KeyType & key_of_vertex)
    const
    { return vertices_.at(key_of_vertex).value; }

    /** Set a value of the vertex with specific key

        \param[in]  key_of_vertex       Key of vertex
        \param[in]  value_of_vertex     Value of vertex
    */
    inline
    void
    SetVertexValue(const KeyType & key_of_vertex, const ValueType & value_of_vertex)
    { vertices_.at(key_of_vertex).value = value_of_vertex; }

    /** Get a weight of the edge

        \return     Weight of edge
        \param[in]  key_src         Key of source (src)
        \param[in]  key_dest        Key of destination (dest)
    */
    inline
    WeightType
    GetEdgeWeight(const KeyType & key_src, const KeyType & key_dest)
    const
    { return vertices_.at(key_src).edges.at(key_dest); }

    /** Set a weight of the edge

        \param[in]  key_src         Key of source (src)
        \param[in]  key_dest        Key of destination (dest)
        \param[in]  weight          Weight of edge
    */
    inline
    void
    SetEdgeWeight(const KeyType & key_src, const KeyType & key_dest, const WeightType & weight)
    { vertices_.at(key_src).edges.at(key_dest) = weight; }

    /** Get a count of vertices

        \return     Count of vertices
    */
    inline
    SizeType
    CountOfVertices(void)
    const
    { return vertices_.size(); }

    /** Get a count of edges

        \return     Count of edges
        \param[in]  key_of_vertex       Key of vertex
    */
    inline
    SizeType
    CountOfEdges(const KeyType & key_of_vertex)
    const
    { return vertices_.at(key_of_vertex).edges.size(); }

    /** Get the list of edges

        \return     Size of list
        \param[out] out_edges       List of edges
        \param[in]  key_of_vertex   Key of vertex
    */
    SizeType
    ListOfEdges(KeyArrayType & out_edges, const KeyType & key_of_vertex)
    {
        out_edges.clear();

        for(auto & edge : vertices_.at(key_of_vertex).edges)
            out_edges.push_back(edge);

        return out_edges.size();
    }
};

} /** ns: algorithm */

#endif /** ! ALGORITHM_ADJACENCYLIST_HPP_ */
