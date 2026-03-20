## Header 
 - Grammar type 
    -> CF = 0
    -> CS = 1
 
 - number of terminals
 - max size of terminals
 
 - number of non terminals 
 - max size of non terminals
 
 - Size of start vector
    -> (X, Y, Z) if CS
    -> X if CF 
        -> A \in {X,Y,Z} is the half length to the further most character
        --> start + A = leftmost considered character, same for right

 - Number of rules
 - Context size 
    -> (X, Y, Z)
    -> X

## body 

### Context Sensitive

 1. Terminal 1
    Terminal 2
    ...

 2. Non Terminal 1
    Non Terminal 2

 3. 