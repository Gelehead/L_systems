[summary](main_doc.md)
# Grammar_h

## UnifiedGrammar

The purpose of this abstract class is to read and handle the grammar files.

#### dimension
1-3D for now 

#### generation_steps
The idea behind this is to have our generation split into multiple steps. For example, for the short term goal of generating a SCAD random map : 
 1. Land / Water generation
 2. height ( / depth ? ) repartition
 3. caverns 
 4. trees

though each one woud need its own algorithm (urgh)


#### New scope
We would want to recreate the wave function collapse algorithm but adding situational awareness. Basically recreating the model synthesis idea but 





## grammar1D
~1 dimension grammar output : you give some rules and it outputs deterministically (for now) a string corresponding to instructions for python turtle



### attributes

#### m - non terminal symbols
Main component for grammar expansion

#### t - terminal symbols
Mappable components :
will be responsible for the final output

#### s - start symbol
Initial(s?) symbol ( for more scalability, should be a vector of initial symbols ).
Grammar expansion will start from here.

#### r - rules 
map of symbols to vector of symbol tuple

symbol -> < {symbol, symbol, symbol}, {symbol, symbol}, etc. >

#### mapper - find better name
Mapper from string to symbols to help read grammar files ( should be useful with really big grammars )
current idea of how to do it :

### functions

#### Read_grammar

shit ton of problems, somehow resolved the 'std::bad_array_new_length' problem with m.reserve(100).

Claude said 
```
Initially, your pointers are valid.
After adding a few symbols to s, s gets reallocated.
The pointers in mapper still point to the old memory locations.
When you access mapper.at('p') after reallocation, you're accessing memory that no longer contains the valid symbol.
This leads to accessing junk data (hence the 'á' character) and eventually causes the memory allocation error when trying to access the invalid memory's next vector.

This is a subtle but dangerous bug that's common in C++ code, and it explains exactly the pattern of errors you're seeing.
```


Other problem with pointers was solved adding pointers everywhere and instantiating symbols as REFERENCES instead of objects and modifying those so the changes are consistent when using the symbols