#ifndef CONSTITUENT_H
#define CONSTITUENT_H

#include <vector>
#include <iostream>
#include <stdint.h>
#include "Seed.h"

// Term was inspired by a paper suggested by Youssef (https://web.stanford.edu/~jurafsky/slp3/18.pdf)
namespace grammar
{
    // 32bytes Constituent payload used by Binary<writer/reader>
    // every children should have its all payload that adds to this structure
    struct Constituent
    {
        uint16_t TypeID = 0;
        uint8_t flags = 0;
        Seed seed;

        // 29 other bytes unused (most likely position)
    };

    class Constituent
    {
    public:
        // makes a random choice among all possible nextElements
        virtual std::vector<Constituent&> getNextElements() const = 0;

        // add to next Elements
        virtual void addToNext(const std::map<std::vector<Constituent*>&, float> elements) const = 0;

        // get representation ( for ASCII / other symbolic representation of system )
        virtual char getRep() const = 0;

        // implemented here 
        virtual bool isTerminal();
        virtual bool operator<(const Constituent& c2)   const = 0;
        virtual bool operator==(const Consistuent& c2)  const = 0;

    private: 
        // tells whether 
        bool terminal;
        std::map<std::vector<std::vector<Constituent&>*>, float> nextElements;
        // symbolic representation of consistuent for grammar
        char rep;


    protected:
        virtual Constituent();
        virtual ~Constituent() = default;
    };
}

#endif // CONSTITUENT_H
