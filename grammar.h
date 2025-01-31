#include "symbol.h"

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

        static grammar read_grammar(std::string filename){
            std::ifstream file(filename);
            std::string str;

            std::vector<symbol> m, t;
            symbol s; 
            std::vector<std::string> r;

            auto read_line = [&](std::vector<symbol>& vec){
                // stores the current line (designated by some pointer shit im guessing)
                std::getline(file, str);
                std::istringstream iss(str);
                vec = {std::istream_iterator<symbol>{iss}, {}};
            };

            read_line(m);
            read_line(t);
            std::getline(file, str);
            s = symbol(str[0]);

            std::regex rule_regex(R"((\w+)\s*->\s*(.+))");
            while (std::getline(file, str)) {
                std::smatch match;
                if (std::regex_match(str, match, rule_regex)){
                    std::string right = match[2].str();
                    std::stringstream ss(right);

                    while (std::getline(ss, r, '|')) {
                        r.push_back(r);
                    }
                }
            }

            return grammar(m, t, s, r);
        }

    private:
        // non terminal symbols
        std::vector<symbol> m;

        // terminal symbols
        std::vector<symbol> t;

        // start symbol
        symbol s;
};