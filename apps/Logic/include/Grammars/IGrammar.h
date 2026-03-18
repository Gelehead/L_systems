#ifndef IGRAMMAR_H
#define IGRAMMAR_H

#include "Constituent.h"
#include "Seed.h"

#include <string>
#include <vector>
#include <map>

namespace grammar
{
    /*******************************************************************
     * used solely for parsing purposes so far ( readGrammar() calls readGrammarClass() )
     ********************************************************************/
    enum GrammarType
    {
          ABSTRACT
        , CS
        , CF
        , GRAMMAR_1D
        , GRAMMAR_3D
    };

    class IGrammar 
    {
    private:
        // non terminal constituents
        std::vector<Constituent*> _nonTerminal;

        // terminal constituents
        std::vector<Constituent*> _terminal;

        // start constituents
        std::vector<Constituent*> _start;

        // rules (used to link a situation of constituent to another)
        std::map<std::vector<Constituent *>, std::vector<Constituent *>> _rules; 

        Seed _seed;

    public:
        virtual std::vector<Constituent*> generate(int generation, std::vector<Constituent*> base, Seed seed) = 0;

    private: 
        virtual IGrammar* read_grammar(std::string filePath) = 0;
        IGrammar();
    };
}

#endif // IGRAMMAR_H