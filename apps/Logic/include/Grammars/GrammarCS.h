#ifndef GRAMMARCS_H
#define GRAMMARCS_H

#include "IGrammar.h"

namespace grammar
{
    /*******************************************************************
     * suffieciently abstract to encapsulate 1D and 3D 
     ********************************************************************/
    class GrammarCS : public IGrammar
    {
    private:
        std::vector<float> _bounds;

    public:
        std::vector<Constituent *> generate(int generation, std::vector<Constituent*> base, Seed seed) override;
        static std::shared_ptr<GrammarCS>* readGrammar(std::string& filePath);

    private : 
        GrammarCS(
            std::vector<Constituent *> nonTerminal,
            std::vector<Constituent *> terminal,
            std::vector<Constituent *> start,
            std::map<std::vector<Constituent *>, std::vector<Constituent *>> rules,
            Seed seed,
            std::vector<float> bounds
        )
        : IGrammar(nonTerminal, terminal, start, rules, seed)
        , _bounds(bounds)
        {}
    };
} // namespace grammar


#endif // GRAMMARCS_H