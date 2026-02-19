# Constituent 
Main component of the grammar generation logic.
Derived following the tree : 

Constituent
|-- Symbol ( 1d )
|-- Tile   ( 2d )
|-- Chunk  ( 3d )


## interface 
function to hide / override : 
  - isTerminal : check if the current Constituent can be further derived 
  - getNextElements : returns a vector of possible next generation from this one Constituent
  - addToNext : returns nothing, adds to the nextElements another vector of possible Constituents 
  - selectRandomNext : takes one of the possible next elements randomly and returns it 
  - getChar : returns the character that 
  - toString : visual representation of Constituent and its next elements

## Other functionalities 
  - "<<" operator : permits fast output for debugging
    -- REQUIRES getChar
    -- has overload for vector of Constituent too

## Notes and commentaries
Compilation of notes across all documentation before deleting the files
1. Shouldn't we keep track of the current generation as tiles shouldnt be able to interact with tile entities generations below them ?
    - A tile can ask information to its neighbouring tiles about previous generations 
2. entropy
"information quantity" that we have about the tile
 - the more incertain we are about its state, the greater the entropy
 - if a tile is collapsed ( has its final state ), its entropy is 0
3. Query is supposed to be any request that the main map calls onto a certain ( probably random ) tile that spreads to further tiles.
  - Has to contain
    - Response object : 
      - do a shit load of overloaded methods
      - create an object that can contain every information needed 
    
      Further experimentation needed

  - Query depth, if asking the neighbouring tiles : how many neighbours are to be interrogated

  - Queried attribute ( have to "count" every tile asked not to ask the same tile multiple times )


### Symbol
The 1 dimensional Constituent for 1D Grammars and L-systems 
-- really abstract 
Used for any purposes, could be cool to make a text parser from this 


### Tile 
2 Dimensional Constituent
Not yet fully coded 


### Chunk 
3 Dimensional Constituent 
--- Current project 
