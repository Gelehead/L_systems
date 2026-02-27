#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <cmath>

#include "GrammarUnified.h"

class grammar;
std::ostream& operator<<(std::ostream& os, const grammar& gram);
class grammar : public GrammarUnified {
public:
    // m, t, s implicitely present thanks to inheritance from GrammarUnified

    // rules - using pointers to Constituent for map keys to avoid object slicing
    std::map<Constituent*, std::vector<std::vector<Constituent*>>> r;

    grammar(
        const std::vector<Constituent*> non_terminal, 
        const std::vector<Constituent*> terminal, 
        const std::vector<Constituent*> start,
        std::map<Constituent*, std::vector<std::vector<Constituent*>>> rules
    );

    // Default constructor
    grammar();

    bool is1DGenerator() const override;

    // @param generation vector of grammar elements 
    // @return string corresponding to every character concatenated  
    static std::string vec2string(std::vector<Constituent*> generation);

    static grammar* read_grammar(std::string filename, int passLines = 0);

    friend std::ostream& operator<<(std::ostream& os, const grammar& gram);

protected:
    // executes n times the generation rules starting from string str
    // @returns grammar element vector of the generation^th generation
    std::vector<Constituent*> generate1DImp(int generation, std::vector<Constituent*> base) const override;

    // never called because canGenerate2D returns false
    std::vector<std::vector<Constituent*>> generate2pDImp(int generation, std::vector<std::vector<Constituent*>> base) const override;
};

#endif