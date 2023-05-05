/*
util.h
Alexis Rodriguez, Daniela Nieto
arodr247, 
CS 251
Project 6 - File Compression
Description: This program is a file/string compression algorithm that allows to compress and decompress files using the a Huffman algorithm. It implements binary trees and priority queues
*/
#pragma once
#include "bitstream.h"
#include "hashmap.h"
#include "priorityqueue.h"
typedef hashmap hashmapF;
typedef unordered_map<int, string> hashmapE;

struct HuffmanNode {
  int character;
  int count;
  HuffmanNode* zero;
  HuffmanNode* one;
};

// Helper function to delete nodes in tree in a post-order traversal
void _freeTree(HuffmanNode* node) {
  if (node == nullptr) {
  	// Base case
    return;
  } else {
  	// frees the right
    _freeTree(node->one);
    // frees the left
    _freeTree(node->zero);
    delete node;
  }
}

//
// This method frees the memory allocated for the Huffman tree.
//
void freeTree(HuffmanNode* node) { _freeTree(node); }

//
// Helper function for buildEncodingMap used to first check if the value
// is in the map. If the asciiValue is in the map then we update the count. If
// the value is not in the map then we just make a new pair and set count to 1.
//
void addToMap(hashmapF& map, char input) {
  int asciiValue = input;
  // checking in the asciiValue value is in the map
  if (map.containsKey(asciiValue)) {
    // get the count of the asciiValue
    int count = map.get(asciiValue);
    // then we update the count by 1
    map.put(asciiValue, count + 1);
  } else {
    // not in the map, update count to 1
    map.put(asciiValue, 1);
  }
}

//
// This function build the frequency map.  If isFile is true, then it reads
// from filename.  If isFile is false, then it reads from a string filename.
//
//
void buildFrequencyMap(string filename, bool isFile, hashmapF& map) {
  // if filename is a file
  if (isFile) {
    ifstream infile;
    infile.open(filename);
    char input;
    while (infile.get(input)) {
      // read in all the chars one by one from the file
      addToMap(map, input);
    }
    infile.close();
  } else {
    // the filename is a string
    for (char& c : filename) {
      // go through the string and add every char to the map
      addToMap(map, c);
    }
  }
  // return a map containing only the 1 occurrence of PSEUDO_EOF
  map.put(PSEUDO_EOF, 1);
}

//
// helper function that gets two nodes and deletes them after setting
// the newNode left and right children using the two deleted nodes
//
void _buildEncodingTree(priorityqueue<HuffmanNode*>& pq, HuffmanNode*& root) {
  while (pq.Size() > 1) {
    // Deque for first node
    HuffmanNode* zero = pq.dequeue();
    // Deque for second node
    HuffmanNode* one = pq.dequeue();
    // Create new node that will hold first and second node
    HuffmanNode* newNode = new HuffmanNode();
    newNode->character = NOT_A_CHAR;
    newNode->count = zero->count + one->count;
    newNode->zero = zero;
    newNode->one = one;

    // Add new node
    pq.enqueue(newNode, newNode->count);
    if (pq.Size() == 1) {
      root = newNode;
    }
  }
}

//
// This function builds an encoding tree from the frequency map.
//
HuffmanNode* buildEncodingTree(hashmapF& map) {
  priorityqueue<HuffmanNode*> pq;
  // check if the map is not empty
  if (map.size() > 0) {
    // get the keys from the map
    vector<int> allKeys = map.keys();
    // for every key in the vector
    for (auto& key : allKeys) {
      HuffmanNode* newNode = new HuffmanNode();
      // HuffmanNode* newNode = nullptr;
      newNode->character = key;
      // get the current counter for this key
      int counter = map.get(key);
      newNode->count = counter;
      // add newNode to the priorityqueue
      pq.enqueue(newNode, counter);
    }
    // set curr to the most left node in priorityqueue
    // call helper to build the encodingTree
    HuffmanNode* root = nullptr;
    _buildEncodingTree(pq, root);
    return root;
  } else {
    return nullptr;
  }
}

//
// Recursive helper function for building the encoding map.
//
void _buildEncodingMap(HuffmanNode* node, hashmapE& encodingMap, string str,
                       HuffmanNode* prev) {
  if (node->character != NOT_A_CHAR) {
    // at the leaft node add for example: 256: EOF --> 1100
    encodingMap[node->character] = str;
    return;
  } else {
    // traversal
    _buildEncodingMap(node->zero, encodingMap, str + "0", node);
    _buildEncodingMap(node->one, encodingMap, str + "1", node);
  }
}

