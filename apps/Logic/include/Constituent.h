#ifndef CONSTITUENT_H
#define CONSTITUENT_H

#include <vector>
#include <random>
#include <string>
#include <iostream>
#include <random>
#include <chrono>

// Term was inspired by a paper suggested by Youssef (https://web.stanford.edu/~jurafsky/slp3/18.pdf)
class Constituent {
    public :
        virtual ~Constituent() = default;

        // interface methods
        bool virtual isTerminal() const = 0;
        virtual std::vector<std::vector<Constituent*>> getNextElements() const = 0;
        virtual void addToNext(const std::vector<Constituent*>& elements) = 0;

        // randomly select next element
        virtual std::vector<Constituent*> selectRandomNext() const = 0;
        
        virtual char getChar() const = 0;
        virtual std::string toString() const = 0;

        virtual bool operator<(const Constituent& s2) const = 0;
        virtual bool operator==(const Constituent& s2) const = 0;
    
    private:
        std::vector<std::vector<Constituent>> next;
        char c;
};

inline std::ostream& operator<<(std::ostream& os, const std::vector<Constituent*> v){
    os << "{";
    for ( size_t i = 0 ; i < v.size() ; i++ ) {
        os << v.at(i)->getChar();
        if ( i < v.size() - 1) { os << ", "; }
    }
    os << "}";
    
    return os;
}

// Overload output operator for Constituent
inline std::ostream& operator<<(std::ostream& os, const Constituent* ge) {
    os << "Symbol: " << ge->getChar();
    
    // ?? shouldnt this be replaced by the vector<symbol> cout method
    os << " Possible follow-up symbols: ";
    if (ge->getNextElements().empty()) {
        os << "{}";
    } else {
        os << "{" << std::endl;
        for ( const std::vector<Constituent*>& possibility : ge->getNextElements() ){
            os << "[" ;
            for (size_t i = 0; i < possibility.size(); i++) {
                os << possibility[i]->getChar();
                if (i < possibility.size() - 1) {
                    os << ", ";
                }
            }
            os << "]";
            if ( possibility != ge->getNextElements().back() ) { os << "," << std::endl; }
        }
        os << "}";
    }
    
    return os;
}


//      (1D Constituent) 
//  SYMBOL IS IN ANOTHER FILE
//

//      (2D constituent)
//  TILE IS IN ANOTHER FILE
//

//      (3D constituent)
//  CHUNK IS IN ANOTHER FILE
//

#endif
