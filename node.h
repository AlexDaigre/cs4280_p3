#ifndef NODE_H
#define NODE_H
    #include "token.h"

    struct Node {
        const char* nodeType;
        struct token token0;
        struct token token1;
        struct token token2;
        Node* child0;
        Node* child1;
        Node* child2;
        Node* child3;
    };

#endif