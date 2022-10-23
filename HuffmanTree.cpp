
#include "HuffmanTree.hpp"
#include <iostream>
#include <sstream>
#include "HeapQueue.hpp"
#include "Deque.hpp"
#include <assert.h>  

#define DEBUG 1

Huffman::Huffman() {}

std::string Huffman::find(char a) {
    return this->pFind(a, "", this->root);
}

std::string Huffman::pFind(char a, std::string path, HuffmanNode* curr) {
    if (curr->getCharacter() == a) {
        return path;
    }
    else if (curr->isBranch()) {
        return pFind(a, path+"1", curr->right) + pFind(a, path+"0", curr->left);
    }
    else {
        return "";
    }
}

HuffmanKey::iterator find_key(HuffmanKey& hmk, char key) {
    for (auto pair = hmk.begin(); pair != hmk.end(); ++pair ) {
        if (pair->first == key)
            return pair;
    }
    return hmk.end();
}


std::string Huffman::compress(const std::string inputStr) {
    std::map<char, size_t> s = this->parse(inputStr);
    HeapQueue<HuffmanNode*, HuffmanNode::Compare> pq;
    for (auto pair = s.begin(); pair != s.end(); ++pair ) {
        pq.insert(new HuffmanNode(pair->first, pair->second));
        std::cout<< pair->first << ": " << pair->second << ";";
    }

    std::map<char, std::string> bit_keys;
    while(pq.size() > 1) {
        // std::cout<<pq<<std::endl;
        HuffmanNode* l = pq.min();
        pq.removeMin();
        HuffmanNode* r = pq.min();
        pq.removeMin();
        HuffmanNode * p = new HuffmanNode('\0', l->getFrequency() + r->getFrequency()); 
        p->left = l; p->right = r; r->parent = p; l->parent = p;
        if(bit_keys.find(r->getCharacter()) == bit_keys.end()) 
            bit_keys[r->getCharacter()] = "";
        if(bit_keys.find(l->getCharacter()) == bit_keys.end()) 
            bit_keys[l->getCharacter()] = "";
          
        populate_bit_keys(bit_keys, "0", l);
        populate_bit_keys(bit_keys, "1", r);

        pq.insert(p);
    }

    this->root = pq.min();
    std::string returnString;
    std::cout<<"\n\nCodes:::";
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
    if (curr->isLeaf()) {
        auto elem = bit_keys.find(curr->getCharacter());
        elem->second = dir + elem->second;
    }
    else {
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
        return s;
    }
    else {
        return p_serializeTree(curr->left) + p_serializeTree(curr->right) + "B";
    }
}

std::string Huffman::decompress(const std::string inputCode, const std::string serializedTree) {
    Deque<HuffmanNode> nodeStack;

    for (int i = 0; i < serializedTree.size(); i++) {
        if (serializedTree[i] == 'B') {
            HuffmanNode* right = nodeStack.popLeft();
            HuffmanNode* left = nodeStack.popLeft();
            HuffmanNode* parent = new HuffmanNode('\0', 0, nullptr, left, right);
            right->parent = parent; left->parent = parent;
            nodeStack.pushLeft(parent);
        }
        else { //"L{Char}"
            i++;
           nodeStack.pushLeft(new HuffmanNode(serializedTree[i], 0));
        }
    }

    this->root = nodeStack.popLeft();

    #ifdef DEBUG
    assert(nodeStack.isEmpty());
    #endif

    #ifdef DEBUG
    assert(this->serializeTree() == serializedTree);
    #endif
    
    std::string returnString = "";
    HuffmanNode* curr = this->root;
    for (int i =0; i < inputCode.size(); i++) {
        if (curr->isLeaf()) {
            returnString+= curr->getCharacter();
            curr = this->root;
        }
        else {
            if (inputCode[i] == '1') {
                curr = curr->right;
            }
            else if(inputCode[i]=='0') {
                curr = curr->left;
            }
        }
    }

    #ifdef DEBUG
    std::cout<< returnString<<std::endl;
    assert(curr == this->root);
    #endif

    if (curr->isLeaf()) {
        returnString+= curr->getCharacter();
    } 
    

    return returnString;
}


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