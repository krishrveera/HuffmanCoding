#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "HuffmanBase.hpp"
#include "priorityQueue.hpp"
#include <vector>
#include <sstream>
#include <map>
#include <tuple>
#include <string>

typedef std::vector<std::pair<char, size_t>> HuffmanKey;

class Huffman : HuffmanTreeBase {
    private:
    std::string pFind(char a, std::string path, HuffmanNode* curr);
    std::string find(char a);
    std::string p_serializeTree(HuffmanNode* const curr) const;
    std::map<char, size_t> parse(const std::string inStr);
void populate_bit_keys(std::map<char, std::string> &bit_keys, std::string dir, HuffmanNode* curr);
    public:
    HuffmanNode* root;
    Huffman();
    std::string compress(const std::string inputStr);
    std::string serializeTree() const;
    std::string decompress(const std::string inputCode, const std::string serializedTree);
};


#endif