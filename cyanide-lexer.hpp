#ifndef __LEX_H_
#define __LEX_H_
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

enum type{
    TOKEN_ID, TOKEN_INT, TOKEN_EOF, TOKEN_ASGN, TOKEN_SCLN, TOKEN_LP, TOKEN_RP, TOKEN_KW
} ;

struct Token{
    enum type tokenType ;
    std::string tokenValue ;
} ;

class CyanideLexer{
    private:
        char currentToken ;
        std::string srcCode ;
        int cursor, lineNum, charNum, srcLen ;
        std::vector<std::string> keywords = {"peek"} ;

    public:
        CyanideLexer(std::string src){
            cursor = 0 ;
            lineNum = 1 ;
            charNum = 1 ;
            srcCode = src ;
            srcLen = srcCode.length() ;
            currentToken = srcCode.at(cursor) ;
        }

        char getNextToken(){
            if(cursor < srcLen){
                char temp = currentToken ;
                cursor += 1 ;
                charNum += 1 ;
                currentToken = srcCode[cursor] ;
                return temp ;
            }
            else{
                // currentToken = '\0' ;
                return '\0' ;
            }
        }

        char peak(int offset = 0){
            if((cursor + offset) < srcLen)
                return srcCode[cursor+offset] ;
            else    
                return '\0' ;
        }

        void skipDelimiters(){
            bool skip = false ;
            char delims[4] = {' ', '\n', '\t', '\r'} ; 
            while(true){
                for(char& delim : delims){
                    if(currentToken == delim){
                        skip = true ;
                        break ;
                    }
                }
                if(skip){
                    if(currentToken == '\n'){
                        lineNum += 1 ;
                        charNum = 1 ;
                    }
                    getNextToken() ;
                    skip = false ;
                }
                else break ;
            }
        }

        std::string getType(enum type token){
            switch(token){
                case TOKEN_ID:
                    return "identifier" ;
                
                case TOKEN_INT:
                    return "integer" ;

                case TOKEN_SCLN:
                    return "termination" ;

                case TOKEN_ASGN:
                    return "assignment" ;

                case TOKEN_LP:
                    return "left-bracket" ;

                case TOKEN_RP:
                    return "right-bracket" ;

                case TOKEN_KW:
                    return "keyword" ;
            }
            return "invalid" ;
        }

        // Convert source code to tokens
        Token* tokenizeLangTokens(){
            std::stringstream buffer ;
            while(isalnum(currentToken) || currentToken == '_'){
                buffer << getNextToken() ;
            }
            Token *newToken = new Token() ;
            newToken->tokenType = (std::find(keywords.begin(), keywords.end(), buffer.str()) != keywords.end()) ? TOKEN_KW : TOKEN_ID ;
            newToken->tokenValue = buffer.str() ;
            return newToken ;
        }

        Token* tokenizeInteger(){
            std::stringstream buffer ;
            while(isdigit(currentToken)){
                buffer << getNextToken() ;
            }
            Token *newToken = new Token() ;
            newToken->tokenType = TOKEN_INT ;
            newToken->tokenValue = buffer.str() ;
            return newToken ;
        }

        Token* tokenizeUnique(enum type unique){
            Token *newToken = new Token() ;
            newToken->tokenType = unique ;
            newToken->tokenValue = std::string(1, getNextToken()) ;
            return newToken ;
        }

        std::vector<Token*> tokenizeCode(){
            std::vector<Token*> tokens ;
            Token *tempToken ;
            bool eof = false ;
            while(cursor < srcLen && !eof){
                skipDelimiters() ;
                if(isalpha(currentToken)){
                    tokens.push_back(tokenizeLangTokens()) ;
                }
                else if(isdigit(currentToken)){
                    tokens.push_back(tokenizeInteger()) ;
                }
                else{
                    switch(currentToken){
                        case ';':
                            tokens.push_back(tokenizeUnique(TOKEN_SCLN)) ;
                            break ; 

                        case ':':
                            tokens.push_back(tokenizeUnique(TOKEN_ASGN)) ;
                            break ;

                        case '(':
                            tokens.push_back(tokenizeUnique(TOKEN_LP)) ;
                            break ;

                        case ')':
                            tokens.push_back(tokenizeUnique(TOKEN_RP)) ;
                            break ;
                        
                        case '\0':
                            tokens.push_back(tokenizeUnique(TOKEN_EOF)) ;
                            break ;

                        default:
                            std::cerr << "!!! Foreign token alert -> [" << currentToken << "] !!! " ;
                            std::cerr << "< Check: Line " << lineNum << " (" << charNum << ") >" << std::endl ; 
                            exit(1) ;
                            break ;
                        
                    }
                }
            }
            return tokens ;
        }
} ;

#endif 