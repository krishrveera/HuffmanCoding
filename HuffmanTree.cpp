
#include "HuffmanTree.hpp"
#include <iostream>
#include <sstream>
#include "HeapQueue.hpp"
#include "Deque.hpp"
#include <assert.h>  

Huffman::Huffman() {}

std::string Huffman::find(char a) {
    return this->pFind(a, "", this->root);
}

/**
 * @brief Recursive function to return the path to a character on the tree
 * 
 * @param a 
 * @param path 
 * @param curr 
 * @return std::string 
 */
std::string Huffman::pFind(char a, std::string path, HuffmanNode* curr) {
    if (curr->getCharacter() == a) {
        return path;
    }
    else if (curr->isBranch()) {
        return pFind(a, path+"1", curr->right) + pFind(a, path+"0", curr->left); // recursive element that gives a 1 when it heads to the right and a 0 when it heads to the left
    }
    else {
        return "";
    }
}

/**
* @brief finds a key 
*
* @param hmk
* @param key
*/

HuffmanKey::iterator find_key(HuffmanKey& hmk, char key) {
    for (auto pair = hmk.begin(); pair != hmk.end(); ++pair ) {
        if (pair->first == key)
            return pair; // returns the corresponding pair to the key being identified as the for loop loops through the hmk vector
    }
    return hmk.end();
}

/**
*@brief compresses the string inputted and returns a 
*
*@param std::string inputStr
*/


std::string Huffman::compress(const std::string inputStr) {
    std::map<char, size_t> s = this->parse(inputStr); 
    HeapQueue<HuffmanNode*, HuffmanNode::Compare> pq;
    for (auto pair = s.begin(); pair != s.end(); ++pair ) {
        pq.insert(new HuffmanNode(pair->first, pair->second)); // inserts a new HuffmanNode in the priority queue 
        std::cout<< pair->first << ": " << pair->second << ";"; // prints out the values in the node given above
    }

    std::map<char, std::string> bit_keys; 
    while(pq.size() > 1) {
        // std::cout<<pq<<std::endl;
        HuffmanNode* l = pq.min();
        pq.removeMin();
        HuffmanNode* r = pq.min();
        pq.removeMin(); 
        HuffmanNode * p = new HuffmanNode('\0', l->getFrequency() + r->getFrequency()); // the new huffman node of the summed frequency of the two characters of the lowest frequency is being added back to the huffman tree after removing the said characters
        p->left = l; p->right = r; r->parent = p; l->parent = p; // a branch is being created of the two characters with the lowest frequency 
        if(bit_keys.find(r->getCharacter()) == bit_keys.end()) // ?
            bit_keys[r->getCharacter()] = ""; // ?
        if(bit_keys.find(l->getCharacter()) == bit_keys.end()) // ?
            bit_keys[l->getCharacter()] = ""; // ?
          
        populate_bit_keys(bit_keys, "0", l); // bit_keys is being populated with a 0 since the character was alloted the left branch
        populate_bit_keys(bit_keys, "1", r); // bit_keys is being populated with a 1 since the character was alloted the right branch

        pq.insert(p); // the parent node is being added to the priority queue
    }

    this->root = pq.min(); // ?
    std::string returnString; 
    // std::cout<<"\n\nCodes:::";
    // for (auto& pair : bit_keys) {
    //     std::cout<< pair.first << ": " << pair.second << ";";
    // }
    std::cout<<'\n';
    for (int i=0; i<inputStr.length(); i++) {
        returnString+= bit_keys.find(inputStr[i])->second;
    }
    // delete pq;
    return returnString;
}

void Huffman::populate_bit_keys(std::map<char, std::string> &bit_keys, std::string dir, HuffmanNode* curr) {
    if (curr == nullptr) return;
    if (curr->isLeaf()) { // ?
        auto elem = bit_keys.find(curr->getCharacter());
        elem->second = dir + elem->second;
    }
    else { // ? I know this branches to the left or right if the current is detected not to be a leaf
        populate_bit_keys(bit_keys, dir, curr->left);
        populate_bit_keys(bit_keys, dir, curr->right);
    }
}


std::string Huffman::serializeTree() const {
    return p_serializeTree(this->root); 
}

std::string Huffman::p_serializeTree(HuffmanNode* const curr) const {
    if (curr->isLeaf()) {
        std::string s = "L";
        s+=curr->getCharacter(); 
        return s; // returns the character with a L if the current node is a leaf
    }
    else {
        return p_serializeTree(curr->left) + p_serializeTree(curr->right) + "B"; // returns the character with a B indicating that branching has occured
    }
}

/**
* @brief decompressing algorithm 
*
* @param inputCode fdeikjhwdb
* @param serializedTree dsvjhvbs
*/

std::string Huffman::decompress(const std::string inputCode, const std::string serializedTree) {
    Deque<HuffmanNode> nodeStack;

    for (int i = 0; i < serializedTree.size(); i++) {
        if (serializedTree[i] == 'B') {
            HuffmanNode* right = nodeStack.popLeft();
            HuffmanNode* left = nodeStack.popLeft(); // both are pop left since we are decompressing the serialized tree from left to right
            HuffmanNode* parent = new HuffmanNode('\0', 0, nullptr, left, right);
            right->parent = parent; left->parent = parent;
            nodeStack.pushLeft(parent);
        }
        else { //"L{Char}"
            i++;
           nodeStack.pushLeft(new HuffmanNode(serializedTree[i], 0));// this is when the serialized tree indicates that we have reached a leaf
        }
    }

    this->root = nodeStack.popLeft();

    #ifdef DEBUG
    assert(nodeStack.isEmpty()); // ? what is assert?
    #endif

    #ifdef DEBUG
    assert(this->serializeTree() == serializedTree); // ?
    #endif
    
    // decompressing logic when to go right and left
    std::string returnString = "";
    HuffmanNode* curr = this->root;
    for (int i =0; i < inputCode.size(); i++) {
        if (inputCode[i] == '1') {
                curr = curr->right;
            }
        else if(inputCode[i]=='0') {
                curr = curr->left;
        }
        if (curr->isLeaf()) {
            returnString+= curr->getCharacter();
            curr = this->root;
        }
    }

    #ifdef DEBUG
    std::cout<< returnString<<std::endl;
    assert(curr == this->root); // ?
    #endif

    if (curr->isLeaf()) {
        returnString+= curr->getCharacter();
    }  // ?
    

    return returnString;
}

/**
* @brief creates a frequency map for a character
*
* @param inStr
*/

std::map<char, size_t> Huffman::parse(const std::string inStr) {
    std::map<char, size_t> freqParser;
    for (int i = 0; i < inStr.size(); i++) {
        auto elem =  freqParser.find(inStr[i]);
        if (elem != freqParser.end()) {
            elem->second ++;
        }
        else {
            freqParser[inStr[i]] = 1;
        }
    }
    return freqParser;
}