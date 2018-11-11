#ifndef TREE_H
#define TREE_H
#include <set>
#include <string>
#include "node.h"

class Tree { 
    private:
        Node *rootNode;

    public:
        Tree();

    private:
        void addNodeRecursiveBody(Node* node, std::string value); 
        std::string getSpacesFromInt(int numberOfSpaces);
        std::string getStringFromSet(std::set<std::string> valuesSet);
        void preOrderRecursiveBody(Node* node, std::ofstream &outputFile, int level);
        void inOrderRecursiveBody(Node* node, std::ofstream &outputFile, int level);
        void postOrderRecursiveBody(Node* node, std::ofstream &outputFile, int level);

    public:
        void buildTree(std::string value);
        void traversePostorder(std::ofstream &outputFile);
        void traverseInorder(std::ofstream &outputFile);
        void traversePreorder(std::ofstream &outputFile);
};

#endif