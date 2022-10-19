#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "HuffmanTreeBase.hpp"
#include "priorityQueue.hpp"


class Huffman : HuffmanTreeBase {
    public:
    HuffmanNode* root;
    std::string compress(const std::string inputStr);
    std::string serializeTree();
    std::string decompress(const std::string inputCode, const std::string serializedTree);
    private:

};


#endif