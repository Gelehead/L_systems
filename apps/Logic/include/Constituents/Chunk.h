#ifndef CHUNK_H
#define CHUNK_H

#include "Constituent.h"

namespace grammar
{
  
  class Chunk : public Constituent
  {
  private:
    // 
    std::vector<std::vector<std::vector<ConstituenType>>> composition;
  public:
    Chunk();

    std::vector<Constituent *> getNextElements(Seed seed) const override;
    void addToNext(std::vector<Constituent *> element, float probability) override;
  };

} // namespace grammar


#endif // CHUNK_H
