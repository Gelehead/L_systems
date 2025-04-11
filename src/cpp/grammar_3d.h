#include "grammar.h"
#include "GrammarElement.h"

class grammar_3D : grammar {
    public :
        // non terminal tiles
        std::vector<tile> nt_tiles;
        
        // terminal tiles 
        std::vector<tile> t_tiles;

        // starting tiles 
        std::vector<tile> s_tiles;

        // rules
        std::map<tile, std::vector<std::vector<tile>>> rules;

        grammar_3D(
            const std::vector<tile> nt,
            const std::vector<tile> t,
            const std::vector<tile> s,
            std::map<tile, std::vector<std::vector<tile>>> r
        ) : nt_tiles(nt), t_tiles(t), s_tiles(s), rules(r) {}

        static grammar_3D read_grammar(std::string filename){
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
                    mapper.at(leftSymbol->getChar())->addToNext(next);
                    r[*leftSymbol].push_back(next);
    
                } else {
                    std::cerr << "Warning: Ignoring malformed rule: " << str << std::endl;
                }
            }
            return grammar_3D(m, t, s, r);
        }
};