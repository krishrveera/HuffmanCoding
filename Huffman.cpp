
#include "Huffman.cpp"
#include <map>

std::string Huffman::compress(const std::string inputStr) {
    std::map<char, size_t> s = this->parse(inputStr);
    HuffmanPQ pq;
    for (auto& pair : s) {
        pq.pushRight(new LinkedHuffmanNode(pair.first, pair.second));
    }

    std::map<char, std::string> bit_keys;
    while(pq.getLength() > 1) {
        LinkedHuffmanNode* l = pq.pop();
        LinkedHuffmanNode* r = pq.pop();
    
        LinkedHuffmanNode * p = new LinkedHuffmanNode('\0', l->getFrequency() + r->getFrequency()); 
        p->left = l; p->right = r; r->parent = p; l->parent = p;
        if(bit_keys.find(r->getCharacter()) == bit_keys.end()) 
            bit_keys[r->getCharacter()] = "";
        if(bit_keys.find(l->getCharacter()) == bit_keys.end()) 
            bit_keys[l->getCharacter()] = "";
          
        populate_bit_keys(&bit_keys, "0", l);
        populate_bit_keys(&bit_keys, "1", r);

        pq.pushRight(p);
    }

    LinkedHuffmanNode* root = pq.pop();
    std::string returnString;

    for (int i=0; i<inputStr.length(); i++) {
        returnString+= bit_keys[inputStr[i]];
    }
    return inputString;
}

void populate_bit_keys(std::map<char, std::string> &bit_keys, std::string dir, LinkedHuffNode* curr) {
    if (curr == nullptr) return;
    if (curr->isLeaf()) {
        auto elem = bit_keys.find(curr->getCharacter());
        elem->second = dir + elem->second;
    }
    else {
        populate_bit_keys(&bit_keys, dir, curr->left);
        populate_bit_keys(&bit_keys, dir, curr->right);
    }
}


std::string Huffman::serializeTree() {
    return "";
}

std::string Huffman::decompress(const std::string inputCode, const std::string serializedTree) {
    n := serializedTree.length
    for i := 0 to n 
        current = inputCode
        while current.left() != nullptr && current.right() != nullptr
            if serializedTree[i] == 0 
                current = current.left();
            else    
                current = current.right();
            endif
            i++;
        endwhile
        print current.symbol    
    return "";
}


std::map<char, size_t> parse(const std::string inStr) {
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