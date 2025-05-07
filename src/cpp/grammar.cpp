#include "grammar.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

// GrammarUnified implementations
GrammarUnified* GrammarUnified::readGrammar(std::string filePath) {
    // TODO:
    // checks the file format with the first line
    std::string dimension, type;
    int noise_steps, generation_steps;
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filePath);
    }
    file >> dimension >> type >> generation_steps >> noise_steps;
    
    // Implementation needed
    return nullptr;
}

// checks if grammar is 1D L_system
std::vector<Consistuent*> GrammarUnified::generate(int generation, std::vector<Consistuent*> base) const {
    if (is1DGenerator()) {
        return generate1DImp(generation, base);
    }
    else {
        throw std::runtime_error("This grammar only supports 2D generation");
    }
}

std::vector<std::vector<Consistuent*>> GrammarUnified::generate(int generation, std::vector<std::vector<Consistuent*>> base) const {
    if (!is1DGenerator()) {
        throw std::runtime_error("This grammar does not support 2D generation");
    }
    return generate2pDImp(generation, base);
}

// grammar implementations
grammar::grammar(
    const std::vector<Consistuent*> non_terminal, 
    const std::vector<Consistuent*> terminal, 
    const std::vector<Consistuent*> start,
    std::map<Consistuent*, std::vector<std::vector<Consistuent*>>> rules
) : m(non_terminal), t(terminal), s(start), r(rules) {}

grammar::grammar() : m(), t(), s(), r() {}

bool grammar::is1DGenerator() const {
    return true;
}

std::string grammar::vec2string(std::vector<Consistuent*> generation) {
    std::string out = "";
    for (Consistuent* s : generation) {
        out += s->getChar();
    }
    return out;
}

grammar* grammar::read_grammar(std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    
    std::string str;
    std::vector<Consistuent*> m, s, t;
    std::map<Consistuent*, std::vector<std::vector<Consistuent*>>> r;

    // Reserve space for elements
    m.reserve(100);
    t.reserve(100);
    s.reserve(100);

    // map from char to Consistuent pointer
    std::map<char, Consistuent*> mapper;
    
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
            Consistuent* leftSymbol = mapper.at(left[0]);
            
            // Process right side of the rule
            std::vector<Consistuent*> next;
            for (char c : right) {
                if (mapper.find(c) != mapper.end()) {
                    next.push_back(mapper.at(c)); 
                } else {
                    std::cerr << "Symbol in rules not found amongst declared symbols: " << c << std::endl;
                }
            }

            // Add the rule
            if (r.find(leftSymbol) == r.end()) {
                r[leftSymbol] = std::vector<std::vector<Consistuent*>>();
            }
            leftSymbol->addToNext(next);
            r[leftSymbol].push_back(next);
        } else {
            std::cerr << "Warning: Ignoring malformed rule: " << str << std::endl;
        }
    }
    
    // Create a new grammar object on the heap and return pointer to it
    return new grammar(m, t, s, r);
}

std::vector<Consistuent*> grammar::generate1DImp(int generation, std::vector<Consistuent*> base) const {
    if (generation <= 0) { return base; }

    std::vector<Consistuent*> next_gen;
    for (Consistuent* sym : base) {
        if (sym->isTerminal()) {
            next_gen.push_back(sym);
        } else {
            // select randomly the next generation from the rules
            std::vector<Consistuent*> generated_vec = sym->selectRandomNext();
            for (Consistuent* generated_sym : generated_vec) {
                next_gen.push_back(generated_sym);
            }
        }
    }
    return generate(generation-1, next_gen);
}

std::vector<std::vector<Consistuent*>> grammar::generate2pDImp(int generation, std::vector<std::vector<Consistuent*>> base) const {
    throw std::runtime_error("Not implemented");
}

// Implementation of the stream operator
std::ostream& operator<<(std::ostream& os, const grammar& gram) { 
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
        for (const std::vector<Consistuent*>& next : pair.second) {
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