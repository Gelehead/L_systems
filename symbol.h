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

        void operator|(symbol s){ for (symbol sym : s.next ){this->next.push_back(sym);} }

        // Return a random symbol in the next vector
        symbol operator!(){
            if (next.empty()) {
                return *this; // Return self if no next symbols
            }
            return next.at(std::rand() % next.size());
        }

        symbol operator>(symbol s){
            return s;
        }

        bool operator<(const symbol& s2) const {
            return this->getChar() < s2.getChar();
        }

        bool isTerminal(){ return c >= 'a' && c <= 'z'; }
        
        char getChar() const { return c; }
        const std::vector<symbol>& getNext() const { return next; }

    private :
        char c;
        std::vector<symbol> next;

    // Declare friends
    friend std::ostream& operator<<(std::ostream& os, const symbol& symb);
    friend std::ostream& operator<<(std::ostream& os, const std::vector<symbol>& sym_vec);
};

// Overload output operator for symbol
std::ostream& operator<<(std::ostream& os, const symbol& symb) {
    os << "Symbol: " << symb.c;
    
    os << " Follow-up symbols: ";
    if (symb.next.empty()) {
        os << "{}";
    } else {
        os << "{";
        for (size_t i = 0; i < symb.next.size(); i++) {
            os << symb.next[i].c;
            if (i < symb.next.size() - 1) {
                os << ", ";
            }
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

#endif