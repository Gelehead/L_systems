#include "GrammarUnified.h"
#include "GrammarCS_1D.h"
#include "grammar.h"

// GrammarUnified implementations

// @param filePath path/to/grammar from called location (usually L_systems\)
// @return nullptr if no match, result from CS::read_grammar if matched CS, result from CF::read_grammar if matched CF
GrammarUnified* GrammarUnified::read_grammar(std::string filePath) {
    std::string type;
    int dimension;
    GrammarClass gramClass;
    
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filePath);
    }
    
    // read variables
    // tf is noise steps 
    file >> dimension >> type;
    if (type == "CS") {
        gramClass = CS;
    } else if (type == "CF") {
        gramClass = CF;
    } else {
        throw std::runtime_error("Unknown grammar type: " + type);
    }

    try {
        switch ( gramClass ) {
            case CS :
                return GrammarCS_1D::read_grammar(filePath, 1);

            case CF :
                if ( dimension == 1 ) { 
                    return grammar::read_grammar(filePath, 1); 
                }
                else { 
                    throw std::logic_error("not implemented"); 
                }

            default:
                break;
        }
    } catch ( const std::exception& e){
        throw std::runtime_error("failed to parse " + type + " from " + filePath + " : " + e.what() );
    }
    
    // if doesnt match any expected pattern, return nullptr
    return nullptr;
}

GrammarUnified::GrammarUnified() : m(), t(), s() {}

GrammarUnified::GrammarUnified(
    const std::vector<Constituent*> non_terminal, 
    const std::vector<Constituent*> terminal, 
    const std::vector<Constituent*> start
) : m(non_terminal), t(terminal), s(start) {}

// checks if grammar is 1D L_system
std::vector<Constituent*> GrammarUnified::generate(int generation, std::vector<Constituent*> base) const {
    if (is1DGenerator()) {
        return generate1DImp(generation, base);
    }
    else {
        throw std::runtime_error("This grammar only supports 2D generation");
        return std::vector<Constituent*>();
    }
}

std::vector<std::vector<Constituent*>> GrammarUnified::generate(int generation, std::vector<std::vector<Constituent*>> base) const {
    if (!is1DGenerator()) {
        throw std::runtime_error("This grammar does not support 2D generation");
    }
    return generate2pDImp(generation, base);
}

std::ostream& operator<<(std::ostream& os, const GrammarUnified& g) {
    os << "Non terminal symbols : " << std::endl << g.m << std::endl;
    os << "Terminal symbols : " << std::endl << g.t << std::endl;
    os << "Starting symbol : " << std::endl << g.s << std::endl;

    return os;
}

// --------------- CS Grammar --------------- 
