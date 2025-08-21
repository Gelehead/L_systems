#ifndef GRAMMAR_CS_H
#define GRAMMAR_CS_H

#include "GrammarUnified.h"

class CSgrammar : public GrammarUnified {
public:
    // Subclass used in the construction of the implicit graph
    // should have its own class ( generalizable to graph A* )
    class DerivationNode{
    public:
        std::vector<Constituent*> form;
        DerivationNode* parent;
        std::vector<std::pair<std::vector<Constituent*>, std::vector<std::vector<Constituent*>>>> steps;
        int g_score, h_score;
        std::vector<int> rule_left_size;

        // CONSTANTS
        // in [0, 1]
        static const int W_STEP = 1;
        static const int W_LENGTH_PENALTY = 1;
        static const int W_COMPLEXITY = 1;
        
        static const int MAX_LENGTH = 4000;

        // constructor
        DerivationNode(
            std::vector<Constituent*> form,
            DerivationNode* parent,
            std::vector<std::pair<std::vector<Constituent*>, std::vector<std::vector<Constituent*>>>> steps
        );

        // heuristics functions
        // count nonterminals
        //int h_step();
        
        // apply penalty if too long
        //int h_length_penalty(int max_length = MAX_LENGTH);
        
        // count number of patterns present in current string
        //int h_complexity();


        // aho-corasick functions
        //int buildMatchingMachine(std::string arr[], int k, int MAXS, int out[], int* g[], int f[]);
    };

    std::map<std::vector<Constituent*>, std::vector<std::vector<Constituent*>>> r;

    CSgrammar(
        const std::vector<Constituent*> non_terminal, 
        const std::vector<Constituent*> terminal, 
        const std::vector<Constituent*> start,
        std::map<std::vector<Constituent*>, std::vector<std::vector<Constituent*>>> rules
    );

    CSgrammar();

    static CSgrammar* read_grammar(std::string filePath, int skipLines = 0);

    // Add these missing virtual function overrides:
    bool is1DGenerator() const override;

protected:
    std::vector<Constituent*> generate1DImp(int generation, std::vector<Constituent*> base) const override;
    std::vector<std::vector<Constituent*>> generate2pDImp(int generation, std::vector<std::vector<Constituent*>> base) const override;
};

class Grammar3D : public GrammarUnified {
    // Implementation to be defined
public:
    bool is1DGenerator() const override { return false; }

protected:
    std::vector<Constituent*> generate1DImp(int generation, std::vector<Constituent*> base) const override {
        throw std::runtime_error("Not implemented");
    }
    
    std::vector<std::vector<Constituent*>> generate2pDImp(int generation, std::vector<std::vector<Constituent*>> base) const override {
        throw std::runtime_error("Not implemented");
    }
};

#endif GRAMMAR_CS_H