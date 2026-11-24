
# Mini C Preprocessor

## 1. Project Overview

The Mini C Preprocessor is a basic preprocessor tool developed using the C programming language.

The purpose of this project is to understand how a C preprocessor performs operations on a source file before compilation.

The program reads a C source file, processes selected preprocessing operations, and generates an output file with the `.i` extension.

## 2. Objectives

- Understand the basic working of a C preprocessor.
- Remove comments from a C source file.
- Process basic file inclusion directives.
- Perform basic macro substitution.
- Generate an output file with the `.i` extension.

## 3. Features

### A. Comment Removal

- Removes single-line comments (`//`).
- Removes multi-line comments (`/* ... */`).
- Includes basic handling of double-quoted strings.

### B. File Inclusion

- Processes basic `#include` directives.
- Supports header filenames written using quotation marks and angle brackets.
- Attempts to locate system header files in `/usr/include`.

### C. Macro Handling

- Supports object-like macros.
- Supports function-like macros.
- Performs basic macro parameter substitution.

## 4. Technologies Used

- C Programming Language
- File Handling
- Pointers
- String Handling
- Header Files
- Structures
- Makefile
- Linux Environment

## 5. Project File Structure

| File Name | Description |
|---|---|
| `mypreprocessor.c` | Main program |
| `cmtremove.c` | Comment removal implementation |
| `cmdremoval.h` | Comment removal header file |
| `file_inclusion.c` | File inclusion implementation |
| `file_inclusion.h` | File inclusion header file |
| `macro_handler.c` | Macro handling implementation |
| `macro_handler.h` | Macro handling header file |
| `test.c` | Test source file |
| `Makefile` | Compilation instructions |

## 6. Compilation and Execution

### Step 1: Clone the repository

```bash
git clone https://github.com/saieshwarsai2005-dot/mini-c-preprocessor.git
```

### Step 2: Enter the project directory

```bash
cd mini-c-preprocessor
```

### Step 3: Compile the project

```bash
make
```

### Step 4: Run the preprocessor

```bash
./mypreprocessor test.c
```

The program generates an output file with the `.i` extension.

### Step 5: View the output

```bash
cat test.i
```

## 7. Expected Output

The generated `.i` file contains the processed source code after the supported comment removal, file inclusion, and macro substitution operations.

The exact output depends on the input source file and the preprocessing operations supported by the implementation.

## 8. Limitations

- This project implements basic preprocessing operations for learning purposes.
- It does not support every feature of the standard C preprocessor.
- Complex conditional preprocessing directives are not fully implemented.
- Recursive macro expansion and advanced macro operations are not fully supported.
- System header processing may produce unprocessed header content.

## 9. Learning Outcomes

Through this project, I learned about:

- The basic concept of C preprocessing.
- Working with source and header files.
- File handling using C.
- String processing and pointers.
- Modular programming using multiple C files.
- Compilation using a Makefile.

## 10. Conclusion

The Mini C Preprocessor demonstrates the basic concepts of preprocessing in C through comment removal, file inclusion, and macro substitution.

It provides practical learning experience in C programming, file handling, and modular program development.
