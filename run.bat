@echo off
set N_GENERATION=5
set GRAMMAR_FILE=cube_thing.txt
:: python script
set PENCIL_SIZE=6
set ANGLE=90

:: generate grammar
cd .\source\cpp\output\
main.exe ../../grammars/%GRAMMAR_FILE% %N_GENERATION%
cd ..\..\..

:: interpret grammar
cd .\source\Python
python interpreter.py %PENCIL_SIZE% %ANGLE%

cd ..
cd ..