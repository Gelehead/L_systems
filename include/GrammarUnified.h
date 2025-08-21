#ifndef GRAMMAR_UNIFIED_H
#define GRAMMAR_UNIFIED_H

#include "Constituent.h"

#include <string>
#include <vector>
#include <map>

// Forward declaration for the friend operator
class GrammarUnified;
std::ostream& operator<<(std::ostream& os, const GrammarUnified& g);
std::ostream& operator<<(std::ostream& os, std::vector<Constituent> v);

class CSgrammar;
std::ostream& operator<<(std::ostream& os, const CSgrammar& g);

// TODO: unfinished
enum GrammarClass {
    ABSTRACT,
    CS,
    CF,
    GRAMMAR_1D,
    GRAMMAR_3D
};

class GrammarUnified {
public:
    // non terminal symbols
    std::vector<Constituent*> m;

    // terminal symbols 
    std::vector<Constituent*> t;

    // start symbols
    std::vector<Constituent*> s;

    GrammarUnified(
        const std::vector<Constituent*> non_terminal, 
        const std::vector<Constituent*> terminal, 
        const std::vector<Constituent*> start
    );

    GrammarUnified();

    GrammarClass gClass = ABSTRACT;

    static GrammarUnified* read_grammar(std::string filePath);
    
    virtual bool is1DGenerator() const = 0;

    virtual std::vector<Constituent*> generate(int generation, std::vector<Constituent*> base) const;
    virtual std::vector<std::vector<Constituent*>> generate(int generation, std::vector<std::vector<Constituent*>> base) const;

    virtual GrammarClass getGrammarClass() { return gClass; }

protected:
    // "1D" and 2/3D generations 
    virtual std::vector<Constituent*> generate1DImp(int generation, std::vector<Constituent*> base) const = 0;
    virtual std::vector<std::vector<Constituent*>> generate2pDImp(int generation, std::vector<std::vector<Constituent*>> base) const = 0;
};

#endif // GRAMMAR_H