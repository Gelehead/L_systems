# Tile_H

Principal agent of the procedural map generation, shouldnt be too complex not to force too harsh computation problems.



### Notes and commentaries
1. Shouldn't we keep track of the current generation as tiles shouldnt be able to interact with tile entities generations below them ?
    - A tile can ask information to its neighbouring tiles about previous generations 
    - 

### Attributes 

#### parent 
pointer to parent Tile 

Used to keep track of the terrain generation step by step

#### Children
vector of tile pointers 

#### neighbours 
2/3D vector of tile pointers 

#### entropy
"information quantity" that we have about the tile
 - the more incertain we are about its state, the greater the entropy
 - if a tile is collapsed ( has its final state ), its entropy is 0