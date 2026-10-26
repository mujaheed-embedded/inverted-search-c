# Inverted Search in C

## 📌 Overview

Inverted Search is a C programming project that creates an index of words from multiple text files and allows users to search for words efficiently.

Instead of scanning every file for each search, the program builds an inverted index that maps words to the files in which they appear, along with their occurrence counts.

## ✨ Features

* **Create Database:** Build an index of words from multiple text files.
* **Search Database:** Search for a word and identify the files containing it.
* **Display Database:** Display indexed words and their associated file information.
* **Save Database:** Store the database in a file for later use.
* **Update Database:** Update the database using a saved database file.
* **File Handling:** Read and process multiple text files.
* **Dynamic Data Structures:** Organize indexed information using linked lists and hash tables.

## 🛠️ Technologies Used

* C Programming
* Data Structures and Algorithms
* Hash Tables
* Linked Lists
* File Handling
* Dynamic Memory Allocation
* Makefile and GCC

## 📂 Project Structure

```text
INVERTED_SEARCH_PROJECT/
├── create_database.c
├── create_index.c
├── display_database.c
├── search.c
├── save_database.c
├── update.c
├── free_all.c
├── main.c
├── inverted_search.h
├── makefile
├── file1.txt
├── file2.txt
├── file3.txt
├── file4.txt
└── f3.txt
```

## ⚙️ Compilation

Make sure GCC and Make are installed.

Compile the project using:

```bash
make
```

The Makefile compiles the source files and generates the executable `Inverter_search.exe`.

## ▶️ Execution

Run the executable using:

```bash
./Inverter_search.exe
```

## 🧹 Clean Build Files

To remove the generated object files and executable, run:

```bash
make clean
```

## 🧠 Concepts Practiced

* String processing and word indexing
* Hash table-based searching
* Linked-list operations
* File input and output
* Dynamic memory management
* Modular C programming
* Database creation, searching, saving, and updating

## 🎯 Objective

To strengthen practical knowledge of C programming and Data Structures and Algorithms by implementing a searchable word index across multiple text files.

## 👨‍💻 Author

**Mujaheed Ahmed**

GitHub: [mujaheed-embedded](https://github.com/mujaheed-embedded)
