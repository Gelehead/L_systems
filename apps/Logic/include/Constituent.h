#ifndef CONSTITUENT_H
#define CONSTITUENT_H

#include <vector>
#include <iostream>
#include <stdint.h>
#include "Seed.h"
#include <map>

// Term was inspired by a paper suggested by Youssef (https://web.stanford.edu/~jurafsky/slp3/18.pdf)
namespace grammar
{
    /*******************************************************************
     * 32 bytes Constituent payload used by Binary<Reader/Writer>
     * every children should have its all payload that adds to this structure
     * 7 / 32 bytes used here
     ********************************************************************/
    struct ConstituentPayload
    {
        uint16_t TypeID = 0;
        uint8_t flags = 0;
        Seed seed; // 4 bytes
    };

    class Constituent
    {
    private:
        std::map<std::vector<Constituent *>, float> _nextElements;
        bool _terminal;
        char _rep;

    public:
        /*******************************************************************
         * \brief makes a random choice among all possible _nextElements accounting for probabilities
         * \param seed needs world seed to make generation deterministic
         * \returns ref of constituent
         ********************************************************************/
        virtual std::vector<Constituent *> getNextElements(Seed seed) const = 0;

        /*******************************************************************
         * \brief add Constituent to objects' _nextElements with probability
         * \param &element reference to Constituent
         * \param probability : threshold random number has to go over before being considered : [0,1]
         * \returns
         ********************************************************************/
        virtual void addToNext(Constituent *element, float probability) = 0;

        /*******************************************************************
         * \brief get representation (ASCII)
         ********************************************************************/
        virtual char getRep() { return _rep; }
        virtual bool isTerminal() { return _terminal; }

    protected:
        Constituent() {};
        ~Constituent() = default;
    };
}

#endif // CONSTITUENT_H
