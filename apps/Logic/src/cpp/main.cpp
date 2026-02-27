#include "grammar.h"
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
    
    grammar *g = grammar::read_grammar(argv[1], 1);

    std::cout << *g << std::endl;

    // grammar* g = argc > 1 ? grammar::read_grammar(argv[1], 0) : grammar::read_grammar(FIRST_LANGUAGE);

    // std::cout << g->gClass << std::endl;

    // no touchey, output logic
    std::ofstream out(argv[3]);
    out << grammar::vec2string(g->generate(atoi(argv[2]), g->s));
    out.close();
}
