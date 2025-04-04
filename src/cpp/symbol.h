#ifndef SYMBOL
#define SYMBOL

#include <vector>
#include <random>
#include <string>
#include <iostream>

class symbol {
    public :
        symbol(char ch) : c(ch), next() {}
        symbol() : c('\0'), next() {}

        // adds another choice for the next generation
        void add_to_next(std::vector<symbol*> sv){next.push_back(sv); }

        // Return a random symbol in the next vector
        // Note : does the same as getting from the rules map ( see symbol_h.md )
        std::vector<symbol*> operator!(){
            if (this->isTerminal()) {
                // Return a vector with only itself if no next symbols
                return std::vector<symbol*>{this};
            }
            return next.at(std::rand() % next.size());
        }

        bool operator<(const symbol& s2) const {
            return this->getChar() < s2.getChar();
        }
        bool operator==(const symbol& s2) const {
            return (this->getChar() == s2.getChar()) && (this->next == s2.next);
        }

        bool isTerminal(){ return next.empty(); }
        
        char getChar() const { return c; }

    private :
        char c;
        std::vector<std::vector<symbol*>> next;

    // Declare friends
    friend std::ostream& operator<<(std::ostream& os, const symbol& symb);
    friend std::ostream& operator<<(std::ostream& os, const std::vector<symbol>& sym_vec);
};

// Overload output operator for symbol
std::ostream& operator<<(std::ostream& os, const symbol& symb) {
    os << "Symbol: " << symb.c;
    
    // ?? shouldnt this be replaced by the vector<symbol> cout method
    os << " Possible follow-up symbols: ";
    if (symb.next.empty()) {
        os << "{}";
    } else {
        os << "{" << std::endl;
        for ( const std::vector<symbol*>& possibility : symb.next ){
            os << "[" ;
            for (size_t i = 0; i < possibility.size(); i++) {
                os << possibility[i]->c;
                if (i < possibility.size() - 1) {
                    os << ", ";
                }
            }
            os << "]";
            if ( possibility != symb.next.back() ) { os << "," << std::endl; }
        }
        os << "}";
    }
    
    return os;
}

// Overload output operator for vector of symbols
std::ostream& operator<<(std::ostream& os, const std::vector<symbol>& sym_vec) {
    os << '{';
    for (size_t i = 0; i < sym_vec.size(); i++) {
        os << sym_vec[i].c;
        if (i < sym_vec.size() - 1) {
            os << ", ";
        }
    }
    os << '}';
    
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<symbol*>& sym_vec) {
    os << '{';
    for (size_t i = 0; i < sym_vec.size(); i++) {
        os << sym_vec[i]->getChar();
        if (i < sym_vec.size() - 1) {
            os << ", ";
        }
    }
    os << '}';
    
    return os;
}


#endif