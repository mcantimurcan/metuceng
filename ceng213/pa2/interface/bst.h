#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;

// do not add any other library.
// modify parts as directed by assignment text and comments here.

template <class T>
class BST {
private:
    // Define TreeNode for the second phase (Binary Search Tree)
    /* DO NOT CHANGE */
    struct TreeNode {
        std::string key;
        T data;
        TreeNode* left;
        TreeNode* right;
        TreeNode(const std::string &k, const T& value) : key(k), data(value), left(NULL), right(NULL) {}
        
    };

    TreeNode* root;


public: // Do not change.

    BST();
    ~BST();
    TreeNode* getRoot() { return root; }
    bool isEmpty() { return root == NULL; }

    BST& insert(const std::string key, const T& value);
    bool search(std::string value) const;
    void remove(std::string value);
    BST<T>* merge(BST<T>* bst);
    BST<T>* intersection(BST<T>* bst);
    std::vector<TreeNode> tree2vector(TreeNode* root);
    void tree2vector(TreeNode* node, vector<TreeNode>& result);
    void print();
    
private:// you may add your own utility member functions here.

    void print(TreeNode* node, std::string indent, bool last, bool isLeftChild); // Do not change.
    void deleteTreeNode(TreeNode* root);// Do not change.
    void insertHelper(TreeNode* &node, const string key, const T &data);
    void removeHelper(TreeNode *& root, std::string key); 
    std::string getMin(TreeNode* root);
    void mergeNodes(const vector<typename BST<T>::TreeNode>& nodes1, const vector<typename BST<T>::TreeNode>& nodes2,
                    vector<typename BST<T>::TreeNode>& mergedNodes);
    void findCommonNodes(const vector<typename BST<T>::TreeNode>& nodes1, const vector<typename BST<T>::TreeNode>& nodes2,
                          vector<typename BST<T>::TreeNode>& commonNodes);
};

    // Constructor
    template <class T>
    BST<T>::BST() : root(NULL) {}

    // Destructor
    template <class T>
    BST<T>::~BST() {
        deleteTreeNode(root);
    }

    // Insert function for BST.    
    template <class T>
    BST<T>& BST<T>::insert(const string key, const T& value) {
        insertHelper(root, key, value);
        return *this;
    }
    
    // Search function for BST.
    template <class T>
    bool BST<T>::search(std::string value) const {
        TreeNode* crawl = root;
        while(crawl){
            if(crawl -> key < value){
                crawl = crawl -> left;
            } else if (crawl -> key > value){
                crawl = crawl -> right;
            } else if (crawl -> key == value) {
                return true;
            }
        }
        return false;
    }
    
    // Remove a node from BST for given key. If key not found, do not change anything.
    template <class T>
    void BST<T>::remove(std::string key) {
        removeHelper(root, key);
    }
    
    // A helper function for converting a BST into vector.
    template <class T>
    vector<typename BST<T>::TreeNode> BST<T>::tree2vector(TreeNode* root) {
        vector<TreeNode> result;
        tree2vector(root, result);
        return result;
    }
    
    template <class T>
    void BST<T>::tree2vector(TreeNode* node, vector<TreeNode>& result){
        if (node != NULL) {
            tree2vector(node -> left, result);
            result.push_back(*node);
            tree2vector(node -> right, result);
        }
    }
    
    // Merge two BST's and return merged BST.
    template <class T>
    BST<T>* BST<T>::merge(BST<T>* bst) {
        vector<TreeNode> bst1Nodes = tree2vector(root);
        vector<TreeNode> bst2Nodes = tree2vector(bst->getRoot());
        vector<TreeNode> mergedNodes;

        mergeNodes(bst1Nodes, bst2Nodes, mergedNodes);

        BST<T>* mergedBST = new BST<T>();

        int mergedSize = mergedNodes.size();

        for (int i = 0; i < mergedSize; i++) {
            mergedBST->insert(mergedNodes[i].key, mergedNodes[i].data);
        }
    
        return mergedBST;
    }
        
    // Intersect two BST's and return new BST.
    template <class T>
    BST<T>* BST<T>::intersection(BST<T>* bst) {
        vector<TreeNode> bst1Nodes = tree2vector(root);
        vector<TreeNode> bst2Nodes = tree2vector(bst->getRoot());
        vector<TreeNode> commonNodes;

        findCommonNodes(bst1Nodes, bst2Nodes, commonNodes);

        BST<T>* intersectionBST = new BST<T>();
    
        int commonSize = commonNodes.size();

        for(int i = 0; i < commonSize; i++) {
            intersectionBST->insert(commonNodes[i].key, commonNodes[i].data);
        }
        return intersectionBST;
    }
    
    
    // Helper Functions
    template <class T>
    void BST<T>::removeHelper(TreeNode *&root, std::string key){
        if (root == NULL){
            return;
        } else if (root -> key > key){
            removeHelper(root->left, key);
        } else if (root -> key < key){
            removeHelper(root->right , key);
        } else {
            if (root -> left != NULL && root -> right != NULL) {
                root -> key = getMin(root -> right);
                removeHelper(root -> right, root -> key);
            } else {
                TreeNode * oldNode =root;
                root = (root -> left != NULL) ? root -> left : root -> right;
                delete oldNode;
            }
        }
    }
    
    template <class T>
    void BST<T>::insertHelper(TreeNode* &node, const string key, const T &data) {
        if (node == NULL) {
            node = new TreeNode(key, data);
        } else if (key < node -> key) {
            insertHelper(node -> left, key, data);
        } else if (key > node -> key) {
            insertHelper(node -> right, key, data);
        }
    }
    
    template <class T>
    void BST<T>::mergeNodes(const vector<typename BST<T>::TreeNode>& nodes1, const vector<typename BST<T>::TreeNode>& nodes2,
                    vector<typename BST<T>::TreeNode>& mergedNodes) {
        int i = 0, j = 0;
        int size1 = nodes1.size();
        int size2 = nodes2.size();
    
        while (i < size1 && j < size2) {
            if (nodes1[i].key < nodes2[j].key) {
                mergedNodes.push_back(nodes1[i]);
                i++;
            } else {
                mergedNodes.push_back(nodes2[j]);
                j++;
            }
        }
        while (i < size1) {
            mergedNodes.push_back(nodes1[i]);
            i++;
        }
        while (j < size2) {
            mergedNodes.push_back(nodes2[j]);
            j++;
        }
    }
    
    template <class T>
    void BST<T>::findCommonNodes(const vector<typename BST<T>::TreeNode>& nodes1, const vector<typename BST<T>::TreeNode>& nodes2,
                          vector<typename BST<T>::TreeNode>& commonNodes) {
        int i = 0, j = 0;
        int size1 = nodes1.size();
        int size2 = nodes2.size();
    
        while (i < size1 && j < size2) {
            if (nodes1[i].key == nodes2[j].key) {
                commonNodes.push_back(nodes1[i]);
                i++;
                j++;
            } else if (nodes1[i].key < nodes2[j].key) {
                i++;
            } else {
                j++;
            }
        }
    }
    
    template <class T>
    std::string BST<T>::getMin(TreeNode* root){
        if (root -> left == NULL){
            return root -> key;
        } else {
            return getMin(root -> left);
        }
    }
    
    template <class T>
    void BST<T>::deleteTreeNode(TreeNode* root) {
        if(root){
            deleteTreeNode(root -> right);
            deleteTreeNode(root -> left);
            delete root;
        }
    }
    
    /* DO NOT CHANGE */
    template <class T>
    void BST<T>::print() {
        print(root, "", true, false);
    
    }
    
    /* DO NOT CHANGE */
    template <class T>
    void BST<T>::print(TreeNode* node, string indent, bool last, bool isLeftChild) {
        if (node != NULL) {
            cout << node->key << endl;
            print(node->left, indent, false, true);
            print(node->right, indent, true, false);
        }
    
    }

#pragma once