#include "GrammarCS.h"

namespace grammar
{
    std::vector<Constituent *> GrammarCS::generate(int gen, std::vector<Constituent *> base, Seed seed)
    {
        // generating logic 
        return {};
    }

    GrammarCS* GrammarCS::readGrammar(std::string& filePath)
    {
        // every created parameter will be accessible once the CS grammar object will be created

        bool grammarType;
        
        int n_terminal;
        std::vector<int> size_terminal;

        int n_nonTerminal;
        std::vector<int> size_nonTerminal;

        std::vector<int> size_start;



        // parsing logic for grammar binary file
    }
} // namespace grammar


