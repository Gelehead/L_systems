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
        std::vector<Constituent *> generate(int generation, std::vector<Constituent*> base, Seed seed) override;
        GrammarCS()
    };
}


#endif // GRAMMARCS_H