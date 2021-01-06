#!/bin/bash

SRC_DIR="/mnt/d/Academics/SeAM_Refactored/SoftwareEvolutionPinot/pinot/src"
AST_DIR="/mnt/d/Academics/SeAM_Refactored/SoftwareEvolutionPinot/pinot/src/ast_dump"
CPA_FILENAME="Pinot_refactored.cpa"
file_ext="cpp"
EXCLUDE_LIST=""

mkdir "$AST_DIR"
mkdir "cap_out"

FILES=($(find $SRC_DIR -type f -name '*.$file_ext' 2>/dev/null))

#for entry in "$SRC_DIR"/*.$file_ext
for entry in `find $SRC_DIR -type f -name '*.cpp'`
do
	filename=$(echo "$entry" | rev | cut -d '/' -f 1| rev)
	
	
        if echo $EXCLUDE_LIST | grep -w "$filename" > /dev/null; then
          echo "Ignored :$filename....."
        else
          echo "processing :$filename....."
	  clang++ -c -ferror-limit=0 -fno-delayed-template-parsing -fno-color-diagnostics -Wno-everything -Xclang -ast-dump "$entry" > "$AST_DIR/$filename.ast" 
        fi       
done

java -jar structure101-parser-ast-cpa.jar generate-cpa -use-db -gzip-compress -keep-going -ignore-compilation-errors -d "$AST_DIR/" -o "cpa_out/$CPA_FILENAME"
