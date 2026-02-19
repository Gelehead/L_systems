#ifndef CHUNK_H
#define CHUNK_H

#include <Constituent.h>

class Chunk : public Constituent {
public :
  bool isTerminal() override;
  // Hides normal Constituent function
  std::vector<std::vector<Chunk*>> getNextElements() override;
  void addToNext(const std::vector<Chunk*>& elements) override;
  

  
  private:
    // originally wasnt a vector of pointers, but it should make more sense to have it as that 
    std::vector<std::vector<Constituent*>> next;
}

#endif 
