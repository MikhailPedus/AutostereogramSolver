#!/bin/bash

cd CMakeFiles/stereogramTest.dir/src

for file in *.cpp.gcno*
do
  cp "$file" "${file/.cpp.gcno/.gcno}"
done

for file in *.cpp.gcda*
do
  cp "$file" "${file/.cpp.gcda/.gcda}"
done

