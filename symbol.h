#ifndef SYMBOL
#define SYMBOL

#include <vector>
#include <random>

class symbol {
    public :
        char c;

        symbol(char ch) : c(ch), next(isTerminal() ? std::vector<symbol>{symbol(ch)} : std::vector<symbol>{}) {}
        symbol() : c(NULL), next(std::vector<symbol>{}) {}

        void operator|(symbol s){ for (symbol sym : s.next ){this->next.push_back(sym);} }

        // return a random symbol in the next vector
        symbol operator!(){ return next.at(std::rand() % next.size());}

        symbol operator>(symbol s){
            return ;
        }

        bool isTerminal(){ return c >= 'a' && c <= 'z'; }

    private :
        std::vector<symbol> next;

};

#endif