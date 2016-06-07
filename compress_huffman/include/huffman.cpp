#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>
#include "huffman.hpp"

using namespace algorithm;

void
Huffman
::CollectRuns(std::ifstream & f)
{
    typedef     std::map<MetaSymbolType, unsigned int>  CacheType;
    typedef     CacheType::iterator                     CacheIterType;

    char        raw;                /**<   signed char (std::ifstream::read() need signed char ptr) */
    SymbolType  symbol;             /**< unsigned char (ascii range is 0 to 255) */
    SymbolType  next_symbol;
    SizeType    run_len = 1;
    CacheType   cache;              /**< Caching a position of the run in the vector(runs_) */

    if(! f.eof())
    {
        f.read(&raw, sizeof(raw));
        symbol = (SymbolType)raw;   /** Cast signed to unsigned */

        while(! f.eof())
        {
            f.read(&raw, sizeof(raw));
            next_symbol = (SymbolType)raw;

            if(symbol == next_symbol)
                ++run_len;
            else
            {
                /** Insert the pair into runs_;
                    key:    pair(symbol, run_len)
                    value:  appearance frequency of key
                */
                MetaSymbolType  meta_symbol = std::make_pair(symbol, run_len);
                CacheIterType   cache_iter = cache.find(meta_symbol);   /** Get the position from cache */

                if(cache_iter == cache.end())
                {
                    runs_.push_back(Run(meta_symbol, 1));           /** First appreance; freq is 1 */
                    cache.emplace(meta_symbol, runs_.size() - 1);   /** Cache the position */
                }
                else
                    ++runs_.at(cache_iter->second);                 /** Add freq */

                run_len = 1;
            }

            symbol = next_symbol;
        }

        /** Process the remaining symbol */
        MetaSymbolType  meta_symbol = std::make_pair(symbol, run_len);
        CacheIterType   cache_iter = cache.find(meta_symbol);       /** Get the position from cache */
        Run             run(meta_symbol, 1);

        if(cache_iter == cache.end())
        {
            runs_.push_back(Run(meta_symbol, 1));                   /** First appreance; freq is 1 */
            cache.emplace(meta_symbol, runs_.size() - 1);           /** Cache the position */
        }
        else
            ++runs_.at(cache_iter->second);                         /** Add freq */
   }
}

void
Huffman
::PrintAllRuns(FILE * f)
{
    fprintf(f, "SYM LENG FREQ\n");  /** Header of data */

    for(auto run : runs_)
        fprintf(f, " %02x %4d %d\n", run.symbol, run.run_len, run.freq);
}

void
Huffman
::Heapify(HeapType & heap)
{
    for(int i = heap.size() - 1; i > 0; --i)
    {
        for(int j = i; j > 0; j = (j - 1) / 2)
        {
            if( heap.at(i) < heap.at((j - 1) / 2) ) /* Minimum heap */
            {
                std::swap( heap.at(i), heap.at((j - 1) / 2) );
            }
        }
    }
}

void
Huffman
::CreateHuffmanTree(void)
{
    Heapify(runs_);
}
