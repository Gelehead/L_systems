#include "grammar.h"
// somehow we re in "output" directory
#define FIRST_LANGUAGE "../grammars/first_language.txt"

int main(int argc, char** argv){
    grammar g = argc > 1 ? grammar::read_grammar(argv[1]) : grammar::read_grammar(FIRST_LANGUAGE);

    std::cout << g << std::endl;
}