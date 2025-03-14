#include "symbol.h"

#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <iterator>

class grammar {
    public:
        // non terminal symbols
        std::vector<symbol> m;

        // terminal symbols
        std::vector<symbol> t;

        // start symbol
        symbol s;

        // rules ( only a string representation of them )
        std::vector<std::string> r;

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
                    
                    // Create a rule string in the format "LEFT->RIGHT"
                    std::string rule = left + "->" + right;
                    r.push_back(rule);
                } else {
                    std::cerr << "Warning: Ignoring malformed rule: " << str << std::endl;
                }
            }
        
            return grammar(m, t, s, r);
        }

    private:

};