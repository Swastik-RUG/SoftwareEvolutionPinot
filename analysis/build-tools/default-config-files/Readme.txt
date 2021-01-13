

The excludes.txt and compile_config.json files included here will help you get started with generating a .cpa from your C/C++ source code.
Copy them to the ROOT directory of your source tree, and edit as required.
The excludes.txt file contains the patterns to exclude most system includes and commonly used libraries.
The compile_config.json is a starting point for configuring your Clang AST generation, mostly removing commonly used compiler commands,
and arguments known not to be recognised by Clang. There is also a section for mapping your-compiler-argument to clang-equivalent-argument