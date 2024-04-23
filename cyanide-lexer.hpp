#ifndef __LEX_H_
#define __LEX_H_
#include <iostream>

class CyanideLexer{
    private:
        char currentToken ;
        int cursor, srcLen ;
        std::string srcCode ;

    public:
        CyanideLexer(std::string src){
            cursor = 0 ;
            srcCode = src ;
            srcLen = srcCode.length() ;
            currentToken = srcCode.at(cursor) ;
        }
} ;

#endif 