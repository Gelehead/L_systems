#include "grammar.h"
#include <iostream>
#include <fstream>
#define FIRST_LANGUAGE "../../grammars/first_language.txt"

int main(int argc, char** argv){
    grammar g = argc > 1 ? grammar::read_grammar(argv[1]) : grammar::read_grammar(FIRST_LANGUAGE);

    //std::cout << g << std::endl;
    //std::cout << g.generate(atoi(argv[2]), g.s) << std::endl;
    std::ofstream out("gram_gen.txt");
    out << grammar::vec2string(g.generate(atoi(argv[2]), g.s));
    out.close();
}