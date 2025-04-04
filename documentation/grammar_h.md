[summary](main_doc.md)
# Grammar_h

## attributes

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

## Read_grammar

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