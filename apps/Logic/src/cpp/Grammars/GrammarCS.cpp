#include "GrammarCS.h"
#include <fstream>
#include "Chunk.h"

namespace grammar
{
    template <typename T>
    T readBin(std::istream& is)
    {
        T value;
        is.read(reinterpret_cast<char*>(&value), sizeof(T));
        return value;
    }

    GrammarCS* GrammarCS::readGrammar(std::string& filePath)
    {
        std::ifstream in(filePath, std::ios::binary);
        if ( !in )
        {
            std::cerr << "Error opening file for reading" << std::endl;
            return ;
        }

        // HEADER
        bool isCSGrammar = readBin<bool>(in);
        if ( !isCSGrammar ) 
        {
            std::cerr << "Error : CS readGrammar called on a non CS grammar bin file" << std::endl;
        }

        int n_terminal = readBin<int>(in);
        int size_terminal = readBin<int>(in);

        int n_nonTerminal = readBin<int>(in);
        int size_nonTerminal = readBin<int>(in);

        std::vector<int> size_start;
        for ( int i = 0 ; i < 3 ; ++i )
        {
            size_start.push_back(readBin<int>(in));
        }

        int n_rules = readBin<int>(in);

        std::vector<int> context_size;
        for ( int i = 0 ; i < 3 ; ++i )
        {
            size_start.push_back(readBin<int>(in));
        }


        // GRAMMAR PARSING
        // for every terminal chunk
        std::vector<Chunk> nt;
        for ( int i = 0; i < n_terminal ; ++i )
        {
            // for every block coordinate in context size
            for ( int x = 0 ; x < context_size.at(0) ; ++x )
            {
                for ( int y = 0 ; y < context_size.at(1) ; ++y )
                {
                    for ( int z = 0 ; z < context_size.at(2) ; ++z )
                    {
                        // read block hash (refer to sm like )



                    }
                }
            }

            // create chunk constituent
            Chunk chunk;
            nt.push_back(chunk);
        }
        
    }

    std::vector<Constituent *> GrammarCS::generate(int gen, std::vector<Constituent *> base, Seed seed)
    {
        // generating logic 
        return {};
    }

} // namespace grammar


