#ifndef NODE_H
#define NODE_H
    #include <set>
    #include <iostream> 
    #include "token.h"

    struct Node {
        struct token thisToken;
        Node *left;
        Node *right;

        // Node() {
        //     this->thisToken = NULL;
        //     this->left = NULL;
        //     this->right = NULL;
        // }
    };

#endif