#include "grammar.h"
// somehow we re in "output" directory
#define FIRST_LANGUAGE "../grammars/first_language.txt"

int main(){
    grammar g = grammar::read_grammar(FIRST_LANGUAGE);
}
