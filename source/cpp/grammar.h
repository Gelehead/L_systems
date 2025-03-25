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
        std::vector<symbol> m;

        // terminal symbols
        std::vector<symbol> t;

        // start symbol
        // TODO: transform into symbol VECTOR and handle it properly 
        std::vector<symbol> s;

        // rules
        std::map<symbol, std::vector<std::vector<symbol>>> r;

        grammar(
            const std::vector<symbol> non_terminal, 
            const std::vector<symbol> terminal, 
            const std::vector<symbol> start,
            std::map<symbol, std::vector<std::vector<symbol>>> rules
        ) : m(non_terminal), t(terminal), s(start), r(rules) {}

        // @param generation vector of symbols 
        // @return string corresponding to every character concatenated  
        static std::string vec2string(std::vector<symbol> generation ) {
            std::string out = "";
            for ( symbol s : generation ) {
                out += s.getChar();
            }
            return out;
        }

        // executes n times the generation rules starting from string str
        // @returns symbol vector of the generation^th generation
        std::vector<symbol> generate(int generation, std::vector<symbol> base){
            if ( generation <= 0 ) { return base; }

            std::vector<symbol> next_gen;
            for ( symbol sym : base ) {
                if ( sym.isTerminal() ){
                    next_gen.push_back(sym);
                } else {
                    // select randomly the next generation from the rules 
                    // Note : still debating whether it s better to use '!sym' or r.at(sym)
                    for ( symbol generated_sym : r.at(sym).at(std::rand() % r.at(sym).size()) ){
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
            std::vector<symbol> m, t;
            std::vector<symbol> s;
            std::map<symbol, std::vector<std::vector<symbol>>> r;

            // map from char to symbol ( helping scalability for huuuge grammars )
            std::map<char, symbol> mapper;
        
            // Read non-terminal symbols
            std::getline(file, str);
            std::istringstream iss_m(str);
            std::string token;
            while (iss_m >> token) {
                if (!token.empty()) {
                    symbol nt_symbol = symbol(token[0]);
                    // add to non terminal symbol vector 
                    m.push_back(nt_symbol);

                    // add to mapper 
                    mapper.insert(std::make_pair(token[0], nt_symbol));
                }
            }

            // Read terminal symbols
            std::getline(file, str);
            std::istringstream iss_t(str);
            while (iss_t >> token) {
                if (!token.empty()) {
                    symbol t_symbol = symbol(token[0]);
                    // add to terminal symbol vector
                    t.push_back(t_symbol);

                    // add to mapper
                    mapper.insert(std::make_pair(token[0], t_symbol));
                }
            }
        
            // Read start symbol(s)
            std::getline(file, str);
            if (!str.empty()) {
                for (char c : str) {
                    symbol s_symbol = symbol(c);
                    mapper.insert(std::make_pair(c, s_symbol));
                    s.push_back(s_symbol);
                }
            } else {
                throw std::runtime_error("Start symbol line is empty");
            }
        
            // Read production rules
            std::regex rule_regex(R"((\w+)\s*->\s*(.*))");
            while (std::getline(file, str)) {
                if (str.empty() || str[0] == '#') {  // Skip empty lines and comments
                    continue;
                }
                
                std::smatch match;
                if (std::regex_match(str, match, rule_regex)) {
                    std::string left = (std::string) match[1].str();
                    std::string right = match[2].str();

                    // add as symbols reference every  
                    std::vector<symbol> next;
                    for (char c : right) { 
                        if ( mapper.find(c) != mapper.end() ){
                            next.push_back(mapper.at(c)); 
                        } else {
                            std::cerr << "Symbol in rules not found amongst declared symbols" << std::endl;
                        }
                    } 

                    // assign follow up symbols in rules
                    symbol leftSymbol = mapper.at(left[0]);
                    if (r.find(leftSymbol) == r.end()) {
                        r[leftSymbol] = std::vector<std::vector<symbol>>();
                        leftSymbol|next;
                    }
                    r[leftSymbol].push_back(next);
                    
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
        for ( std::vector<symbol> next : pair.second ){
            std::cout << next << std::endl;
        }
    }

    return os;
}