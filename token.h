#ifndef TOKEN_H
#define TOKEN_H

    enum tokenIdEnum {
        eofTk = 1003, 
        idTk = 1000,
        intTk = 1001,
        opDelTk = 1002,
        keywordTK = 1004
    }; 

    char* getTokenName(enum tokenIdEnum newToken);

    char* getTokenDescription(enum tokenIdEnum newToken);

    struct token {
        enum tokenIdEnum tokenId;
        char tokenInstance[9];
        int lineNum;
    };
    
#endif