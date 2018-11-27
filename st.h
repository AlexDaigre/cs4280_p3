#ifndef ST_H
#define ST_H

    #include <set> 
    #include "node.h"

    extern std::set <char*> variables;

    void  checkVarsInTree(Node* node);

#endif