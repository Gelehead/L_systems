#ifndef GRAMMAR_ELEMENT
#define GRAMMAR_ELEMENT

#include <vector>
#include <random>
#include <string>
#include <iostream>
#include <random>
#include <chrono>


class GrammarElement {
    public :
        virtual ~GrammarElement() = default;

        // interface methods
        bool virtual isTerminal() const = 0;
        virtual std::vector<std::vector<GrammarElement*>> getNextElements() const = 0;
        virtual void addToNext(const std::vector<GrammarElement*>& elements) = 0;

        // randomly select next element
        virtual std::vector<GrammarElement*> selectRandomNext() const = 0;
        
        virtual char getChar() const = 0;
        virtual std::string toString() const = 0;

        virtual bool operator<(const GrammarElement& s2) const = 0;
        virtual bool operator==(const GrammarElement& s2) const = 0;
    
    private:
        std::vector<std::vector<GrammarElement>> next;
        char c;
};

// ===========================================================================
//                                   SYMBOL
// ===========================================================================


class symbol : public GrammarElement{
    private :
        char c;
        std::vector<std::vector<GrammarElement*>> next;
    
        public :
        symbol(char ch) : c(ch), next() {}
        symbol() : c('\0'), next() {}

        bool isTerminal() const override { return next.empty(); }

        // adds another choice for the next generation
        void addToNext(const std::vector<GrammarElement*>& elements) override {
            next.push_back(elements);
        }

        std::vector<std::vector<GrammarElement*>> getNextElements() const override {
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
                for ( const std::vector<GrammarElement*>& possibility : this->next ){
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
        }

        // duplicate of !operator
        std::vector<GrammarElement*> selectRandomNext() const override{
            if (this->isTerminal()) {
                // Return a vector with only itself if no next symbols
                return std::vector<GrammarElement*>{const_cast<symbol*>(this)};
            }
            static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
            std::uniform_int_distribution<size_t> dist(0, next.size() - 1);
            return next.at(dist(rng));
        }

        // Return a random symbol in the next vector
        // Note : supposed to be selectRandomNext()
        std::vector<GrammarElement*> operator!(){
            if (this->isTerminal()) {
                // Return a vector with only itself if no next symbols
                return std::vector<GrammarElement*>{this};
            }
            static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
            std::uniform_int_distribution<size_t> dist(0, next.size() - 1);
            return next.at(dist(rng));
        }

        bool operator<(const GrammarElement& s2) const override {
            const symbol* other = dynamic_cast<const symbol*>(&s2);
            if (!other) {
                // Handle comparison with different types
                // One approach: compare type names
                return typeid(*this).name() < typeid(s2).name();
            }
            return this->getChar() < other->getChar();
        }
        
        bool operator==(const GrammarElement& s2) const override {
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
std::ostream& operator<<(std::ostream& os, const symbol& symb) {
    os << "Symbol: " << symb.c;
    
    // ?? shouldnt this be replaced by the vector<symbol> cout method
    os << " Possible follow-up symbols: ";
    if (symb.next.empty()) {
        os << "{}";
    } else {
        os << "{" << std::endl;
        for ( const std::vector<GrammarElement*>& possibility : symb.getNextElements() ){
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

// ===========================================================================
//                                      TILE
// ===========================================================================


class tile : symbol {

    int x, y, z;
    double width, length;



};




#endif