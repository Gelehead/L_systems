#include "GrammarCS.h"
#include "Utils.h"


CSgrammar::CSgrammar(
    const std::vector<Constituent*> non_terminal, 
    const std::vector<Constituent*> terminal, 
    const std::vector<Constituent*> start,
    std::map<std::vector<Constituent*>, std::vector<std::vector<Constituent*>>> rules
) : GrammarUnified(non_terminal, terminal, start), r(rules) {
    gClass = CS;
}

CSgrammar::CSgrammar() : GrammarUnified(), r() {}

// --- DerivationNode ---

// number of nonterminals
int CSgrammar::DerivationNode::h_step() {
    int non_terminal_count = 0;
    for ( Constituent* c : this->form ) {
        if ( !c->isTerminal() ) { non_terminal_count++; }
    }
    return non_terminal_count;
}

// adds penalty / bonus based on the string length
// ReLU type shi, 
int CSgrammar::DerivationNode::h_length_penalty(int max_length) {
    int size = form.size();
    if ( size < max_length ) { return pow(size-max_length, 5); }
    if ( size > max_length ) { return (size-max_length) / 4 ; }
    else { return 0; }
}

int scan(
    CSgrammar::DerivationNode dn
){
    // sum of all pattern strings lengths
    const int MAXS = [dn]{ int sum = 0; for (int s : dn.rule_left_size) sum += s; return sum; }();

    // biggest pattern length
    const int MAXC = [dn] { int max = -999; for (int s : dn.rule_left_size) s > max ? max = s : NULL ; return max; }();

    // output function
    int out[MAXS];

    // failure function
    int f[MAXC];

    // GOTO function
    int go[MAXS][MAXC];

    return 1;
}

int CSgrammar::DerivationNode::buildMatchingMachine(std::string arr[], int k, int MAXS, int out[], int* g[], int f[]){
    // ahhhhhhhhhhhhhhhhhhhhh do smth
}

// TODO : implement logic
// adds penalty based on number of rules paterns detected
int CSgrammar::DerivationNode::h_complexity() {
    for ( int size : rule_left_size ) {

    }
    return 1;
}

CSgrammar::DerivationNode::DerivationNode(
    std::vector<Constituent*> form,
    DerivationNode* parent,
    std::vector<std::pair<std::vector<Constituent*>, std::vector<std::vector<Constituent*>>>> steps
) 
: form(form), parent(parent), steps(steps) 
{
    int h = W_STEP*h_step() + W_LENGTH_PENALTY*h_length_penalty(MAX_LENGTH) + W_COMPLEXITY*h_complexity();
    h_score = h;
    g_score = steps.size();
    rule_left_size = std::vector<int>();
    
    // add every different pair left side sizes sizes to vector
    for (auto pair : steps) {
        // if rule left side size isnt in the vector, add it 
        if ( std::find(rule_left_size.begin(), rule_left_size.end(), pair.first.size()) != rule_left_size.end() ){
            rule_left_size.push_back(pair.first.size());
        }
    }
}

// First, add the missing virtual function implementations to CSgrammar class
bool CSgrammar::is1DGenerator() const {
    return true; // Assuming CS grammars generate 1D strings
}

// A* algo to find quickly convergent solution
// should have its own class
std::vector<Constituent*> a_star(std::vector<Constituent*> base, int ruleLengths[]){
    // base case : if Constituent isnt terminal > replace by successor
    // 
    return std::vector<Constituent*>();
}

std::vector<Constituent*> CSgrammar::generate1DImp(int generation, std::vector<Constituent*> base) const {
    if (generation <= 0) { 
        return base; 
    }

    // more complex than i expected
    // will need to use DP with A* algorithm to find fastest convergent outcome

    // placeholder so build doesnt booboo
    return std::vector<Constituent*>();
}

std::vector<std::vector<Constituent*>> CSgrammar::generate2pDImp(int generation, std::vector<std::vector<Constituent*>> base) const {
    throw std::runtime_error("2D generation not implemented for CS grammars");
}

// Fixed read_grammar method for CSgrammar
CSgrammar* CSgrammar::read_grammar(std::string filePath, int skipLines) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filePath);
    }
    
    std::string str;
    std::vector<Constituent*> m, s, t;
    std::map<std::vector<Constituent*>, std::vector<std::vector<Constituent*>>> r;

    // Reserve space for elements
    m.reserve(100);
    t.reserve(100);
    s.reserve(100);

    // map from char to Constituent pointer
    std::map<char, Constituent*> mapper;

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

            std::vector<Constituent*> leftSide;
            std::vector<Constituent*> rightSide;

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
                    r[leftSide] = std::vector<std::vector<Constituent*>>();
                }
                
                // Add to next for each symbol in the left side (for compatibility)
                for (Constituent* sym : leftSide) {
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
        for (const std::vector<Constituent*>& next : pair.second) {
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