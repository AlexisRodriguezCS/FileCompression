<a name="readme-top"></a>

<p align="center">
  <img src="https://raw.githubusercontent.com/AlexisRodriguezCS/FileCompression/main/Images/Files.jpg" alt="Grid" style="display:block;margin:auto;" height="500">
</p>
<h1 align="center">File Compression</h1>

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

Here's an online demo of the project hosted on [repl.it](https://replit.com/@Alexisrz/FileCompression) for you to try out.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- GETTING STARTED -->
<a name="getting-started"></a>
## Getting Started

To set up a project locally, follow these simple steps.

### Prerequisites

_Software used to run the program._
* [Visusal Studio Code](https://code.visualstudio.com/)

* [MinGW](https://sourceforge.net/projects/mingw/)

* [Git](https://git-scm.com/)

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

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- USAGE -->
<a name="usage"></a>
## Usage

`Welcome to the file compression app!`

`1.  Build character frequency map`

`2.  Build encoding tree`

`3.  Build encoding map`

`4.  Encode data`

`5.  Decode data`

`6.  Free tree memory`



`C.  Compress file`

`D.  Decompress file`



`B.  Binary file viewer`

`T.  Text file viewer`

`Q.  Quit`



`Enter choice: `
<br>
Put Commands examples

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTACT -->
<a name="contact"></a>
## Contact

Alexis Rodriguez - [LinkedIn](https://www.linkedin.com/in/alexisrodriguezcs/) - alexisrodriguezdev@gmail.com

Project Link: [https://github.com/AlexisRodriguezCS/FileCompression](https://github.com/AlexisRodriguezCS/FileCompression)

<p align="right">(<a href="#readme-top">back to top</a>)</p>
