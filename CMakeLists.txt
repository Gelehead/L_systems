cmake_minimum_required(VERSION 3.16)
project(grammar_generation VERSION 0.1.0)

# setup client project 
set(CLIENT ${CMAKE_CURRENT_SOURCE_DIR}/Client)
set(CLIENT_INCLUDE ${CLIENT}/include)
set(CLIENT_SRC ${LOGIC}/src)



# setup logic project
set(LOGIC ${CMAKE_CURRENT_SOURCE_DIR}/Logic)
set(LOGIC_INCLUDE ${LOGIC}/include)
set(LOGIC_SRC ${LOGIC}/src)




# setup shared project 
set(COMMON ${CMAKE_CURRENT_SOURCE_DIR}/Common)
set(COMMON_INCLUDE ${COMMON}/include)
set(COMMON_SRC ${COMMON}/src)




# setup include, src and main.cpp





# create target path




# Create plateform independant build + run script
if(WIN32)
    set(RUN_GRAMMAR_SCRIPT run_grammar.bat)
    
    # windows script ( ideally comes from like win_runner_template.txt )

if(UNIX)
    set(RUN_GRAMMAR_SCRIPT run_grammar.sh)

    # unix script ( ideally comes from like unix_runner_template.txt )

else()
    echo "no macOS support available"


# add custom targets 



#install executable



# output information in console




# ! ideally keeps console open for debug prints of the app to be displayed in
