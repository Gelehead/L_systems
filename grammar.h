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
        symbol s;

        // rules
        std::map<symbol, std::vector<symbol>> r;

        grammar(
            const std::vector<symbol> non_terminal, 
            const std::vector<symbol> terminal, 
            const symbol start,
            const std::vector<std::string> rules
        ) : m(non_terminal), t(terminal), s(start) {}

        // executes n times the generation rules starting from string str
        // @returns symbol vector of the nth generation
        std::vector<symbol> generate(int n, std::vector<symbol> str){
            if (n == 0) return str;

            std::vector<symbol> result;
            for (symbol s : m){
                result.push_back(!s);
            }
            return generate(n-1, result);
        }

        static grammar read_grammar(std::string filename) {
            std::ifstream file(filename);
            if (!file.is_open()) {
                throw std::runtime_error("Could not open file: " + filename);
            }
            
            std::string str;
            std::vector<symbol> m, t;
            symbol s;
            std::vector<std::string> r;
        
            // Read non-terminal symbols
            std::getline(file, str);
            std::istringstream iss_m(str);
            std::string token;
            while (iss_m >> token) {
                if (!token.empty()) {
                    m.push_back(symbol(token[0]));
                }
            }

            std::cout << m.at(0) << std::endl;
            

            // Read terminal symbols
            std::getline(file, str);
            std::istringstream iss_t(str);
            while (iss_t >> token) {
                if (!token.empty()) {
                    t.push_back(symbol(token[0]));
                }
            }
        
            // Read start symbol
            std::getline(file, str);
            if (!str.empty()) {
                s = symbol(str[0]);
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
                    std::string left = match[1].str();
                    std::string right = match[2].str();

                    // assign follow up symbols in rules
                    
                } else {
                    std::cerr << "Warning: Ignoring malformed rule: " << str << std::endl;
                }
            }
        
            return grammar(m, t, s, r);
        }

    friend std::ostream& operator<<(std::ostream& os, const grammar& gram);

};

// overload of << operator to have a reasonable way to track progress
std::ostream operator << (std::ostream& os, grammar& gram) { 
    os << std::string("non terminal symbols -> ") << gram.m << std::endl;
    os << std::string("terminal symbols -> ") << gram.t << std::endl;
    os << std::string("Start symbol -> ") << gram.s.getChar() << std::endl;

    for ( size_t i = 0 ; i < gram.m.size() ; i++ ) { 
        os << gram.m.at(i);
    }
}