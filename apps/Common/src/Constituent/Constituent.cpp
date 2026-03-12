#include "Constituent.h"

#include <vector>
#include <random>
#include <string>
#include <iostream>
#include <random>

namespace grammar
{

    bool Constituent::isTerminal() { return terminal; }
    char Constituent::getRep() { return rep; }

    // add to "nextElements" each following element and associated probability
    // ! most likely will create an error as pointers and references arent the exact same
    void Constituent::addToNext(const std::map<std::vector<Constituent*>&, float> elements)
    {
        for (auto const& [cons, prob] : elements)
        {
            // cpp 17+ handles this for us
            // if elements exist -> update, else create pair
            nextElements.insert_or_assign(cons, prob);
        }
    }

    // gives a vector of following constituents
    // ! test this shit
    std::vector<Constituent&> Constituent::getNextElement()
    {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<std::size_t> index_dist(0, nextElements.size() - 1);

        std::vector<Constituent&> choice = nextElements.at(index_dist(gen));

        return choice;
    }

    // ! arbitrary, change asap
    inline bool operator<(Constituent& c2) { return (int) getRep() < (int) c2->getRep(); }

    // compare if 2 constituents are the same ( arbitrary, should be replaced for each children class )
    inline bool operator==(const Constituent& c2) { return getRep() == c2->getRep(); }

    // print for vector of contituent ( might be overloaded )
    inline std::ostream& operator<<(std::ostream& os, const std::vector<Constituent*> v){
        os << "{";
        for ( size_t i = 0 ; i < v.size() ; i++ ) {
            os << v.at(i)->getRep();
            if ( i < v.size() - 1) { os << ", "; }
        }
        os << "}";
        
        return os;
    }

    // print for single constituent
    inline std::ostream& operator<<(std::ostream& os, const Constituent* c) {
        os << "Symbol: " << c->getRep();
        
        // ?? shouldnt this be replaced by the vector<symbol> cout method
        os << " Possible follow-up symbols: ";
        if (c->getNextElements().empty()) {
            os << "{}";
        } else {
            os << "{" << std::endl;
            for ( const std::vector<Constituent*>& possibility : c->getNextElements() ){
                os << "[" ;
                for (size_t i = 0; i < possibility.size(); i++) {
                    os << possibility[i]->getRep();
                    if (i < possibility.size() - 1) {
                        os << ", ";
                    }
                }
                os << "]";
                if ( possibility != c->getNextElements().back() ) { os << "," << std::endl; }
            }
            os << "}";
        }
        
        return os;
    }
}