#include "token.h"


char* getTokenName(enum tokenIdEnum newToken){
    switch (newToken) {
        case eofTk: return "eofTK";
        case idTk: return "idTk";
        case intTk: return "intTk";
        case opDelTk: return "opDelTk";
        case keywordTK: return "keywordTK";
   }
}

char* getTokenDescription(enum tokenIdEnum newToken){
    switch (newToken) {
        case eofTk: return "End of File Token";
        case idTk: return "Identifier Token";
        case intTk: return "Integer Token";
        case opDelTk: return "Operator and Delimiter Token";
        case keywordTK: return "Keyword Token";
   }
}
