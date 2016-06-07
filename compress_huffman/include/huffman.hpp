#ifndef ALGORITHM_HUFFMAN_H_
#define ALGORITHM_HUFFMAN_H_ 1

#include <vector>
#include <utility>

namespace algorithm
{

class Huffman
{
public:
    typedef unsigned char   SymbolType;
    typedef size_t          SizeType;

    typedef std::pair<SymbolType, SizeType> MetaSymbolType;

    struct Run
    {
        const   SymbolType          symbol;
        const   SizeType            run_len;
                SizeType            freq;

        Run(const SymbolType & symbol, const SizeType & run_len, const SizeType & freq = 0)
        : symbol    (symbol)
        , run_len   (run_len)
        , freq      (freq)
        { }

        Run(const MetaSymbolType & meta_symbol, const SizeType & freq = 0)
        : symbol    (meta_symbol.first)
        , run_len   (meta_symbol.second)
        , freq      (freq)
        { }

        Run(const Run & run)
        : symbol    (run.symbol)
        , run_len   (run.run_len)
        , freq      (run.freq)
        { }

        inline
        bool
        operator==(const Run & rhs)
        { return symbol == rhs.symbol && run_len == rhs.run_len; }

        inline
        bool
        operator!=(const Run & rhs)
        { return ! (*this == rhs); }

        inline
        Run &
        operator++(void)
        {
            ++freq;
            return *this;
        }

        inline
        Run
        operator++(int)
        {
            Run temp(*this);
            operator++();
            return temp;
        }

        inline
        Run &
        operator--(void)
        {
            --freq;
            return *this;
        }

        inline
        Run
        operator--(int)
        {
            Run temp(*this);
            operator--();
            return temp;
        }

        inline
        Run &
        operator=(Run run)
        {
            std::swap(*this, run);
            return *this;
        }

        inline
        bool
        operator<(const Run & rhs)
        { return (this->freq < rhs.freq); }

        inline
        bool
        operator>(const Run & rhs)
        { return (this->freq > rhs.freq); }

        inline
        bool
        operator<=(const Run & rhs)
        { return ! operator>(rhs); }

        inline
        bool
        operator>=(const Run & rhs)
        { return ! operator<(rhs); }
    };

    typedef std::vector<Run> HeapType;

private:
    HeapType runs_;

public:
    void CollectRuns(std::ifstream &);
    void PrintAllRuns(FILE * = stdout);
    void Heapify(HeapType &);
    void CreateHuffmanTree(void);
};

} /** ns: algorithm */

#endif /** ! ALGORITHM_HUFFMAN_H_ */
