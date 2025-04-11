#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "GrammarElement.h"

#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <iterator>
#include <map>

class GrammarUnified {
    public :
    // non terminal symbols
    std::vector<GrammarElement*> nt;

    // terminal symbols 
    std::vector<GrammarElement*> t;

    // start symbols
    std::vector<GrammarElement*> s;

    static GrammarUnified* readGrammar(std::string filePath){
        // TODO:
        // checks the file format with the first line
        // 
    }

    virtual bool canGenerate2D() const = 0;

    virtual std::vector<GrammarElement*> generate(int generation, std::vector<GrammarElement*> base) const {
        if (canGenerate2D()) {
            throw std::runtime_error("This grammar only supports 2D generation");
        }
        return generate1DImp(generation, base);
    }

    virtual std::vector<std::vector<GrammarElement*>> generate(int generation, std::vector<std::vector<GrammarElement*>> base) const {
        if (!canGenerate2D()) {
            throw std::runtime_error("This grammar does not support 2D generation");
        }
        return generate2pDImp(generation, base);
    }

    protected :
        // "1D" and 2/3D generations 
        virtual std::vector<GrammarElement*> generate1DImp(int generation, std::vector<GrammarElement*> base) const = 0;
        virtual std::vector<std::vector<GrammarElement*>> generate2pDImp(int generation, std::vector<std::vector<GrammarElement*>> base)const = 0;
};

class grammar : public GrammarUnified {
    public:
        // non terminal symbols
        std::vector<GrammarElement*> m;

        // terminal symbols
        std::vector<GrammarElement*> t;

        // start symbol
        std::vector<GrammarElement*> s;

        // rules - using pointers to GrammarElement for map keys to avoid object slicing
        std::map<GrammarElement*, std::vector<std::vector<GrammarElement*>>> r;

        grammar(
            const std::vector<GrammarElement*> non_terminal, 
            const std::vector<GrammarElement*> terminal, 
            const std::vector<GrammarElement*> start,
            std::map<GrammarElement*, std::vector<std::vector<GrammarElement*>>> rules
        ) : m(non_terminal), t(terminal), s(start), r(rules) {}

        // Default constructor
        grammar() : m(), t(), s(), r() {}

        bool canGenerate2D() const override { return true; }

        // @param generation vector of grammar elements 
        // @return string corresponding to every character concatenated  
        static std::string vec2string(std::vector<GrammarElement*> generation) {
            std::string out = "";
            for (GrammarElement* s : generation) {
                out += s->getChar();
            }
            return out;
        }

