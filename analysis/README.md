## analysis folder structure
This folder contains analysis files for Structure 101 and SciTools
Understand. As PINOT has been refactored multiple analysis files 
exist. It also contains helper scripts to create the `.cpa` files
that are required for a Structure 101 project.

The analysis files are order according to their point in the refactor
pipeline. Meaning that the folder starting with 1 contains the analysis
of the original code and the folder starting with 4 contains the analysis
of the refactored code. See the list below:

- `1_pinot_original` contains the analysis files of the original PINOT code. And the OO-Metrics report generated from Understand.
- `2_pinot_refactor_fat_folders` contains the analysis files for improving the file structure.
- `3_pinot_refactor_plan_files` contains the analysis files of analysis of ast.h, ast.cpp, control.h, control.cpp
- `4_pinot_refactor_complete` contains the anlysis files for the refactored code. According to the refactor plan as described in the report. _The report is located in the docs folder. Also contains the Html OO-Metrics report generated for the refactored PINOT.  
- `OOMetrics_analysis.xlsx` contains the OO-Metrics analysis performed on both PINOT and Refactored PINOT.

## Build
Contains the scripts to create the `.cpa` files. See the README at the
root of the project for a detailed explanation on how to use them.
