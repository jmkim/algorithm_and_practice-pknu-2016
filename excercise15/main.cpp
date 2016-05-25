/**
 *
 *  PageRank
 *  Readme: https://github.com/kdzlvaids/algorithm_and_practice-pknu-2016/blob/master/excercise15/README.pdf
 *
 *  https://github.com/kdzlvaids/algorithm_and_practice-pknu-2016
 *
 */

/** Includes */
#include <iostream>
#include <string>
#include <cctype>   /** std::isspace definition */
#include "include/adjacency_matrix.hpp"
#include "include/pagerank.hpp"
#include "../excercise14/include/filereader.hpp"

/** Flags */
#define FLAG_DO_PRINT_INFO

/** Type definitions */
typedef char            PrCharType;
typedef std::string     PrStringType;
typedef size_t          PrSizeType;

typedef unsigned int    PrKeyType;
typedef PrStringType    PrValueType;
typedef unsigned int    PrWeightType;
typedef double          PrProbabilityType;

int
main(const int argc, const char * argv[])
{
    algorithm::FileReader<PrStringType, std::deque<PrStringType> > fstream; /**< File stream */

    {
        /** Open a file and associate it to file stream */

        if(argc < 2) /** Path of the file not provided */
        {
            std::cerr << "Usage: " << argv[0] << " [path of resource file]" << std::endl;
            return 2;
        }

        fstream.Open(argv[1]); /** Open the file */

        if(fstream.IsOpen() == false) /** File is not exists */
        {
            std::cerr << "Error: File '" << argv[1] << "' not found." << std::endl;
            return 1;
        }
    }

    {
        /** Print the flags (which is applied in compile time) */

        std::cout   << "Enabled flags: "
#ifdef              FLAG_DO_PRINT_INFO
                    << "DO_PRINT_INFO "
#endif
                    << std::endl;
    }


    PrSizeType count_of_vertices;   /**< Count of vertices */
    PrSizeType count_of_edges;      /**< Count of edges */
    
    {
        /** Read line which defines count of vertices and edges */

        PrStringType line;

        while(true)
        {
            if(fstream.ReadLine(line) <= 0 || line.at(0) == '#' || std::isspace(line.at(0)) == true)
                continue;
            else
            {
                std::deque<PrStringType> tokens;
                fstream.DivideByDelimiter(tokens, line, " ");

                count_of_vertices   = stoi(tokens.at(0));
                count_of_edges      = stoi(tokens.at(1));
                break;
            }
        }

#ifdef FLAG_DO_PRINT_INFO
        std::cout << "Count of vertices defined in file: "  << count_of_vertices    << std::endl;
        std::cout << "Count of edges defined in file: "     << count_of_edges       << std::endl;
#endif /** ! FLAG_DO_PRINT_INFO */
    }


    algorithm::AdjacencyMatrix<PrValueType, PrWeightType> graph(count_of_vertices, 0); /**< Graph */

    {
        /** Add edges to graph */

        PrStringType line;

        for(PrKeyType i = 0; i < count_of_edges; ++i)
        {
            if(fstream.ReadLine(line) <= 0 || line.at(0) == '#' || std::isspace(line.at(0)) == true)
            {
                --i;
                continue;
            }
            else
            {
                std::deque<PrStringType> tokens;
                fstream.DivideByDelimiter(tokens, line, " ");

                PrKeyType key_src  = stoi(tokens.at(0));
                PrKeyType key_dest = stoi(tokens.at(1));

                if(graph.IsEdgeExist(key_src, key_dest))
                    graph.SetEdgeWeight(key_src, key_dest, graph.GetEdgeWeight(key_src, key_dest) + 1);
                else
                    graph.SetEdgeWeight(key_src, key_dest, 1);
            }
        }

#ifdef FLAG_DO_PRINT_INFO
        std::cout << "Count of vertices: " << graph.CountOfVertices() << std::endl;


        /** Print the count of edges (except duplicates) */

        PrSizeType num_edges_strict = 0;

        for(PrKeyType vk = 0; vk < graph.CountOfVertices(); ++vk)
            num_edges_strict += graph.CountOfEdges(vk);

        std::cout << "Count of edges (except duplicates): " << num_edges_strict << std::endl;


        /** Print the count of edges */

        PrSizeType num_edges = 0;
        for(PrKeyType s = 0; s < graph.CountOfVertices(); ++s)
        {
            for(PrKeyType d = 0; d < graph.CountOfVertices(); ++d)
                if(graph.IsEdgeExist(s, d))
                    num_edges += graph.GetEdgeWeight(s, d);
        }

        std::cout << "Count of edges: " << num_edges << std::endl;
#endif /** ! FLAG_DO_PRINT_INFO */
    }


    PrKeyType   starting_point; /**< Starting point */
    PrSizeType  clicking_count; /**< Clicking count */

    {
        /** Read line which defines start point and click count */

        PrStringType line;

        while(true)
        {
            if(fstream.ReadLine(line) <= 0 || line.at(0) == '#' || std::isspace(line.at(0)) == true)
                continue;
            else
            {
                std::deque<PrStringType> tokens;
                fstream.DivideByDelimiter(tokens, line, " ");

                starting_point  = stoi(tokens.at(0));
                clicking_count  = stoi(tokens.at(1));
                break;
            }
        }

#ifdef FLAG_DO_PRINT_INFO
        std::cout << "Starting point: " << starting_point << std::endl;
        std::cout << "Clicking count: " << clicking_count << std::endl;
#endif /** ! FLAG_DO_PRINT_INFO */
    }


    algorithm::AdjacencyMatrix<PrValueType, PrProbabilityType> probability(count_of_vertices, 0.0); /**< Graph for store probability */

    {
        /** Make an array to store maximum weight of each vertices, for calculating the probability */

        PrWeightType max_weight[count_of_vertices];

        for(PrKeyType s = 0; s < graph.CountOfVertices(); ++s)
        {
            max_weight[s] = 0.0; /** Initialise */

            for(PrKeyType d = 0; d < graph.CountOfVertices(); ++d)
            {
                if(graph.IsEdgeExist(s, d))
                    max_weight[s] += graph.GetEdgeWeight(s, d);
            }
        }


        /** Make the probability matrix */

        for(PrKeyType s = 0; s < graph.CountOfVertices(); ++s)
        {
            for(PrKeyType d = 0; d < graph.CountOfVertices(); ++d)
            {
                if(graph.IsEdgeExist(s, d))
                    probability.SetEdgeWeight(s, d, (PrProbabilityType)graph.GetEdgeWeight(s, d) / max_weight[s]);
            }
        }


#ifdef FLAG_DO_PRINT_INFO
        /** Print the probability matrix */

        printf("       ");
        for(PrSizeType i = 0; i < graph.CountOfVertices(); ++i)
            printf("%6d ", i);
        printf("\n");

        for(PrKeyType s = 0; s < graph.CountOfVertices(); ++s)
        {
            printf("%6d ", s);
            for(PrKeyType d = 0; d < graph.CountOfVertices(); ++d)
            {
                if(graph.IsEdgeExist(s, d))
                    printf(" %1.3lf ", probability.GetEdgeWeight(s, d));
                else
                    printf("     . ");
            }
            printf("\n");
        }
#endif /** ! FLAG_DO_PRINT_INFO */
    }


    algorithm::PageRank<algorithm::AdjacencyMatrix<PrValueType, PrProbabilityType> > pr(&probability); /**< PageRank class */
    std::vector<PrProbabilityType> pr_result; /**< Store the probabilies of each vertices */

    {
        /** Calc the probability using PageRank algorithm */

        pr.GetProbability(pr_result, starting_point, clicking_count);


        /** Print the probabilities */

        for(auto & p : pr_result)
            printf("%lf\n", p);
    }

    return 0;
}
