#ifndef ALGORITHM_HUFFMAN_H_
#define ALGORITHM_HUFFMAN_H_ 1

#include <map>

namespace algorithm
{

class Huffman
{
public:
    typedef unsigned char   SymbolType;
    typedef size_t          SizeType;

    typedef std::pair<const SymbolType, const SizeType> MetaSymbolType;

private:
    std::map<MetaSymbolType, SizeType> runs_;

public:
    void CollectRuns(std::ifstream &);
    void PrintAllRuns(FILE * = stdout);
};

} /** ns: algorithm */

#endif /** ! ALGORITHM_HUFFMAN_H_ */
