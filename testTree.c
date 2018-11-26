#include <string>
#include <iostream>
#include <fstream>
#include "node.h"
#include "token.h"
#include "testTree.h"
using namespace std; 

    string getSpacesFromInt(int numberOfSpaces) {
        string spaceString;
        for(int i = 0; i < numberOfSpaces; i ++){
            spaceString = spaceString + " ";
        }
        return spaceString;
    }

    void preOrderRecursiveBody(Node* node, int level) { 
        if (node == NULL) {
            return; 
        }

        cout << getSpacesFromInt(level) << node->nodeType << "\n";
        preOrderRecursiveBody(node->child0, ++level); 
        preOrderRecursiveBody(node->child1, ++level);
        preOrderRecursiveBody(node->child2, ++level); 
        preOrderRecursiveBody(node->child3, ++level);
    } 

    void postOrderRecursiveBody(Node* node, int level) { 
        if (node == NULL) {
            return; 
        }

        postOrderRecursiveBody(node->child0, ++level); 
        postOrderRecursiveBody(node->child1, ++level);
        postOrderRecursiveBody(node->child2, ++level); 
        postOrderRecursiveBody(node->child3, ++level);
        cout << getSpacesFromInt(level) << node->nodeType << "\n";
    }

    void traversePostorder(Node* node) {
        cout << "Starting post order traversal:\n";

        if (node == NULL) {
            return; 
        }
        
        postOrderRecursiveBody(node, 0);
    }

    void traversePreorder(Node* node) {
        cout << "Starting pre order traversal:\n";

        if (node == NULL) {
            return; 
        }

        preOrderRecursiveBody(node, 0);
    }