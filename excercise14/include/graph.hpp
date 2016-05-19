/**
 *
 *  Graph
 *
 *  Undirected, weighted graph
 *  https://github.com/kdzlvaids/algorithm_and_practice-pknu-2016
 *
 */

/** Includes */
#include <cstddef> /** To define size_t */

/** STL containers */
#include <vector>
#include <forward_list>

namespace algorithm
{

/** \brief Graph class

    Undirected, weighted graph class.
    TODO: Vertex deletion is not implemented
    TODO: Edge deletion is not implemented
*/
template<
    class       ValueType,                            /**< vertex value type; operator== should be defined */
    class       WeightType            = unsigned int, /**< weight type */
    WeightType  WeightDefaultValue    = 0             /**< default value of weight */
>
class Graph
{
public:
    typedef size_t              SizeType;
    typedef unsigned int        KeyType;        /**< key type, used to access an array */

    /** \brief  Test if two keys are equal

        Test if two keys are equal.
        \return return true if two keys are equal; otherwise return false
        \param  key_first   first key to compare
        \param  key_second  second key to compare
    */
    bool
    IsKeyEqual(const KeyType & key_first, const KeyType & key_second)
    { return key_first == key_second; }

    /** \brief  Vertex class

        Vertex class.
        Each vertex has an array for its edges as a member.
    */
    struct VertexNode
    {
        const   KeyType             key;        /**< key of vertex; same with index in graph_ */
                ValueType           value;      /**< value of vertex */
                std::forward_list<
                    std::pair<const KeyType, WeightType>
                > edges;                        /**< edges of vertex
                                                    \param  const KeyType   key_dest
                                                    \param  WeightType      weight
                                                */
                SizeType            edges_size; /**< count of edges; forward_list not support size() function */

        /** Constructor */
        VertexNode(const KeyType & key, const ValueType & value)
        : key(key)
        , value(value)
        , edges_size(0)
        { }

        /** \brief  Test if two values are equal

            Test if two values are equal.
            \return return true if two values are equal; otherwise return false
            \param  value   value to compare
        */
        bool
        IsValueEqual(const ValueType & value)
        { return this.value == value; }
    };

private:
    std::vector<VertexNode> graph_; /**< graph */

public:
    /** \brief  Test whether there is an edge from the vertices src to dest

        Test whether there is an edge from the vertices depart to dest.
        \return return true if the edge exists; otherwise return false
        \param  key_src     key of source (src)
        \param  key_dest    key of destination (dest)
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

    /** \brief  Add a vertex

        Add a vertex, if a graph not have the vertex with specified value already.
        \return return the key of vertex if added successfully; otherwise return -1
        \param  value_of_vertex     value of vertex
    */
    KeyType
    AddVertex(const ValueType & value_of_vertex)
    {
        KeyType key_of_vertex = GetVertexKey(value_of_vertex);

        if(key_of_vertex == GetVertexCount()) /** Not found */
            graph_.push_back(VertexNode(key_of_vertex, value_of_vertex));

        return key_of_vertex;
    }

    /** \brief  Add an edge

        Add an edge connects two vertices.
        \param  key_src     key of source (src)
        \param  key_dest    key of destination (dest)
        \param  weight      weight of the edge
    */
    void
    AddEdge(const KeyType & key_src, const KeyType & key_dest, const WeightType & weight = WeightDefaultValue)
    {
        graph_.at(key_src).edges.push_front(
            std::make_pair<const KeyType, WeightType> (key_dest, weight)
        );
        ++graph_.at(key_src).edges_size;
    }

    /** \brief  Get a key of the vertex with specified value

        Get a key of the vertex with specified value from a graph.
        If failed to add, return the size of graph which is an invalid key (maximum key + 1).
        \return return the key of vertex if added successfully; otherwise return the size of graph
        \param  value_of_vertex     value of vertex
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

    /** \brief  Get a value of the vertex with specified key

        Get a value of the vertex with specified key from a graph.
        \return return the value
        \param  key_of_vertex   key of vertex
    */
    inline
    ValueType
    GetVertexValue(const KeyType & key_of_vertex)
    { return graph_.at(key_of_vertex).value; }

    /** \brief  Set a value of the vertex with specified key

        Set a value of the vertex with specified key from a graph.
        \param  key_of_vertex       key of vertex
        \param  value_of_vertex     value of vertex
    */
    inline
    void
    SetVertexValue(const KeyType & key_of_vertex, const ValueType & value_of_vertex)
    { graph_.at(key_of_vertex).value = value_of_vertex; }

    /** \brief  Get a count of vertices

        Get a count of vertices
        \return count of vertices
    */
    inline
    SizeType
    GetVertexCount(void)
    { return graph_.size(); }

    /** \brief  Get a count of edges

        Get a count of edges
        \return count of edges
        \param  key_of_vertex       key of vertex
    */
    inline
    SizeType
    GetVertexEdgeCount(const KeyType & key_of_vertex)
    { return graph_.at(key_of_vertex).edges_size; }
};

} /** ns: algorithm */
