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

    KeyType         start_;         /**< Starting point */
    SizeType        count_;         /**< Clicking count */
    bool            cached_;

    /** Calculate the probability

        \param[in]  start       Starting point
        \param[in]  count       Clicking count
        \param[in]  weight      Weight for PageRank
    */
    void
    CalcProbability(const KeyType & start, const SizeType & count, const WeightType & weight = 1.0)
    {
        if(count == 0)
            solution_[start] += weight;
        else
        {
            for(KeyType key = 0; key < probability_->CountOfVertices(); ++key)
            {
                if(probability_->IsEdgeExist(start, key))
                    CalcProbability(key, count - 1, probability_->GetEdgeWeight(start, key) * weight);
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
        if(cached_ != true || start != start_ || count != count_)
        {
            for(KeyType key = 0; key < probability_->CountOfVertices(); ++key)
                solution_[key] = 0.0;

            CalcProbability(start, count);

            cached_ = true;
        }

        out_array.clear();

        for(KeyType key = 0; key < probability_->CountOfVertices(); ++key)
            out_array.push_back(solution_[key]);

        return out_array.size();
    }
};

} /** ns: algorithm */

#endif /** ! ALGORITHM_PAGERANK_HPP_ */
