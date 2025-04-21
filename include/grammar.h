#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "GrammarElement.h"

#include <string>
#include <vector>
#include <map>

// Forward declaration for the friend operator
class grammar;
std::ostream& operator<<(std::ostream& os, const grammar& gram);

enum GrammarClass {
    ABSTRACT,
    GRAMMAR_1D,
    GRAMMAR_3D
};

class GrammarUnified {
public:
    // non terminal symbols
    std::vector<GrammarElement*> nt;

    // terminal symbols 
    std::vector<GrammarElement*> t;

    // start symbols
    std::vector<GrammarElement*> s;

    GrammarClass gClass = ABSTRACT;

    static GrammarUnified* readGrammar(std::string filePath);
    
    virtual bool is1DGenerator() const = 0;

    virtual std::vector<GrammarElement*> generate(int generation, std::vector<GrammarElement*> base) const;
    virtual std::vector<std::vector<GrammarElement*>> generate(int generation, std::vector<std::vector<GrammarElement*>> base) const;

    virtual GrammarClass getGrammarClass() { return gClass; }

protected:
    // "1D" and 2/3D generations 
    virtual std::vector<GrammarElement*> generate1DImp(int generation, std::vector<GrammarElement*> base) const = 0;
    virtual std::vector<std::vector<GrammarElement*>> generate2pDImp(int generation, std::vector<std::vector<GrammarElement*>> base) const = 0;
};

class grammar : public GrammarUnified {
public:
    // non terminal symbols
    std::vector<GrammarElement*> m;

    // terminal symbols
    std::vector<GrammarElement*> t;

    // start symbol
    std::vector<GrammarElement*> s;

    GrammarClass gClass = GRAMMAR_1D;

    // rules - using pointers to GrammarElement for map keys to avoid object slicing
    std::map<GrammarElement*, std::vector<std::vector<GrammarElement*>>> r;

    grammar(
        const std::vector<GrammarElement*> non_terminal, 
        const std::vector<GrammarElement*> terminal, 
        const std::vector<GrammarElement*> start,
        std::map<GrammarElement*, std::vector<std::vector<GrammarElement*>>> rules
    );

    // Default constructor
    grammar();

    bool is1DGenerator() const override;

    // @param generation vector of grammar elements 
    // @return string corresponding to every character concatenated  
    static std::string vec2string(std::vector<GrammarElement*> generation);

    static grammar* read_grammar(std::string filename);

    friend std::ostream& operator<<(std::ostream& os, const grammar& gram);

protected:
    // executes n times the generation rules starting from string str
    // @returns grammar element vector of the generation^th generation
    std::vector<GrammarElement*> generate1DImp(int generation, std::vector<GrammarElement*> base) const override;

    // never called because canGenerate2D returns false
    std::vector<std::vector<GrammarElement*>> generate2pDImp(int generation, std::vector<std::vector<GrammarElement*>> base) const override;
};

class Grammar3D : public GrammarUnified {
    // Implementation to be defined
public:
    bool is1DGenerator() const override { return false; }

protected:
    std::vector<GrammarElement*> generate1DImp(int generation, std::vector<GrammarElement*> base) const override {
        throw std::runtime_error("Not implemented");
    }
    
    std::vector<std::vector<GrammarElement*>> generate2pDImp(int generation, std::vector<std::vector<GrammarElement*>> base) const override {
        throw std::runtime_error("Not implemented");
    }
};

#endif // GRAMMAR_H