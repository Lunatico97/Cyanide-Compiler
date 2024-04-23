#ifndef __LEX_H_
#define __LEX_H_
#include <iostream>
#include <sstream>
#include <vector>

enum type{
    TOKEN_ID, TOKEN_INT, TOKEN_ASGN, TOKEN_SCLN, TOKEN_LP, TOKEN_RP
} ;

struct Token{
    enum type tokenType ;
    std::string tokenValue ;
} ;

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

        char getNextToken(){
            if(cursor < srcLen){
                char temp = currentToken ;
                cursor += 1 ;
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
            }
            return "invalid" ;
        }

        // Convert source code to tokens
        Token* tokenizeIdentifier(){
            std::stringstream buffer ;
            while(isalnum(currentToken) || currentToken == '_'){
                buffer << getNextToken() ;
            }
            Token *newToken = new Token() ;
            newToken->tokenType = TOKEN_ID ;
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
                    tokens.push_back(tokenizeIdentifier()) ;
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

                        default:
                            std::cerr << "Foreign token alert !" << std::endl ;
                            exit(1) ;
                            break ;
                        
                    }
                }
            }
            return tokens ;
        }
} ;

#endif 