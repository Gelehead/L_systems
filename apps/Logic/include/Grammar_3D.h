#ifndef GRAMMAR_3D_H
#define GRAMMAR_3D_H

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdint>

// Shouldnt exist, replace into GRAMMAR_CS_3D

class Grammar_3D : public GrammarUnified {
public :
  // all symbols declarations are implicitely present by inheritance from GrammarUnified
  
  // rules 
  std::map<Constituent*, Constituent*> rules;

  // child class specific constants 
  bool is1DGenerator() { return false; }
  GrammarClass gClass = CS;

  // should be constructed with Grammar_3D::read_grammar
  Grammar_3D(
    const std::vector<Constituent*> non_terminal,
    const std::vector<Constituent*> terminal,
    const std::vector<Constituent*> start,
    const std::map<Constituent*, Constituent*> rules
  );

  // reads a binary file 
  static Grammar_3D* read_grammar(std::string filePath);

  // @return creates a binary file that represents                    a 3D environment
  void generate(int nb_generation, Constituent* base);
}

#endif 
