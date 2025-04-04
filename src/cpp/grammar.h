#include "symbol.h"

#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <iterator>
#include <map>
class grammar {
    public:
        // non terminal symbols
        std::vector<symbol*> m;

        // terminal symbols
        std::vector<symbol*> t;

        // start symbol
        // TODO: transform into symbol VECTOR and handle it properly 
        std::vector<symbol*> s;

        // rules
        std::map<symbol, std::vector<std::vector<symbol*>>> r;

        grammar(
            const std::vector<symbol*> non_terminal, 
            const std::vector<symbol*> terminal, 
            const std::vector<symbol*> start,
            std::map<symbol, std::vector<std::vector<symbol*>>> rules
        ) : m(non_terminal), t(terminal), s(start), r(rules) {}

        // @param generation vector of symbols 
        // @return string corresponding to every character concatenated  
        static std::string vec2string(std::vector<symbol*> generation ) {
            std::string out = "";
            for ( symbol* s : generation ) {
                out += s->getChar();
            }
            return out;
        }

        // executes n times the generation rules starting from string str
        // @returns symbol vector of the generation^th generation
        std::vector<symbol*> generate(int generation, std::vector<symbol*> base){
            if ( generation <= 0 ) { return base; }

            std::vector<symbol*> next_gen;
            for ( symbol* sym : base ) {
                if ( sym->isTerminal() ){
                    next_gen.push_back(sym);
                } else {
                    // select randomly the next generation from the rules
                    std::vector<symbol*> generated_vec = !*sym;
                    for (symbol* generated_sym : generated_vec) {
                        next_gen.push_back(generated_sym);
                    }
                }
            }
            return generate(generation-1, next_gen);
        }

        static grammar read_grammar(std::string filename) {
            std::ifstream file(filename);
            if (!file.is_open()) {
                throw std::runtime_error("Could not open file: " + filename);
            }
            
            std::string str;
            std::vector<symbol*> m, s, t;
            std::map<symbol, std::vector<std::vector<symbol*>>> r;

            // check grammar_h.md for explanation
            m.reserve(100);
            t.reserve(100);
            s.reserve(100);

            // map from char to symbol index in corresponding vector
            std::map<char, symbol*> mapper;
            
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
                    symbol* leftSymbol = mapper.at(left[0]);
                    
                    // Process right side of the rule
                    std::vector<symbol*> next;
                    for (char c : right) {
                        if (mapper.find(c) != mapper.end()) {
                            next.push_back(mapper.at(c)); 
                        } else {
                            std::cerr << "Symbol in rules not found amongst declared symbols: " << c << std::endl;
                        }
                    }

                    // Add the rule
                    if (r.find(*leftSymbol) == r.end()) {
                        r[*leftSymbol] = std::vector<std::vector<symbol*>>();
                    }
                    mapper.at(leftSymbol->getChar())->add_to_next(next);
                    r[*leftSymbol].push_back(next);
    
                } else {
                    std::cerr << "Warning: Ignoring malformed rule: " << str << std::endl;
                }
            }
            return grammar(m, t, s, r);
        }

    friend std::ostream& operator<<(std::ostream& os, grammar& gram);

};

// overload of << operator to have a reasonable way to track progress
std::ostream& operator << (std::ostream& os, grammar& gram) { 
    os << std::string("non terminal symbols -> ") << gram.m << std::endl;
    os << std::string("terminal symbols -> ") << gram.t << std::endl;
    os << std::string("Start symbols -> ") << gram.s << std::endl;

    // for every symbol, print it and iterate over its vector symbols
    // ?? smh iterates from the end
    for ( const auto& pair : gram.r ){
        symbol key = pair.first;
        std::cout << key.getChar() << std::endl;
        for ( std::vector<symbol*> next : pair.second ){
            std::cout << next << std::endl;
        }
    }

    return os;
}