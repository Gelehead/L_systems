#!/bin/bash

# READ ME FIRST
# This is the main run script for UNIX ( arch at least ) for the grammars project
# @args : run.sh @1
# @1 : 1 if you want to clean build the project
#    : 0 or nothing will simply run the project

# If you see a python turtle window pop up with a fractal pattern, it should be working

## Main logic generation parameters
N_GENERATION=4
GRAMMAR_FILE=cube_thing.txt
OUTPUT_GRAMMAR=gram_gen.txt

## python script parameters
PENCIL_SIZE=8
ANGLE=90

# run if in doubt, will only take a bit more time
if [ "$1" == "1" ]; then
  # text messages and failsafes implemented inside the script
  ./build.sh
fi

# Mandatory check to see if the directories exist and are populated
echo " -- Directory checks -- "

# build directory
if [ ! -d "build" ]; then
  echo " No build directory detected "
  echo " Creating one... "
  mkdir build
fi

# build/grammars directory
if [ ! -d "build/grammars" ]; then
  echo " No build/grammars directory detected "
  echo " Creating build/grammar directory "
  mkdir build/grammars
fi

# same with .exe files
echo " -- executables checks -- "

# if previous directories
if [ -x "build/grammar_gen" ]; then
  GRAMMAR_EXE="build/grammar_gen"
else
  echo " ERROR: grammar_gen not found in build/ "
  exit 1
fi

# check if input grammar file exists
if [ ! -f "src/grammars/$GRAMMAR_FILE" ]; then
  echo " ERROR: Input grammar file path not found : src/grammars/$GRAMMAR_FILE"
  exit 1
fi

echo " Running: $GRAMMAR_EXE$ \"src/grammars/$GRAMMAR_FILE\" $N_GENERATION$ \"build/grammars/$OUTPUT_GRAMMAR$\" "

"$GRAMMAR_EXE" \
  "src/grammars/$GRAMMAR_FILE" \
  "$N_GENERATION" \
  "build/grammars/$OUTPUT_GRAMMAR"

# check if grammar generation was succesful
if [ ! -f "build/grammars/$OUTPUT_GRAMMAR" ]; then
  echo " ERROR: grammar generation failed : no output file created "
  exit 1
fi

# running python interpreter
echo " -- Running python interpreter -- "
cd "src/Python"
python interpreter.py $PENCIL_SIZE $ANGLE "../../build/grammars/$OUTPUT_GRAMMAR"
cd "../../"

echo " -- Process completed succesfully -- "
