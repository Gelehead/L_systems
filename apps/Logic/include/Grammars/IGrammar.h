#ifndef IGRAMMAR_H
#define IGRAMMAR_H

#include "Constituent.h"
#include "Seed.h"

#include <string>
#include <vector>
#include <map>

namespace grammar
{
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

    protected: 
        IGrammar() = default;
        ~IGrammar() = default;
        IGrammar(
            std::vector<Constituent *> nonTerminal,
            std::vector<Constituent *> terminal,
            std::vector<Constituent *> start,
            std::map<std::vector<Constituent *>, std::vector<Constituent *>> rules,
            Seed seed
        )
        : _nonTerminal(nonTerminal)
        , _terminal(terminal)
        , _start(start)
        , _rules(rules)
        , _seed(seed)
        {}
    };
}

#endif // IGRAMMAR_H