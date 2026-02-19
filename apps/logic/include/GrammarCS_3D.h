#ifndef GRAMMAR_CS_3D_H
#define GRAMMAR_CS_3D_H

#include "GrammarUnified.h"
#include "Map.h"

class GrammarCS_3D : public GrammarUnified {
public: 
  // terminal, non terminal and start Constituents are implicitely declared by inheritance from GrammarUnified
  std::map<Constituent*, Constituent*> rules;

  GrammarCS_3D(
      const std::vector<Tile*> non_terminal,
      const std::vector<Tile*> terminal,
      const std::vector<Tile*> start,
      // uses Constituents that are specifically concieved for 3D purposes (See chunk.h)
      const std::map<Constituent*, Constituent*> rules
  );

  static GrammarCS_3D* read_grammar(std::string filePath);

  void generate(int nb_generation, Constituent* base);

    /*
    Steps to take from now on
    - [o] Function to generate "next generation" based on existing map
    - [o] Parallel call of all tiles to a big array to have most likely outcome
    - [o] Choose model to encode the generation rules
    - [o] seeding problem (most likely outcome will create patterns, which we dont want?)
    - [o] Pull map from csv
    - [o] Find a way to say like "if there is at least one tile of type 2 in direct vicinity, do XYZ"
    */
};

#endif
