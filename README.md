# SoftwareEvolutionPinot  

## The project is an extension to the Pinot project.  
https://www.cs.ucdavis.edu/~shini/research/pinot/  

## Prerequesits  

Clang  

Java 8+  

Structure 101 C/C++  
https://structure101.com/binaries/structure101-studio-cpa-unix-5.0.16419.tar.gz  
https://structure101.com/binaries/structure101-studio-cpa-win64-5.0.16419.exe  
https://structure101.com/binaries/structure101-studio-cpa-macos-5.0.16419.dmg  

## How to build the CPA files  

To elevtate the complexity in generating the CPA files, a bash script is provided to make this task trivial.  

Find the **script.sh** file inside the build-tools folder of this project.  

Open the script and change the directory paths.  
SRC_DIR -> Pinot source file location.  
AST_DIR -> A temporary storage to create the AST files.  

**SRC_DIR="/mnt/d/Academics/SoftwareEvolution/pinot/src"**  
**AST_DIR="/mnt/d/Academics/SoftwareEvolution/pinot/src/ast_dump"**  

The script also provides an exclude list **WORD_LIST="Your file"** to exclude any files from the compilation.  

Note: The Script file is currently in its early stages and will undergo refactoring.  


### A prebuilt CPA dump of the Pinot source code can be found in the "/SoftwareEvolutionPinot/tree/main/build-tools/cpa_out" folder.
