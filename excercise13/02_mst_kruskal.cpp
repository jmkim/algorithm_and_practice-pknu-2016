#include <set>

template<
    class Graph,
    class GraphNode,
    class MstCapacity   = 100000,
    class Weight        = int,
    class WeightNull    = 0,
    class WeightCompare = std::less<GraphNode>
>
class MinimumSpanningTree
{
    struct MstNode
    {
        const   GraphNode   vertex;
                MstNode *   parent;

        MstNode(const GraphNode & vertex, MstNode * parent)
        : vertex(vertex)
        , parent(parent)
        { }
    };

    MstNode ** root_;
    std::map<int, size_t> tree_size_;
    size_t size_;

public:
    MinimumSpanningTree(void)
    : root_(new MstNode*[MstCapacity]())
    , size_(0)
    { }

    MstNode *
    FindSet(MstNode * vertex)
    {
        if(vertex == NULL)
            return NULL;

        while(vertex != vertex->parent)
        {
            vertex->parent = vertex->parent->parent; /** Path compression */
            vertex = vertex->parent;
        }
        return p;
    }

    void
    Union(MstNode * mstnode_a, MstNode * mstnode_b)
    {
        MstNode * a = FindSet(mstnode_a);
        MstNode * b = FindSet(mstnode_b);

        /** Weighted union */
        if(tree_size_.at(a) > tree_size_.at(b))
        {
            a->parent = b;
            tree_size_.at(a->vertex->key) += tree_size_.at(b->vertex->key);
            tree_size_.erase(b->vertex->key);
        }
        else
        {
            b->parent = a;
            tree_size_.at(b->vertex->key) += tree_size_.at(a->vertex->key);
            tree_size_.erase(a->vertex->key);
        }

    }

    void
    MakeKruskal(const Graph & graph)
    {
        std::set<Weight, std::pair<GraphNode, GraphNode>, WeightCompare> edges;

        graph.traverse(
            [] (GraphNode & edge)
            {
                static GraphNode vertex = edge;

                const Weight w = edge->weight; /** TODO: edge->weight should not used in template */
                if(w == WeightNull) vertex = edge;

                edges.emplace(w, std::make_pair(vertex, edge));
            }
        );

        for(const auto & edge : edges)
        {
            /** TODO: edge.first.key should not used in template */

            if(FindSet(root_[edge.first.key]) != FindSet(table->[edge.second.key]))
            {
                if(root_[edge.first.key] == NULL)
                {
                    root_[edge.first.key] = new MstNode(edge.first, edge.first);
                    tree_size_.emplace(edge.first.key, 1);
                    ++size_;
                }

                if(root_[edge.second.key] == NULL)
                {
                    root_[edge.second.key] = new MstNode(edge.second, root_[edge.first.key]);
                    ++tree_size_.at(FindSet(root_[edge.second.key])->vertex.key);
                    ++size_;
                }
                else if(root_[edge.second.key->parent == NULL])
                {
                    root_[edge.second.key]->parent = root_[edge.first.key];
                    ++tree_size_.at(FindSet(root_[edge.second.key])->vertex.key);
                }
            }
        }
    }
};
