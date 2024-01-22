#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;


template <class T>
class Trie {    
private:
    // Define TrieNode for the first phase (Trie)
    /* DO NOT CHANGE */
    struct TrieNode {
        static const int ALPHABET_SIZE = 128;
        TrieNode* children[ALPHABET_SIZE];
        char keyChar;
        bool isEndOfKey;
        T* data;

        TrieNode(char c) : keyChar(c), isEndOfKey(false), data(NULL) {

                for (int i = 0; i< ALPHABET_SIZE; i++) {
                children[i] = NULL;
                
            }
            
            }
    };

    TrieNode* root;

public: // Do not change.

    Trie(); 
    ~Trie();
    
    Trie& insert(const string& username); 
    void remove(std::string username);
    T* search(std::string username); 
    void findStartingWith(std::string prefix, std::vector<T*> &results); 
    void wildcardSearch(const std::string &wildcardKey, std::vector<T*> &results); 
    void print(); 

private: // you may add your own utility member functions here.
    void print(const std::string& primaryKey); // Do not change this line.
    void printTrie(TrieNode* node, const std::string& currentKey); // Do not change this line.
    void deleteTrieNode(TrieNode* node);
    void findStartingWithHelper(TrieNode* node, std::vector<T*> &results);
    void wildcardSearchHelper(TrieNode* node, const std::string &wildcardKey, std::vector<T*> &results);
};
/* DO NOT CHANGE */
template <class T>
Trie<T>::Trie() : root(new TrieNode('\0')) {}

template <class T>
Trie<T>::~Trie() {
    deleteTrieNode(root);
}

template <class T>
Trie<T>& Trie<T>::insert(const string& key) {
    TrieNode *crawl = root;
    for (int i = 0; i < key.length(); i++) {
        int index = static_cast<unsigned char>(key[i]);
        if (!crawl -> children[index]) {
            crawl -> children[index] = new TrieNode(key[i]);
        }
        crawl = crawl -> children[index];
    }
    crawl -> data = new T(key);
    crawl -> isEndOfKey = true;
    return *this;
}

template <class T>
T* Trie<T>::search(std::string username) {
    if(!root){
        return NULL;
    }
    TrieNode *crawl = root;
    for (int i = 0; i < username.length(); i++) {
        int index = static_cast<unsigned char>(username[i]);
        if (!crawl -> children[index]) {
            return NULL;
        }
        crawl = crawl -> children[index];
    }
    return crawl -> data;
}

template <class T>
void Trie<T>::remove(std::string username) {
    if(!root){
        return;
    }
    TrieNode *crawl = root;
    for (int i = 0; i < username.length(); i++) {
        int index = static_cast<unsigned char>(username[i]);
        if (!crawl -> children[index]) {
            return;
        }
        crawl = crawl -> children[index];
    }
    crawl -> isEndOfKey = false;
}

template <class T>
void Trie<T>::findStartingWith(std::string prefix, std::vector<T*> &results) {
    TrieNode* crawl = root;
    for(int i = 0; i < prefix.length(); i++){
        int index = static_cast<unsigned char>(prefix[i]);
        if (!crawl -> children[index]) {
            return;
        }
        crawl = crawl -> children[index];
    }
    findStartingWithHelper(crawl, results);
}

template <class T>
void Trie<T>::wildcardSearch(const std::string &wildcardKey, std::vector<T*> &results) {
    wildcardSearchHelper(root, wildcardKey, results);
}

// Helper Functions
template <class T>
void Trie<T>::deleteTrieNode(TrieNode* root) {
    if(!root){
        return;
    }
    for(int i = 0; i < TrieNode::ALPHABET_SIZE; i++){
        deleteTrieNode(root -> children[i]);
    }
    delete root -> data;
    delete root; 
}

template <class T>
void Trie<T>::findStartingWithHelper(TrieNode* node, std::vector<T*> &results){
    if (node == NULL){
        return;
    }
    if (node -> isEndOfKey && node -> data) {
        results.push_back(node -> data);
    }
    for(int i = 0; i < TrieNode::ALPHABET_SIZE; i++){
        if(node -> children[i]){
            findStartingWithHelper(node -> children[i], results);
        }
    }
}

template <class T>
void Trie<T>::wildcardSearchHelper(TrieNode* node, const std::string &wildcardKey, std::vector<T*> &results) {
    if (!node) {
        return;
    }
    if (wildcardKey.empty()) {
        if (node -> isEndOfKey && node -> data) {
            for(int i = 0; i < results.size(); i++){
                if(node -> data == results[i]){
                    return;
                }
            }
            results.push_back(node -> data);
        }
        return;
    }
    char currentChar = wildcardKey[0];
    if (currentChar == '*') {
        wildcardSearchHelper(node, wildcardKey.substr(1), results);
        for (int i = 0; i < TrieNode::ALPHABET_SIZE; i++) {
            if (node -> children[i]) {
                wildcardSearchHelper(node -> children[i], wildcardKey, results);
            }
        }
    } else if (currentChar == '?') {
        for (int i = 0; i < TrieNode::ALPHABET_SIZE; i++) {
            if (node -> children[i]) {
                wildcardSearchHelper(node -> children[i], wildcardKey.substr(1), results);
            }
        }
    } else {
        int index = static_cast<unsigned char>(currentChar);
        if (node -> children[index]) {
            wildcardSearchHelper(node -> children[index], wildcardKey.substr(1), results);
        }
    }
}

/* DO NOT CHANGE */
template<class T>
void Trie<T>::print() {
    print("");
}
/* DO NOT CHANGE */
template <class T>
void Trie<T>::print(const std::string& primaryKey) {
    if (primaryKey.empty()) {
        // Print the entire tree.
        printTrie(root, "");
    } else {
        // Print specific keys.
        TrieNode* primaryNode = root;
        for (int i = 0; i < primaryKey.length(); i++) {
            
            int index = primaryKey[i];
            if (!primaryNode->children[index]) {
                std::cout << "{}" << std::endl; // Primary key not found, nothing to print.
                return ;
            }
            primaryNode = primaryNode->children[index];
        }

        }
    }
/* DO NOT CHANGE */
template <class T>
void Trie<T>::printTrie(TrieNode* node, const std::string& currentKey) {
    if (!node) {
        return;
    }
    if (node->isEndOfKey) {
        std::cout << currentKey <<std::endl;
        std::cout << "Watched Movies:" << std::endl;
        if(node->data) {
            node->data->printMovies();
        }
    }
    for (int i = 0; i < 128; ++i) {
        if (node->children[i]) {
            printTrie(node->children[i], currentKey + static_cast<char>(i));
        }
    }
}


#pragma once