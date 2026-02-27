#include "GrammarGenerator.h"

int main()
{
    grammar::Generator generator("grammar gen");

    while ( !generator._exit )
    {
        generator.execute();
    }
    return 0;
}