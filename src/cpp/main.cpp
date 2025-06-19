#include "grammar.h"
#include "noise.h"
#include <iostream>
#include <fstream>

#define DEF_OUTPUT_PATH "../../build/grammars/gram_gen.txt"
#define FIRST_LANGUAGE "../../grammars/first_language.txt"

/* arguments
 1- input grammar file
 2- generation
 3- output path
*/
int main(int argc, char** argv) {
    // Process grammar first
    GrammarUnified* big_g = GrammarUnified::readGrammar(argv[1]);

    grammar* g = argc > 1 ? grammar::read_grammar(argv[1]) : grammar::read_grammar(FIRST_LANGUAGE);
    std::string outputPath = (argc > 3) ? argv[3] : DEF_OUTPUT_PATH;

    std::ofstream out(outputPath);

    // print input grammar path
    std::cout << "input grammar path" << std::endl;
    std::cout << argv[1] << std::endl;
    std::cout << "" << std::endl;

    std::cout << "number of generations" << std::endl;
    std::cout << argv[2] << std::endl;
    std::cout << "" << std::endl;

    std::cout << *g << std::endl;

    //std::cout << grammar::vec2string(g->generate(atoi(argv[2]), g->s)) << std::endl;

    out << grammar::vec2string(g->generate(atoi(argv[2]), g->s));
    out.close();
}