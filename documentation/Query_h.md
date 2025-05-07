# Query 

Query is supposed to be any request that the main map calls onto a certain ( probably random ) tile that spreads to further tiles.

### Has to contain
 - Response object : 
    - do a shit load of overloaded methods
    - create an object that can contain every information needed 
    
    Further experimentation needed

 - Query depth, if asking the neighbouring tiles : how many neighbours are to be interrogated

 - Queried attribute ( have to "count" every tile asked not to ask the same tile multiple times )