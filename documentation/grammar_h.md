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


## function 1