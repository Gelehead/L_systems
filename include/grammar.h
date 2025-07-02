#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "Consistuent.h"

#include <string>
#include <vector>
#include <map>

// Forward declaration for the friend operator
class grammar;
std::ostream& operator<<(std::ostream& os, const grammar& gram);

class GrammarUnified;
std::ostream& operator<<(std::ostream& os, const GrammarUnified& g);
std::ostream& operator<<(std::ostream& os, std::vector<Consistuent> v);

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
    std::vector<Consistuent*> m;

    // terminal symbols 
    std::vector<Consistuent*> t;

    // start symbols
    std::vector<Consistuent*> s;

    GrammarUnified(
        const std::vector<Consistuent*> non_terminal, 
        const std::vector<Consistuent*> terminal, 
        const std::vector<Consistuent*> start
    );

    GrammarUnified();

    GrammarClass gClass = ABSTRACT;

    static GrammarUnified* read_grammar(std::string filePath);
    
    virtual bool is1DGenerator() const = 0;

    virtual std::vector<Consistuent*> generate(int generation, std::vector<Consistuent*> base) const;
    virtual std::vector<std::vector<Consistuent*>> generate(int generation, std::vector<std::vector<Consistuent*>> base) const;

    virtual GrammarClass getGrammarClass() { return gClass; }

protected:
    // "1D" and 2/3D generations 
    virtual std::vector<Consistuent*> generate1DImp(int generation, std::vector<Consistuent*> base) const = 0;
    virtual std::vector<std::vector<Consistuent*>> generate2pDImp(int generation, std::vector<std::vector<Consistuent*>> base) const = 0;
};

class grammar : public GrammarUnified {
public:
    // m, t, s implicitely present thanks to inheritance from GrammarUnified

    // rules - using pointers to Consistuent for map keys to avoid object slicing
    std::map<Consistuent*, std::vector<std::vector<Consistuent*>>> r;

    grammar(
        const std::vector<Consistuent*> non_terminal, 
        const std::vector<Consistuent*> terminal, 
        const std::vector<Consistuent*> start,
        std::map<Consistuent*, std::vector<std::vector<Consistuent*>>> rules
    );

    // Default constructor
    grammar();

    bool is1DGenerator() const override;

    // @param generation vector of grammar elements 
    // @return string corresponding to every character concatenated  
    static std::string vec2string(std::vector<Consistuent*> generation);

    static grammar* read_grammar(std::string filename, int passLines = 0);

    friend std::ostream& operator<<(std::ostream& os, const grammar& gram);

protected:
    // executes n times the generation rules starting from string str
    // @returns grammar element vector of the generation^th generation
    std::vector<Consistuent*> generate1DImp(int generation, std::vector<Consistuent*> base) const override;

    // never called because canGenerate2D returns false
    std::vector<std::vector<Consistuent*>> generate2pDImp(int generation, std::vector<std::vector<Consistuent*>> base) const override;
};
class CSgrammar : public GrammarUnified {
public:
    std::map<std::vector<Consistuent*>, std::vector<std::vector<Consistuent*>>> r;

    CSgrammar(
        const std::vector<Consistuent*> non_terminal, 
        const std::vector<Consistuent*> terminal, 
        const std::vector<Consistuent*> start,
        std::map<std::vector<Consistuent*>, std::vector<std::vector<Consistuent*>>> rules
    );

    CSgrammar();

    static CSgrammar* read_grammar(std::string filePath, int skipLines = 0);

    // Add these missing virtual function overrides:
    bool is1DGenerator() const override;

protected:
    std::vector<Consistuent*> generate1DImp(int generation, std::vector<Consistuent*> base) const override;
    std::vector<std::vector<Consistuent*>> generate2pDImp(int generation, std::vector<std::vector<Consistuent*>> base) const override;
};

class Grammar3D : public GrammarUnified {
    // Implementation to be defined
public:
    bool is1DGenerator() const override { return false; }

protected:
    std::vector<Consistuent*> generate1DImp(int generation, std::vector<Consistuent*> base) const override {
        throw std::runtime_error("Not implemented");
    }
    
    std::vector<std::vector<Consistuent*>> generate2pDImp(int generation, std::vector<std::vector<Consistuent*>> base) const override {
        throw std::runtime_error("Not implemented");
    }
};

#endif // GRAMMAR_H