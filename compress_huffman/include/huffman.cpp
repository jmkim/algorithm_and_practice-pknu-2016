#include <iostream>
#include <fstream>
#include <map>
#include "huffman.hpp"

using namespace algorithm;

void
Huffman
::CollectRuns(std::ifstream & f)
{
    char        raw;                /**<   signed char (std::ifstream::read() need signed char ptr) */
    SymbolType  symbol;             /**< unsigned char (ascii range is 0 to 255) */
    SymbolType  next_symbol;
    SizeType    run_len = 1;

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
                /** Insert pair into runs_;
                    key:    pair(symbol, run_len)
                    value:  appearance frequency of key
                */
                MetaSymbolType meta_symbol = std::make_pair(symbol, run_len);

                if(runs_.find(meta_symbol) == runs_.end())
                    runs_.insert(std::make_pair(meta_symbol, 1));   /** First appreance; freq is 1 */
                else
                    ++runs_.at(meta_symbol);                        /** Add freq */

                run_len = 1;
            }

            symbol = next_symbol;
        }

        /** Process the remaining symbol */
        MetaSymbolType meta_symbol = std::make_pair(symbol, run_len);

        if(runs_.find(meta_symbol) == runs_.end())
            runs_.insert(std::make_pair(meta_symbol, 1));
        else
            ++runs_.at(meta_symbol);
    }
}

void
Huffman
::PrintAllRuns(FILE * f)
{
    fprintf(f, "SYM LENG FREQ\n");  /** Header of data */

    for(auto run : runs_)
        fprintf(f, " %02x %4d %d\n", run.first.first, run.first.second, run.second);
}
