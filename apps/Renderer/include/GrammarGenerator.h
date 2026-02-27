/***************************************************************
 * Starting point of the app, will initialize fronted and 
 * backend ports and will have the while true loop
 *
 **************************************************************/

#ifndef GrammarGenerator_H
#define GrammarGenerator_H

namespace grammar
{
    class Generator
    {
    public:

        /***************************************************************
        * Constructor, ! need to think more about its parameters
        * \param[in] name Name of the generator 
        * \param[in] ???
        * 
        * Will create then set the portfactory 
        ****************************************************************/

        void Generator(
            const std::string name 
        );


        /***************************************************************
        * Destructor                                                   *
        ****************************************************************/

        void ~Generator();


        /***************************************************************
        * Prompt client event handler to read messages sent to its port
        * Stores it into a "data" variable that will be sent to storage
        *
        * \returns true if all inputs were written succesfully 
        * \returns false otherwise
        ****************************************************************/

        bool readInputs();


        /***************************************************************
        * Calls grammarClient.beforeRender(), render(), afterRender()
        * 
        *
        ****************************************************************/

        void run();


        /***************************************************************
        * Sends "data" variable to storage depending on whether they got
        * updated or not 
        * 
        * \returns true if all outputs were succesfully written
        * \returns false otherwise
        ****************************************************************/

        bool writeOutputs();


        /***************************************************************
        * Periodically executed function that calls  
        * readInputs() -> run() -> writeOutputs()
        *
        ****************************************************************/

        void execute();

    };
}


#endif GrammarGenerator_H