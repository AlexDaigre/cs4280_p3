#ifndef NODE_H
#define NODE_H
    #include <set>
    #include <iostream> 
    #include "token.h"

    struct Node {
        char* nodeType;
        struct token token0;
        struct token token1;
        struct token token2;
        Node* node0;
        Node* node1;
        Node* node2;
        Node* node3;
    };

#endif