//
// This function builds the encoding map from an encoding tree.
//
hashmapE buildEncodingMap(HuffmanNode* tree) {
  hashmapE encodingMap;
  if (tree == nullptr) {
    return encodingMap;
  }
  string str = "";
  _buildEncodingMap(tree, encodingMap, str, nullptr);
  return encodingMap;
}
//
// This function encodes the data in the input stream into the output stream
// using the encodingMap.  This function calculates the number of bits
// written to the output stream and sets result to the size parameter, which is
// passed by reference.  This function also returns a string representation of
// the output file, which is particularly useful for testing.
//
string encode(ifstream& input, hashmapE& encodingMap, ofbitstream& output,
              int& size, bool makeFile) {
  char c;
  string encodingStr = "";

  while (input.get(c)) {
    // Read one char at once
    int cToi = c;
    // Add to encoding string using encoding map
    encodingStr += encodingMap[cToi];
  }
  // Add end of file
  encodingStr += encodingMap[PSEUDO_EOF];
  // Make file
  if (makeFile) {
    for (auto& c : encodingStr) {
      output.writeBit(c - '0');
    }
  }
  // Update size
  size = encodingStr.length();
  // return string with encoding
  return encodingStr;
}

//
// This function decodes the input stream and writes the result to the output
// stream using the encodingTree.  This function also returns a string
// representation of the output file, which is particularly useful for testing.
//
string decode(ifbitstream& input, HuffmanNode* encodingTree, ofstream& output) {
  HuffmanNode* curr = encodingTree;
  string decodingStr = "";
  int c = input.readBit();
  while (c != EOF) {
    if (c == 0) {
    	// goes left
      curr = curr->zero;
    } else {
    	// goes right
      curr = curr->one;
    }
    if (curr->character != NOT_A_CHAR) {
      if (curr->character == PSEUDO_EOF) {
      	// at the end of the file
        break;
      }
      // update the string
      decodingStr += (char)(curr->character);
      curr = encodingTree;
    }
    c = input.readBit();
  }
  // write to the output
  output << decodingStr;
  return decodingStr;
}

//
// This function completes the entire compression process.  Given a file,
// filename, this function (1) builds a frequency map; (2) builds an encoding
// tree; (3) builds an encoding map; (4) encodes the file (don't forget to
// include the frequency map in the header of the output file).  This function
// should create a compressed file named (filename + ".huf") and should also
// return a string version of the bit pattern.
//
string compress(string filename) {
  // Step 1
  hashmapF frequencyMap;
  buildFrequencyMap(filename, true, frequencyMap);
  // Step 2
  HuffmanNode* encodingTree = nullptr;
  encodingTree = buildEncodingTree(frequencyMap);
  // Step 3
  hashmapE encodingMap;
  encodingMap = buildEncodingMap(encodingTree);
  // Step 4
  ifstream input(filename);
  ofbitstream output(filename + ".huf");
  output << frequencyMap;  // add the frequency map to the file
  int size = 0;
  string codeStr = encode(input, encodingMap, output, size, true);
  freeTree(encodingTree);
  return codeStr;
}

//
// This function completes the entire decompression process.  Given the file,
// filename (which should end with ".huf"), (1) extract the header and build
// the frequency map; (2) build an encoding tree from the frequency map; (3)
// using the encoding tree to decode the file.  This function should create a
// compressed file using the following convention.
// If filename = "example.txt.huf", then the uncompressed file should be named
// "example_unc.txt".  The function should return a string version of the
// uncompressed file.  Note this function should reverse what the compress
// function did.
//
string decompress(string filename) {
  // Get file name and extension
  size_t pos = filename.find(".huf");
  if ((int)pos >= 0) {
    filename = filename.substr(0, pos);
  }
  pos = filename.find(".");
  string ext = filename.substr(pos, filename.length() - pos);
  filename = filename.substr(0, pos);

  ifbitstream input(filename + ext + ".huf");
  ofstream output(filename + "_unc" + ext);
  // Step 1
  hashmapF frequencyMap;
  input >> frequencyMap;
  // Step 2
  HuffmanNode* encodingTree = nullptr;
  encodingTree = buildEncodingTree(frequencyMap);
  // Step 3
  string decodeStr = decode(input, encodingTree, output);
  freeTree(encodingTree);
  return decodeStr;
}