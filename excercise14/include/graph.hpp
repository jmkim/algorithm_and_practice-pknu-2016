#include <vector>

namespace algorithm
{

template<
    class VertexType,                           /**< vertex value type */
    class EdgeType,                             /**< edge value type */
    class VertexEqual           = std::equal<VertexType>,   /**< compare (equality) for vertex value type */
    class EdgeCompare           = std::less<EdgeType>,      /**< compare (less) for edge value type */
    class WeightType            = unsigned int, /**< weight type */
    class WeightDefaultValue    = 0             /**< default value of weight */
>
class Graph
{
public:
    typedef size_t          SizeType;
    typedef unsigned int    KeyType;

    struct VertexNode
    {
        VertexType  value;              /**< value of vertex */
        EdgeNode *  next;               /**< point to edge of this vertex */

        /** Constructor */
        VertexNode(const VertexType & value)
        : value(value)
        , next(NULL)
        { }
    };

    struct EdgeNode
    {
        const   KeyType         key;        /**< key (index of vertex in table) */
                EdgeType        value;      /**< value of edge */
                WeightType      weight;     /**< weight of edge */
                GraphNode *     next;       /**< point to next edge */

        /** Constructor */
        GraphNode(const KeyType &       key,
                  const EdgeType &      value,
                  const WeightType &    weight = WeightDefaultValue)
        : key(key)
        , value(value)
        , weight(weight)
        , next(NULL)
        { }
    };

private:
    std::vector<VertexNode> graph_;

public:
#if 0 /** unblock while graph_ is not a pointer type */
    /** Constructor */
    Graph(void)
    : graph_(new VertexNode[Capacity]())
    , size_(0)
    { }

    /** Destructor */
    ~Graph(void)
    { delete graph_[]; }
#endif

    /** \brief  Test whether there is an edge from the vertices src to dest

        Test whether there is an edge from the verticies depart to dest.
        \return return true if the edge exists; otherwise return false
        \param  key_src     key of source (src)
        \param  key_dest    key of destination (dest)
    */
    bool
    Adjacent(const KeyType & key_src, const KeyType & key_dest)
    {

        while(
        /** (TODO:) Not implemented */
    }

    /** \brief  Adds the vertex

        Adds the vertex, if the graph not have the vertex with specified value already.
        \return return the key of a graph if added successfully; otherwise return -1
        \param  value_of_vertex     value of vertex
    */
    SizeType
    AddVertex(const VertexType & value_of_vertex)
    {
        if(IsVertexExist(value_of_vertex) == true) return -1;

        graph_.push_back(VertexNode(value_of_vertex));
        return graph_.size() - 1;
    }

    /** \brief  Test whether there is a vertex with specified value

        Test whether there is a vertex with specified value.
        \return return true if the vertex exists; otherwise return false
        \param  value_of_vertex     value of vertex
    */
    bool
    IsVertexExist(const VertexType & value_of_vertex)
    {
        for(const VertexNode & v : graph_)
        {
            if(VertexEqual(v.vlaue, value_of_vertex) == 0)
                return true;
        }

        return false;
    }
};

} /* ns:algorithm */
