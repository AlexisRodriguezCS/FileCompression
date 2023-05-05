//
// STARTER CODE: util.h
//
// TODO Write your own header
//

#pragma once

typedef hashmap hashmapF;
typedef unordered_map <int, string> hashmapE;

struct HuffmanNode {
    int character;
    int count;
    HuffmanNode* zero;
    HuffmanNode* one;
};

//
// This method frees the memory allocated for the Huffman tree.
//
void freeTree(HuffmanNode* node) {
    
    // TO DO:  Write this function.
    
}

//
// This function build the frequency map.  If isFile is true, then it reads
// from filename.  If isFile is false, then it reads from a string filename.
//
//
void buildFrequencyMap(string filename, bool isFile, hashmapF &map) {
    
    // TO DO:  Write this function.
    
}

//
// This function builds an encoding tree from the frequency map.
//
HuffmanNode* buildEncodingTree(hashmapF &map) {
    
    // TO DO:  Write this function.
    
    return nullptr;  // TO DO: update this return
}

//
// Recursive helper function for building the encoding map.
//
void _buildEncodingMap(HuffmanNode* node, hashmapE &encodingMap, string str, HuffmanNode* prev) {
    
    // TO DO:  Write this function.
    
}

//
// This function builds the encoding map from an encoding tree.
//
hashmapE buildEncodingMap(HuffmanNode* tree) {
    hashmapE encodingMap;
    
    // TO DO:  Write this function.
    
    return encodingMap;
}

//
// This function encodes the data in the input stream into the output stream
// using the encodingMap.  This function calculates the number of bits
// written to the output stream and sets result to the size parameter, which is
// passed by reference.  This function also returns a string representation of
// the output file, which is particularly useful for testing.
//
string encode(ifstream& input, hashmapE &encodingMap, ofbitstream& output,
              int &size, bool makeFile) {
    
    // TO DO:  Write this function.
    
    return "";
}


//
// This function decodes the input stream and writes the result to the output
// stream using the encodingTree.  This function also returns a string
// representation of the output file, which is particularly useful for testing.
//
string decode(ifbitstream &input, HuffmanNode* encodingTree, ofstream &output) {
    
    // TO DO:  Write this function.
    
    return "";
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
    
    // TO DO:  Write this function.
    
    return "";
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
    
    // TO DO:  Write this function.
    
    return "";
}