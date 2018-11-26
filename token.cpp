#include "token.h"


char* getTokenName(enum tokenIdEnum newToken){
    switch (newToken) {
        case eofTk: return (char*)"eofTK";
        case idTk: return (char*)"idTk";
        case intTk: return (char*)"intTk";
        case opDelTk: return (char*)"opDelTk";
        case keywordTK: return (char*)"keywordTK";
   }
}

char* getTokenDescription(enum tokenIdEnum newToken){
    switch (newToken) {
        case eofTk: return (char*)"End of File Token";
        case idTk: return (char*)"Identifier Token";
        case intTk: return (char*)"Integer Token";
        case opDelTk: return (char*)"Operator and Delimiter Token";
        case keywordTK: return (char*)"Keyword Token";
   }
}
