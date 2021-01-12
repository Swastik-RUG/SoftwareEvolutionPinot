# Software Evolution of PINOT

## The project is an extension to the Pinot project.  
https://www.cs.ucdavis.edu/~shini/research/pinot/  

## Prerequesits  

Clang  

Java 8+  

Structure 101 C/C++  
https://structure101.com/binaries/structure101-studio-cpa-unix-5.0.16419.tar.gz  
https://structure101.com/binaries/structure101-studio-cpa-win64-5.0.16419.exe  
https://structure101.com/binaries/structure101-studio-cpa-macos-5.0.16419.dmg  


## Analysis tools
This project used multiple tools for the analysis of PINOT. All files related to
the analysis of PINOT are located in the `analysis` directory. Inside the analysis
directory the following subdirectories can be found:

- `build-tools`: contains scripts to build the CPA files that are required for
analysis using Structure101. See the section 'How to buld the CPA files' in this
readme for more information.
- `pinot-original`: contains the Structure101 and Understand files that were
used for analysis of the original PINOT application as found [here](https://www.cs.ucdavis.edu/~shini/research/pinot/).
-  `pinot-refactored`: contains the Structure101 and Understand files that were
used for analysis of the refactored PINOT application. The source code of the
refactored PINOT application is located in the `src` folder of this repository.

_Note: the Structure101 projects require an absolute path towards the CPA files. The section 'How to use the Structure101 projects' explains how to use them._

### How to build the CPA files  

To elevtate the complexity in generating the CPA files, a bash script is provided to make this task trivial.  

Find the **script.sh** file inside the build-tools folder of this project.  

Open the script and change the directory paths.  
SRC_DIR -> Pinot source file location.  
AST_DIR -> A temporary storage to create the AST files.  

**SRC_DIR="/mnt/d/Academics/SoftwareEvolution/pinot/src"**  
**AST_DIR="/mnt/d/Academics/SoftwareEvolution/pinot/src/ast_dump"**  

The script also provides an exclude list **EXCLUDE_LIST="Your file"** to exclude any files from the compilation.  

Note: The Script file is currently in its early stages and will undergo refactoring.  


**A prebuilt CPA dump of the Pinot source code can be found in the "/SoftwareEvolutionPinot/tree/main/build-tools/cpa_out" folder.**

### How to use the Structure101 projects
The Structure101 projects require an absolute path towards the CPA files in the
same folder. Use the following steps to open a project:

1. Open the Structure101 file as usual. Structure101 will prompt that it cannot
locate the CPA file(wrong path).
2. In the top menu bar of Structure101 click on Project and the click on Properties..(Shortkey F4 can be used as well).
3. The Project properties menu will pop-up. Now go to the Main settings tab and change the CPA file path to the correct file path on your system.

**Important!!!!!**
When opening the Structure101 project for the original PINOT also change the CPA
path towards the CPA file of the original PINOT source.
