#!/bin/bash

SRC_DIR="/mnt/d/Academics/SoftwareEvolution/pinot/src"
AST_DIR="/mnt/d/Academics/SoftwareEvolution/pinot/src/ast_dump"
CPA_FILENAME="Pinotv1.cpa"
file_ext="cpp"
EXCLUDE_LIST="ast.cpp"

for entry in "$SRC_DIR"/*.$file_ext
do
	filename=$(echo "$entry" | rev | cut -d '/' -f 1| rev)
	
	
        if echo $EXCLUDE_LIST | grep -w "$filename" > /dev/null; then
          echo "Ignored :$filename....."
        else
          echo "processing :$filename....."
	  clang++ -c -fno-delayed-template-parsing -fno-color-diagnostics -Xclang -ast-dump "$entry" > "$AST_DIR/$filename.ast" 
        fi       
done

java -jar structure101-parser-ast-cpa.jar generate-cpa -use-db -gzip-compress -keep-going -ignore-compilation-errors -d "$AST_DIR/" -o "cpa_out/$CPA_FILENAME"