        static grammar* read_grammar(std::string filename) {
            std::ifstream file(filename);
            if (!file.is_open()) {
                throw std::runtime_error("Could not open file: " + filename);
            }
            
            std::string str;
            std::vector<GrammarElement*> m, s, t;
            std::map<GrammarElement*, std::vector<std::vector<GrammarElement*>>> r;

            // Reserve space for elements
            m.reserve(100);
            t.reserve(100);
            s.reserve(100);

            // map from char to GrammarElement pointer
            std::map<char, GrammarElement*> mapper;
            
            // Read non-terminal symbols
            std::getline(file, str);
            std::istringstream iss_m(str);
            std::string token;
            while (iss_m >> token) {
                if (!token.empty()) {
                    symbol* m_sym = new symbol(token[0]);
                    m.push_back(m_sym);
                    mapper[token[0]] = m_sym;
                }
            }
        
            // Read terminal symbols
            std::getline(file, str);
            std::istringstream iss_t(str);
            while (iss_t >> token) {
                if (!token.empty()) {
                    symbol* t_sym = new symbol(token[0]);
                    t.push_back(t_sym);
                    mapper[token[0]] = t_sym;
                }
            }

            // Read start symbol(s)
            std::getline(file, str);
            if (!str.empty()) {
                for (char c : str) {
                    if (mapper.find(c) != mapper.end()) {
                        s.push_back(mapper.at(c));
                    } else {
                        std::cerr << "Symbol in start symbols not found amongst declared symbols: " << c << std::endl;
                    }
                }
            } else {
                throw std::runtime_error("Start symbol line is empty");
            }

            // Read production rules
            std::regex rule_regex(R"((\w)\s*->\s*([\w\+\-\*\/\[\]\{\}\(\)]+))");
            while (std::getline(file, str)) {
                if (str.empty() || str[0] == '#') {  // Skip empty lines and comments
                    continue;
                }

                std::smatch match;
                if (std::regex_match(str, match, rule_regex)) {
                    std::string left = (std::string) match[1].str();
                    std::string right = match[2].str();

                    if (left.empty() || mapper.find(left[0]) == mapper.end()) {
                        std::cerr << "Left symbol in rule not found amongst declared symbols: " << left << std::endl;
                        continue;
                    }

                    // Get the left symbol from the mapper
                    GrammarElement* leftSymbol = mapper.at(left[0]);
                    
                    // Process right side of the rule
                    std::vector<GrammarElement*> next;
                    for (char c : right) {
                        if (mapper.find(c) != mapper.end()) {
                            next.push_back(mapper.at(c)); 
                        } else {
                            std::cerr << "Symbol in rules not found amongst declared symbols: " << c << std::endl;
                        }
                    }

                    // Add the rule
                    if (r.find(leftSymbol) == r.end()) {
                        r[leftSymbol] = std::vector<std::vector<GrammarElement*>>();
                    }
                    leftSymbol->addToNext(next);
                    r[leftSymbol].push_back(next);
                } else {
                    std::cerr << "Warning: Ignoring malformed rule: " << str << std::endl;
                }
            }
            return &grammar(m, t, s, r);
        }
    friend std::ostream& operator<<(std::ostream& os, grammar& gram);

    protected :
        // executes n times the generation rules starting from string str
        // @returns grammar element vector of the generation^th generation
        std::vector<GrammarElement*> generate1DImp(int generation, std::vector<GrammarElement*> base) const override{
            if (generation <= 0) { return base; }

            std::vector<GrammarElement*> next_gen;
            for (GrammarElement* sym : base) {
                if (sym->isTerminal()) {
                    next_gen.push_back(sym);
                } else {
                    // select randomly the next generation from the rules
                    std::vector<GrammarElement*> generated_vec = sym->selectRandomNext();
                    for (GrammarElement* generated_sym : generated_vec) {
                        next_gen.push_back(generated_sym);
                    }
                }
            }
            return generate(generation-1, next_gen);
        }

        // never called because canGenerate2D returns false
        std::vector<std::vector<GrammarElement*>> generate2pDImp(int generation, std::vector<std::vector<GrammarElement*>> base) const override {
            throw std::runtime_error("Not implemented");
        }
};

// overload of << operator to have a reasonable way to track progress
std::ostream& operator<<(std::ostream& os, grammar& gram) { 
    os << std::string("non terminal symbols -> ");
    os << '{';
    for (size_t i = 0; i < gram.m.size(); i++) {
        os << gram.m[i]->getChar();
        if (i < gram.m.size() - 1) {
            os << ", ";
        }
    }
    os << '}' << std::endl;
    
    os << std::string("terminal symbols -> ");
    os << '{';
    for (size_t i = 0; i < gram.t.size(); i++) {
        os << gram.t[i]->getChar();
        if (i < gram.t.size() - 1) {
            os << ", ";
        }
    }
    os << '}' << std::endl;
    
    os << std::string("Start symbols -> ");
    os << '{';
    for (size_t i = 0; i < gram.s.size(); i++) {
        os << gram.s[i]->getChar();
        if (i < gram.s.size() - 1) {
            os << ", ";
        }
    }
    os << '}' << std::endl;

    // for every grammar element, print it and iterate over its vector elements
    for (const auto& pair : gram.r) {
        os << pair.first->getChar() << std::endl;
        for (const std::vector<GrammarElement*>& next : pair.second) {
            os << '{';
            for (size_t i = 0; i < next.size(); i++) {
                os << next[i]->getChar();
                if (i < next.size() - 1) {
                    os << ", ";
                }
            }
            os << '}' << std::endl;
        }
    }

    return os;
}

#endif // GRAMMAR_H