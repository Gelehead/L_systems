/***************************************************************
* List of all flags and corresponding types 
* Inspired from ImGui flagging system using bitwise operations
*
* empty for now but will be updated when needed 
****************************************************************/

// types 
typedef int GramFlags;


// enums 

// Flags for main app really high level configs
enum GramFlags_
{
        GramFlags_None          = 0,
        GramFlags_Debug         = 1 << 1
};
