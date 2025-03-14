#ifndef SYMBOL
#define SYMBOL

#include <vector>
#include <random>
#include <string>

class symbol {
    public :
        symbol(char ch) : c(ch), next(isTerminal() ? std::vector<symbol>{symbol(ch)} : std::vector<symbol>{}) {}
        symbol() : c(NULL), next(std::vector<symbol>{}) {}

        void operator|(symbol s){ for (symbol sym : s.next ){this->next.push_back(sym);} }

        // return a random symbol in the next vector
        symbol operator!(){ return next.at(std::rand() % next.size());}

        symbol operator>(symbol s){
            return s;
        }

        bool isTerminal(){ return c >= 'a' && c <= 'z'; }

    private :
        char c;
        std::vector<symbol> next;

    friend std::ostream& operator<<(std::ostream& os, const symbol& symb);
};

// overload output ( " << " ) behaviour for symbol
std::ostream& operator <<(std::ostream& os, const symbol& symb) { 
    os << std::string("symbols : ") << symb.c << std::string("\n follow up symbols : ") << symb.next;
    return os;
}

// overload output ( " << " ) behaviour for symbol vector
std::ostream& operator << (std::ostream& os, const std::vector<symbol>& sym_vec) {
    os << '{';
    for ( int i = 0; i < sym_vec.size() ; i++ ) {
        os << sym_vec.at(i);
        if ( i < sym_vec.size() - 1 ) { 
            os << ',' << ' ';
        }
    }
    os << '}';
    
    return os;
}

#endif