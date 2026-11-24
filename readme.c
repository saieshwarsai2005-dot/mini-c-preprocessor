cat > README.md <<'EOF'
# Mini C Preprocessor

## Project Overview

This project implements a basic C preprocessor using the C programming language.

It demonstrates selected preprocessing operations performed before compilation.

## Features

### 1. Comment Removal
- Removes single-line comments (//).
- Removes multi-line comments (/* ... */).
- Includes basic handling of double-quoted strings.

### 2. File Inclusion
- Processes basic #include directives.
- Supports header filenames using quotation marks and angle brackets.
- Attempts to locate system headers in /usr/include.

### 3. Macro Handling
- Supports object-like macros.
- Supports function-like macros.
- Performs basic macro parameter substitution.

## Technologies Used

- C Programming
- File Handling
- Pointers
- Structures
- String Handling
- Header Files
- Makefile

## Project Structure

- cmdtremove.c - Comment removal implementation
- cmdremoval.h - Comment removal declaration
- file_inclusion.c - File inclusion implementation
- file_inclusion.h - File inclusion declaration
- macro_handler.c - Macro processing implementation
- macro_handler.h - Macro processing declaration
- mypreprocessor.c - Main program
- test.c - Testing source file
- Makefile - Build instructions

## Compilation

Build the project using:

make

Run the generated executable according to the Makefile.

## Limitations

This is an educational implementation of selected C preprocessing operations. It does not implement the complete C preprocessor standard.

## Learning Objectives

- Understanding file handling in C.
- Working with pointers and structures.
- Understanding string processing.
- Practising modular programming.
- Learning basic preprocessing concepts.
EOF
