#include <string>
#include <set>
#include <stack>
#include <list>
#include <iostream>
#include <fstream>
#include "node.h"
#include "tree.h"
using namespace std; 

    //public:
    Tree::Tree() {
        this->rootNode = new Node();
    }

    //private:
    void Tree::addNodeRecursiveBody(Node* node, string value) {
        // cout << "Starting add new node recursion\n";
        if (value[0] > node->value[0]) {
            // cout << "New node is greater than current node\n";
            if (node->right == NULL) {
                // cout << "Current right node child is empty. Adding new right node.\n";
                node->right = new Node(value);
            } else {
                // cout << "Right node already present, continuing traversal.\n";
                addNodeRecursiveBody(node->right, value);
            }
        } else if (value[0] < node->value[0]) {
            // cout << "New node is less than current node\n";
            if (node->left == NULL) {
                // cout << "Current left node child is empty. Adding new left node.\n";
                node->left = new Node(value);
            } else {
                // cout << "Left node already present, continuing traversal.\n";
                addNodeRecursiveBody(node->left, value);
            }
        } else {
            // cout << "Current node is the same value as input.\n";
            set<string>::iterator it;
            it=node->valuesSet.find(value);
            if (it == node->valuesSet.end()) {
                node->valuesSet.insert(value);
            }
        }
        return;
    } 

    string Tree::getSpacesFromInt(int numberOfSpaces) {
        string spaceString;
        for(int i = 0; i < numberOfSpaces; i ++){
            spaceString = spaceString + " ";
        }
        return spaceString;
    }

    string Tree::getStringFromSet(set<string> valuesSet){
        string valuesSetString = "";
        set<string>::iterator it;
        for (it=valuesSet.begin(); it!=valuesSet.end(); ++it) {
            valuesSetString += *it + ' ';
        }
        return valuesSetString;
    }

    void Tree::preOrderRecursiveBody(Node* node, ofstream &outputFile, int level) { 
        if (node == NULL) {
            return; 
        }

        cout << getSpacesFromInt(level) << node->value << ": " << getStringFromSet(node->valuesSet) << "\n";
        outputFile << getSpacesFromInt(level) << node->value << ": " << getStringFromSet(node->valuesSet) << "\n";
        preOrderRecursiveBody(node->left, outputFile, ++level); 
        preOrderRecursiveBody(node->right, outputFile, ++level); 
    } 

    void Tree::inOrderRecursiveBody(Node* node, ofstream &outputFile, int level) { 
        if (node == NULL) {
            return; 
        }

        inOrderRecursiveBody(node->left, outputFile, ++level); 
        cout << getSpacesFromInt(level) << node->value << ": " << getStringFromSet(node->valuesSet) << "\n";
        outputFile << getSpacesFromInt(level) << node->value << ": " << getStringFromSet(node->valuesSet) << "\n";
        inOrderRecursiveBody(node->right, outputFile, ++level); 
    }

    void Tree::postOrderRecursiveBody(Node* node, ofstream &outputFile, int level) { 
        if (node == NULL) {
            return; 
        }

        postOrderRecursiveBody(node->left, outputFile, ++level); 
        postOrderRecursiveBody(node->right, outputFile, ++level);
        cout << getSpacesFromInt(level) << node->value << ": " << getStringFromSet(node->valuesSet) << "\n";
        outputFile << getSpacesFromInt(level) << node->value << ": " << getStringFromSet(node->valuesSet) << "\n";
    }


    //public:
    void Tree::buildTree(string value) { 
        // cout << "Starting node insert\n";

        if (this->rootNode->value.empty()) {
            this->rootNode->value = value[0];
            this->rootNode->valuesSet.insert(value);
            // cout << "Initilised root node\n";
            return;
        }

        // cout << "Adding new node\n";

        addNodeRecursiveBody(this->rootNode, value);
    }

    void Tree::traversePostorder(ofstream &outputFile) {
        cout << "Starting post order traversal:\n";
        Node *currentNode = this->rootNode;

        if (currentNode->value == ""){
            return;
        }
        
        postOrderRecursiveBody(currentNode, outputFile, 0);
    }

    void Tree::traverseInorder(ofstream &outputFile) {
        cout << "Starting in order traversal:\n";
        Node *currentNode = this->rootNode;

        if (currentNode->value == ""){
            return;
        }

        inOrderRecursiveBody(currentNode, outputFile, 0);
    }

    void Tree::traversePreorder(ofstream &outputFile) {
        cout << "Starting pre order traversal:\n";
        Node *currentNode = this->rootNode;

        if (currentNode->value == ""){
            return;
        }

        preOrderRecursiveBody(currentNode, outputFile, 0);
    }