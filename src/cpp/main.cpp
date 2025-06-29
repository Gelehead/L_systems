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
    grammar* g = argc > 1 ? grammar::read_grammar(argv[1], 0) : grammar::read_grammar(FIRST_LANGUAGE);
    
    std::string outputPath = (argc > 3) ? argv[3] : DEF_OUTPUT_PATH;

    std::ofstream out(outputPath);

    std::cout << *g << std::endl;

    // no touchey, output logic
    out << grammar::vec2string(g->generate(atoi(argv[2]), g->s));
    out.close();
}