#!/bin/bash
# above line is used to tell the system to read the file as a bash script

set -e

echo " -- Full project Build -- "

# clean build
echo " -- Cleaning project -- "
rm -rf build
mkdir build

# run cmake configuration and test if went well
echo " -- Configuring project -- "
cmake -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_MAP_TEST=OFF
if [ $? -ne 0 ]; then
  echo " ERROR: CMake configuration failed "
  read -1 -s -r -p "press any key to continue..."
  echo
  exit 1
fi

# Build project ( grammar generation only )
# should clean the project of the perlin noise generation
echo " -- building project -- "
cd build
cmake --build . --config Release --target grammar_gen
if [ $? -ne 0 ]; then
  echo " ERROR: Build failed "
  cd ..
  exit 1
fi

cd ..

echo " -- Build completed succesfully -- "
