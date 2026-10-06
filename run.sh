#!/usr/bin/env bash

# variables
outDir="out"
outFile="histograms.pdf"
outFileGraph="graph.pdf"

mkdir -p $outDir

# compile code
g++ -o Histos histos.cpp `root-config --cflags --glibs` || { echo "Error compiling histos.cpp"; exit 1; }

# run code
./Histos "${outDir}/${outFile}" "${outDir}/${outFileGraph}"
