#ifndef GRAMMAR_ELEMENT
#define GRAMMAR_ELEMENT

#include <vector>
#include <random>
#include <string>
#include <iostream>
#include <random>
#include <chrono>


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

// ===========================================================================
//                                   SYMBOL
// ===========================================================================


class symbol : public Constituent{
    private :
        char c;
        std::vector<std::vector<Constituent*>> next;
    
        public :
        symbol(char ch) : c(ch), next() {}
        symbol() : c('\0'), next() {}

        bool isTerminal() const override { return next.empty(); }

        // adds another choice for the next generation
        void addToNext(const std::vector<Constituent*>& elements) override {
            next.push_back(elements);
        }

        std::vector<std::vector<Constituent*>> getNextElements() const override {
            return next;
        }
        char getChar() const override { return c; }

        std::string toString() const override {
            std::string string = "Symbol: " + this->c;
    
            // ?? shouldnt this be replaced by the vector<symbol> cout method
            string += " Possible follow-up symbols: ";
            if (this->isTerminal()) {
                string += "{}";
            } else {
                string += "{" ;
                for ( const std::vector<Constituent*>& possibility : this->next ){
                    string += "[" ;
                    for (size_t i = 0; i < possibility.size(); i++) {
                        string += possibility[i]->getChar();
                        if (i < possibility.size() - 1) {
                            string += ", ";
                        }
                    }
                    string += "]";
                    if ( possibility != this->next.back() ) { string += ",\n"; }
                }
                string += "}";
            }

            return string;
        }

        // duplicate of !operator
        std::vector<Constituent*> selectRandomNext() const override{
            if (this->isTerminal()) {
                // Return a vector with only itself if no next symbols
                return std::vector<Constituent*>{const_cast<symbol*>(this)};
            }
            static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
            std::uniform_int_distribution<size_t> dist(0, next.size() - 1);
            return next.at(dist(rng));
        }

        // Return a random symbol in the next vector
        // Note : supposed to be selectRandomNext()
        std::vector<Constituent*> operator!(){
            if (this->isTerminal()) {
                // Return a vector with only itself if no next symbols
                return std::vector<Constituent*>{this};
            }
            static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
            std::uniform_int_distribution<size_t> dist(0, next.size() - 1);
            return next.at(dist(rng));
        }

        bool operator<(const Constituent& s2) const override {
            const symbol* other = dynamic_cast<const symbol*>(&s2);
            if (!other) {
                // Handle comparison with different types
                // One approach: compare type names
                return typeid(*this).name() < typeid(s2).name();
            }
            return this->getChar() < other->getChar();
        }
        
        bool operator==(const Constituent& s2) const override {
            const symbol* other = dynamic_cast<const symbol*>(&s2);
            if (!other) {
                return false; // Different types can't be equal
            }
            // Check if characters and next elements are equal
            if (this->getChar() != other->getChar()) {
                return false;
            }
            
            // Compare next elements
            const auto& thisNext = this->getNextElements();
            const auto& otherNext = other->getNextElements();
            
            if (thisNext.size() != otherNext.size()) {
                return false;
            }
            
            // Compare each vector of next elements
            for (size_t i = 0; i < thisNext.size(); i++) {
                if (thisNext[i].size() != otherNext[i].size()) {
                    return false;
                }
                
                for (size_t j = 0; j < thisNext[i].size(); j++) {
                    if (!(*thisNext[i][j] == *otherNext[i][j])) {
                        return false;
                    }
                }
            }
            
            return true;
        }

    // Declare friends
    friend std::ostream& operator<<(std::ostream& os, const symbol& symb);
    friend std::ostream& operator<<(std::ostream& os, const std::vector<symbol>& sym_vec);
};

// Overload output operator for symbol
inline std::ostream& operator<<(std::ostream& os, const symbol& symb) {
    os << "Symbol: " << symb.c;
    
    // ?? shouldnt this be replaced by the vector<symbol> cout method
    os << " Possible follow-up symbols: ";
    if (symb.next.empty()) {
        os << "{}";
    } else {
        os << "{" << std::endl;
        for ( const std::vector<Constituent*>& possibility : symb.getNextElements() ){
            os << "[" ;
            for (size_t i = 0; i < possibility.size(); i++) {
                os << possibility[i]->getChar();
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
inline std::ostream& operator<<(std::ostream& os, const std::vector<symbol>& sym_vec) {
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

inline std::ostream& operator<<(std::ostream& os, const std::vector<symbol*>& sym_vec) {
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

// ===========================================================================
//                                  3D symbol
// ===========================================================================


class symbol_3D : Constituent{

    int x, y, z;
    double width, length;

};




#endif