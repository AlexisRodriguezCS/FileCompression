<a name="readme-top"></a>

<p align="center">
  <img src="https://raw.githubusercontent.com/AlexisRodriguezCS/FileCompression/main/Images/Files.jpg" alt="Grid" style="display:block;margin:auto;" height="500">
</p>

<h1 align="center" style="font-size: 58px;">File Compression</h1>

<!-- TABLE OF CONTENTS -->
<p align="center">
  <a href="#about">About The Project</a> •
  <a href="#getting-started">Getting Started</a> •
  <a href="#usage">Usage</a> •
  <a href="#Contact">Contact</a>
</p>

<!-- ABOUT THE PROJECT -->

<a name="about"></a>

## About The Project

This C++ program is designed to perform file compression and decompression using the Hoffman Coding technique. It employs a priority queue, which is implemented as a custom binary search tree and a hashmap. Nodes within the binary search tree are organized by priority, allowing for efficient compression and decompression of files. When nodes have the same priority, they are linked as a linked list.

The program functions as a file/string compression algorithm, providing the ability to compress and decompress files using the Huffman algorithm. It utilizes binary trees to encode and decode the data, while the priority queue determines the order in which the data is processed. The program's use of binary trees and priority queues allows it to provide an efficient and effective compression algorithm.

One notable feature of this program is its use of a custom priority queue. By implementing the priority queue as a binary search tree and hashmap.h file, the program is able to accommodate nodes with the same priority. This allows for more efficient compression and decompression of files, as the program can group nodes with the same priority together in the tree.

Overall, this C++ program provides a powerful implementation of the Hoffman Coding technique for file compression and decompression. It makes use of a custom priority queue that's implemented as a binary search tree and hashmap.h file, allowing for efficient grouping of nodes with the same priority. The program is a valuable tool for anyone who needs to compress and decompress files or strings, providing an efficient and effective compression algorithm.

> My partner and I were provided with main.cpp, hashmap.cpp, and bitsream.h, however, we successfully designed and implemented util.h and priorityqueue.h to complement the existing code, demonstrating our ability to expand upon and enhance pre-existing software.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- GETTING STARTED -->

<a name="getting-started"></a>

## Getting Started

To set up a project locally, follow these simple steps.

### Prerequisites

_Software used to run the program._

- [Visusal Studio Code](https://code.visualstudio.com/)

- [MinGW](https://sourceforge.net/projects/mingw/)

- [Git](https://git-scm.com/)

### Installation

_Here's how to install and set up the program._

From your command line:

```bash
# Clone this repository
$ git clone https://github.com/AlexisRodriguezCS/FileCompression.git

# Go into the repository
$ cd FileCompression

# Compile code into an executable
$ make build

# Run the program
$ make run
```

Here's an online demo of the project hosted on [repl.it](https://replit.com/@Alexisrz/FileCompression) for you to try out. To run the demo, make sure to execute the 'make build' and 'make run' commands in the repl.it console.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- USAGE -->

<a name="usage"></a>

## Usage

When the "make run" command is executed, it displays the following output and awaits user input.

<br>

`Welcome to the file compression app!`

`1.  Build character frequency map`

`2.  Build encoding tree`

`3.  Build encoding map`

`4.  Encode data`

`5.  Decode data`

`6.  Free tree memory`

<br>

`C.  Compress file`

`D.  Decompress file`

<br>

`B.  Binary file viewer`

`T.  Text file viewer`

`Q.  Quit`

<br>

`Enter choice: `

<br>

> Below is a list of every command available in the program along with a brief description of what each command does and its requirements:

<br>

| Command                          | Description and Requirements                                                                                   |
| -------------------------------- | -------------------------------------------------------------------------------------------------------------- |
| 1. Build character frequency map | Generates a map of character frequencies in the data.                                                          |
| 1a. [F]ile or [S]tring           | Please specify the input type by entering "F" for file or "S" for string.                                      |
| 2. Build encoding tree           | Constructs an encoding tree based on the character frequency map.                                              |
| 3. Build encoding map            | Creates an encoding map using the encoding tree.                                                               |
| 4. Encode data                   | Encodes the data using the encoding map. Requires an existing encoding map.                                    |
| 5. Decode data                   | Decodes the data using the encoding map. Requires an existing encoding map.                                    |
| 6. Free tree memory              | Releases memory occupied by the encoding tree.                                                                 |
| C. Compress file                 | Compresses a file using the encoding map. Requires an existing encoding map and the file to be compressed.     |
| D. Decompress file               | Decompresses a file using the encoding map. Requires an existing encoding map and the file to be decompressed. |
| B. Binary file viewer            | Displays the content of a binary file. Requires the binary file to be viewed.                                  |
| T. Text file viewer              | Displays the content of a text file. Requires the text file to be viewed.                                      |
| Q. Quit                          | Exits the program.                                                                                             |

The following is the program output generated when executed with the input file "example.txt".

Command 1:

`Enter choice: 1`<br>
`[F]ilename or [S]tring? F`<br>
`Enter file name: example.txt`<br>

`Building frequency map...`<br>
`98:       'b' --> 3`<br>
`99:       'c' --> 1`<br>
`97:       'a' --> 3`<br>
`32:       ' ' --> 2`<br>
`256:      EOF --> 1`<br>

Command 2:

`{N/A, count=10}`<br>
`{N/A, count=4}`<br>
`{' '(32), count=2}`<br>
`{N/A, count=2}`<br>
`{'c'(99), count=1}`<br>
`{EOF(256), count=1}`<br>
`{N/A, count=6}`<br>
`{'b'(98), count=3}`<br>
`{'a'(97), count=3}`<br>

Command 3:

`Building encoding map...`<br>
`98:     'b' --> 10`<br>
`256:    EOF --> 011`<br>
`99:     'c' --> 010`<br>
`97:     'a' --> 11`<br>
`32:     ' ' --> 00`<br>

Command 4:

`Encoding...`<br>
`Compressed file size: 34`<br>
`1110001110000101110011`<br>

Command 5:

`Decoding...`<br>
`ab ab cab`<br>

Command 6:

`Freeing encoding tree...`

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTACT -->

<a name="contact"></a>

## Contact

Alexis Rodriguez - [LinkedIn](https://www.linkedin.com/in/alexisrodriguezcs/) - alexisrodriguezdev@gmail.com

Project Link: [https://github.com/AlexisRodriguezCS/FileCompression](https://github.com/AlexisRodriguezCS/FileCompression)

<p align="right">(<a href="#readme-top">back to top</a>)</p>
