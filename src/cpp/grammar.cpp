#include "grammar.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

// GrammarUnified implementations

// @param filePath path/to/grammar from called location (usually L_systems\)
// @return nullptr if no match, result from CS::read_grammar if matched CS, result from CF::read_grammar if matched CF
GrammarUnified* GrammarUnified::read_grammar(std::string filePath) {
    std::string type;
    int dimension;
    GrammarClass gramClass;
    
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filePath);
    }
    
    // read variables
    // tf is noise steps 
    file >> dimension >> type;
    if (type == "CS") {
        gramClass = CS;
    } else if (type == "CF") {
        gramClass = CF;
    } else {
        throw std::runtime_error("Unknown grammar type: " + type);
    }

    try {
        switch ( gramClass ) {
            case CS :
                return CSgrammar::read_grammar(filePath, 1);

            case CF :
                if ( dimension == 1 ) { 
                    return grammar::read_grammar(filePath, 1); 
                }
                else { 
                    throw std::logic_error("not implemented"); 
                }

            default:
                break;
        }
    } catch ( const std::exception& e){
        throw std::runtime_error("failed to parse " + type + " from " + filePath + " : " + e.what() );
    }
    
    // if doesnt match any expected pattern, return nullptr
    return nullptr;
}

GrammarUnified::GrammarUnified() : m(), t(), s() {}

GrammarUnified::GrammarUnified(
    const std::vector<Consistuent*> non_terminal, 
    const std::vector<Consistuent*> terminal, 
    const std::vector<Consistuent*> start
) : m(non_terminal), t(terminal), s(start) {}

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

std::ostream& operator<<(std::ostream& os, const GrammarUnified& g) {
    os << "Non terminal symbols : " << std::endl << g.m << std::endl;
    os << "Terminal symbols : " << std::endl << g.t << std::endl;
    os << "Starting symbol : " << std::endl << g.s << std::endl;

    return os;
}

// grammar implementations
grammar::grammar(
    const std::vector<Consistuent*> non_terminal, 
    const std::vector<Consistuent*> terminal, 
    const std::vector<Consistuent*> start,
    std::map<Consistuent*, std::vector<std::vector<Consistuent*>>> rules
) : GrammarUnified(non_terminal, terminal, start), r(rules) {
    gClass = GRAMMAR_1D;
}

grammar::grammar() : GrammarUnified(), r() {}

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

grammar* grammar::read_grammar(std::string filename, int passLines) {
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

    // skip some lines 
    for ( int i = 0; i < passLines ; i++ ){
        std::getline(file, str);
    }
    
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
                std::cerr << "(CF) Left symbol in rule not found amongst declared symbols: " << left << std::endl;
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

// --------------- CS Grammar --------------- 

CSgrammar::CSgrammar(
    const std::vector<Consistuent*> non_terminal, 
    const std::vector<Consistuent*> terminal, 
    const std::vector<Consistuent*> start,
    std::map<std::vector<Consistuent*>, std::vector<std::vector<Consistuent*>>> rules
) : GrammarUnified(non_terminal, terminal, start), r(rules) {
    gClass = CS;
}

CSgrammar::CSgrammar() : GrammarUnified(), r() {}

// First, add the missing virtual function implementations to CSgrammar class
bool CSgrammar::is1DGenerator() const {
    return true; // Assuming CS grammars generate 1D strings
}

// recursively apply rules when recognizing a pattern
// @param base the base consistuent vector
// @param ruleLengths sorted array of all different rule lengths
std::vector<Consistuent*> scan(std::vector<Consistuent*> base, int ruleLengths[]){
    // base case : if consistuent isnt terminal > replace by successor
    // 
}

std::vector<Consistuent*> CSgrammar::generate1DImp(int generation, std::vector<Consistuent*> base) const {
    if (generation <= 0) { 
        return base; 
    }

    std::vector<Consistuent*> next_gen;

    for (int i = 0 ; i < generation ; i++ ){
        bool stable = false;
        while ( !stable ) {
            int a =0;
        }
    }

    return generate1DImp(generation - 1, next_gen);
}

std::vector<std::vector<Consistuent*>> CSgrammar::generate2pDImp(int generation, std::vector<std::vector<Consistuent*>> base) const {
    throw std::runtime_error("2D generation not implemented for CS grammars");
}

// Fixed read_grammar method for CSgrammar
CSgrammar* CSgrammar::read_grammar(std::string filePath, int skipLines) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filePath);
    }
    
    std::string str;
    std::vector<Consistuent*> m, s, t;
    std::map<std::vector<Consistuent*>, std::vector<std::vector<Consistuent*>>> r;

    // Reserve space for elements
    m.reserve(100);
    t.reserve(100);
    s.reserve(100);

    // map from char to Consistuent pointer
    std::map<char, Consistuent*> mapper;

    // skip some lines 
    for (int i = 0; i < skipLines; i++) {
        std::getline(file, str);
    }
    
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
        std::istringstream start_stream(str);
        std::string start_token;
        while (start_stream >> start_token) {
            if (!start_token.empty() && mapper.find(start_token[0]) != mapper.end()) {
                s.push_back(mapper.at(start_token[0]));
            } else if (!start_token.empty()) {
                std::cerr << "Symbol in start symbols not found amongst declared symbols: " << start_token[0] << std::endl;
            }
        }
    } else {
        throw std::runtime_error("Start symbol line is empty");
    }

    // TODO
    // Read production rules - improved regex for context-sensitive rules
    std::regex rule_regex(R"((.+?)\s*->\s*(.+))");
    while (std::getline(file, str)) {
        if (str.empty() || str[0] == '#') {
            continue;
        }

        std::smatch match;
        if (std::regex_match(str, match, rule_regex)) {
            std::string left = match[1].str();
            std::string right = match[2].str();

            std::vector<Consistuent*> leftSide;
            std::vector<Consistuent*> rightSide;

            // Parse left side - handle each character
            bool valid_left = true;
            for (char c : left) {
                if (c != ' ' && c != '\t') { // Skip whitespace
                    if (mapper.find(c) == mapper.end()) {
                        std::cerr << "(CS) Left symbol in rule not found: " << c << " in rule: " << str << std::endl;
                        valid_left = false;
                        break;
                    }
                    leftSide.push_back(mapper.at(c));
                }
            }

            // Parse right side - handle each character
            bool valid_right = true;
            for (char c : right) {
                if (c != ' ' && c != '\t') { // Skip whitespace
                    if (mapper.find(c) == mapper.end()) {
                        std::cerr << "Right symbol in rule not found: " << c << " in rule: " << str << std::endl;
                        valid_right = false;
                        break;
                    }
                    rightSide.push_back(mapper.at(c));
                }
            }

            if (valid_left && valid_right && !leftSide.empty()) {
                // Use the full leftSide as the key for context-sensitive rules
                if (r.find(leftSide) == r.end()) {
                    r[leftSide] = std::vector<std::vector<Consistuent*>>();
                }
                
                // Add to next for each symbol in the left side (for compatibility)
                for (Consistuent* sym : leftSide) {
                    sym->addToNext(rightSide);
                }
                
                r[leftSide].push_back(rightSide);
            }
        } else {
            std::cerr << "Warning: Ignoring malformed rule: " << str << std::endl;
        }
    }
    
    file.close();
    return new CSgrammar(m, t, s, r);
}

// Implementation of the stream operator
std::ostream& operator<<(std::ostream& os, const CSgrammar& gram) { 

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
        os << "for " << pair.first << ":" << std::endl;
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
        os << "----------" << std::endl;
    }

    return os;
}