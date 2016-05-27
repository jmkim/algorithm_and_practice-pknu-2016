/**
 *
 *  PageRank
 *
 *  https://github.com/kdzlvaids/algorithm_and_practice-pknu-2016
 *
 */

#ifndef ALGORITHM_PAGERANK_HPP_
#define ALGORITHM_PAGERANK_HPP_ 1

/** Includes */
#include "adjacency_matrix.hpp"
#include <vector>
#include <map>
#include <tuple>

namespace algorithm
{

/** PageRank algorithm

    \note   Depends deeply with algorithm::AdjacencyMatrix
*/
template<
    class   GraphType,
    class   WeightType      = double,                   /**< Weight type */
    class   WeightArrayType = std::vector<WeightType>   /**< Array of weight type */
>
class PageRank
{
public:
    typedef size_t          SizeType;
    typedef unsigned int    KeyType;

protected:
    GraphType *     probability_;   /**< Graph for store probability */
    WeightType *    solution_;      /**< Array for store solution */

    std::map<std::tuple<KeyType, KeyType, SizeType>, double> cache_; /**< 3-dimension tree cache */

    /** Calculate the probability

        \param[in]  start       Starting point
        \param[in]  count       Clicking count
        \param[in]  weight      Weight for PageRank
    */
    void
    CalcProbability(const KeyType & start, const SizeType & count, const KeyType & key = start, const SizeType & step = 1, const WeightType & weight = 1.0)
    {
        if(step >  count) return; 
        if(step == count)
        {
            solution_[key] += weight;
        }
        else
        {
            for(KeyType i = 0; i < probability_->CountOfVertices(); ++i)
            {
                /** TODO: Implement cache */
                if(probability_->IsEdgeExist(key, i))
                {
                    if(step < cache_.size() && cache_.at(step).IsEdgeExist(start, i))
                        solution_[key] += cache_.at(step).GetEdgeWeight(start, i);
                    else
                    {
                        if(step > cache_.size())
                            cache_.
                        CalcProbability(start, count - 1, i, step + 1, probability_->GetEdgeWeight(key, i) * weight);
                    }
                }
            }
        }
    }

public:
    /** Constructor */
    PageRank(GraphType * graph_probability)
    : probability_(graph_probability)
    , solution_(new WeightType[probability_->CountOfVertices()])
    , start_(0)
    , count_(0)
    , cached_(false)
    { }

    /** Destructor */
    ~PageRank(void)
    { delete[] solution_; }

    /** Get the probability of each vertices

        \return     Size of array
        \param[out] out_array   Array to store the probabilities
        \param[in]  start       Starting point
        \param[in]  count       Clicking count
    */
    SizeType
    GetProbability(WeightArrayType & out_array, const KeyType & start, const SizeType & count)
    {
        for(KeyType key = 0; key < probability_->CountOfVertices(); ++key)
            solution_[key] = 0.0;

        CalcProbability(start, count);

        out_array.clear();

        for(KeyType key = 0; key < probability_->CountOfVertices(); ++key)
            out_array.push_back(solution_[key]);

        return out_array.size();
    }
};

} /** ns: algorithm */

#endif /** ! ALGORITHM_PAGERANK_HPP_ */
