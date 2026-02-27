/***************************************************************
 * Starting point of the client 
 * backend ports and will have the while true loop
 *
 **************************************************************/

#ifndef GrammarClient_H
#define GrammarClient_H

namespace grammar
{
    class Client
    {
    public:
            
        /***************************************************************
        * Any object creation, map/terrain/mesh processing 
        * Fetching storage and data preprocessing
        **************************************************************/

        void beforeRender();
        

        /***************************************************************
        * main render logic 
        **************************************************************/

        void render();


        /***************************************************************
        * object deletion mainly ?
        **************************************************************/

        void afterRender();


    private:
        // fuckload of variable that will be used when rendering 
    };
}

#endif // GrammarClient_H