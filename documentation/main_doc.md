# Summary

## often used commentary linguo
 - '??' : unclear purpose of following code
 - 'Note :' : good to know, might be of use to optimize code

## Ideas, notes, wtv
I'm questionning the whole pointer idea. It migh be a good idea to get the reference thing done now because it might compromise the exection some time in the future.
-- Done, translation to pointer logic 

Translating into 2d space 

Abstract Multi LAyer Grammar ( AMLAG ) generation algorithm
1. Initialize map
   1. Initialize each tile 
   2. Declare its neighbours
2. Select lowest entropy tile ( random amongst lowest equal values )
3. Query up to the nth Moore ( both right/left and diagonal ) neighbours distance to get likelihood of outcome
4. "Collapse" into one of its possible next consistuent ( weighted by likelihood )
5. Back to step 2 until the whole map is filled with upper layer 



### [Logs](logs.md)
Only relevant commits will be mentionned, some are just daily commit things to have a pretty github profile

### [Grammar.h](grammar_h.md)
The backbone of this whole application. 

TODO :
 1. Add positional awareness of grammar
    - Grammar should generate randomly then adapt to its own generation by situational / positional awareness : when some consistuent appear, it should generate / destroy other specific consistuents.
    (writing this later just to flex but this is known as CSG and i had no idea it existed yet theorized it)

### [Consistuent.h](Consituent.md)
"Constituent" term coming from ( or at least first heard of in ) "Context-Free Grammars and Constituency Parsing" - Speech and Language Processing. Daniel Jurafsky & James H. Martin. Proposed by a friend.




### [file.h](file.md)
small description 

### [file.h](file.md)
small description 


## Resources 

 - [Speech and Language Processing. Daniel Jurafsky & James H. Martin.](https://web.stanford.edu/~jurafsky/slp3/18.pdf)

 
 - Model synthesis
    
    Paul Merell
    - [P. Merrell. Model Synthesis.  Ph.D. Dissertation, University of North Carolina at Chapel Hill, 2009](https://paulmerrell.org/wp-content/uploads/2021/06/thesis.pdf)
    - [P. Merrell and D. Manocha. Model Synthesis: A General Procedural Modeling Algorithm. IEEE Transactions on Visualization and Computer Graphics, 2010.](https://paulmerrell.org/wp-content/uploads/2021/06/tvcg.pdf)
    - [P. Merrell and D. Manocha. Continuous Model Synthesis.  ACM Transactions on Graphics, 2008.](https://paulmerrell.org/wp-content/uploads/2021/06/continuous.pdf)
    - [P. Merrell. Example-Based Model Synthesis. Symposium on Interactive 3D Graphics (i3D), 2007.](https://paulmerrell.org/wp-content/uploads/2022/03/model_synthesis.pdf)
    - [P. Merrell and D. Manocha. Example-Based Curve Generation.  Computers & Graphics, 2010.](https://paulmerrell.org/wp-content/uploads/2021/06/curveSynthesis.pdf)

 - Context Free Grammars ( CFG )
    - find sum interesting that can be of any use
    - Parsing Expression Grammars (PEG)
    - Ordered CFG (oCFG)


 - Wave Function Collapse

    Maxim Gumin
    - [Gumin's github repo](https://github.com/mxgmn/WaveFunctionCollapse)

 - [Comparison between WFC and MS](https://paulmerrell.org/wp-content/uploads/2021/07/comparison.pdf)

 - Graph Grammars
    - [Example-Based Procedural Modeling Using Graph Grammars](https://paulmerrell.org/wp-content/uploads/2024/02/ProcModelUsingGraphGram.pdf)

 - [Good recap and general idea video](https://www.youtube.com/watch?v=zIRTOgfsjl0)