#ifndef _PARSER_H_
#define _PARSER_H_

#include "cyanide-lexer.hpp"

enum ntype{
    NODE_ID, NODE_INT, NODE_ACE, NODE_PEEK, NODE_RET
} ;

// Parse Tree Node
struct Node{
    enum ntype nodeType ;
    std::string *value ;
    Node *child ;
    std::vector<Node*> subTree ;
} ;

class CyanideParser{
    private:
        int limit, index ;
        Token *currentToken ;
        std::vector<Token*> tokenHolder ;

    public:
        CyanideParser(std::vector<Token*> tokens){
            index = 0 ;
            tokenHolder = tokens ;
            limit = tokens.size() ;
            currentToken = tokenHolder.at(index) ;
        }

        Token* proceed(enum type ctype){
            if(currentToken->tokenType != ctype){
                std::cout << "Syntax Error !!!" << std::endl ;
                exit(1) ;
            }
            else{
                index += 1 ;
                currentToken = tokenHolder.at(index) ;
                return currentToken ;
            }
        }

        Node *parseInt(){
            if(currentToken->tokenType != TOKEN_INT){
                std::cout << "Syntax Error !!!" << std::endl ;
                exit(1) ;
            }
            Node *newNode = new Node ;
            newNode->value = &currentToken->tokenValue ;
            newNode->nodeType = NODE_INT ;
            proceed(TOKEN_INT) ;
            return newNode ;
        }

        Node *parseID(){
            std::string *buffer = &currentToken->tokenValue ;
            proceed(TOKEN_ID) ;
            proceed(TOKEN_ASGN) ;
            Node *newNode = new Node() ;
            newNode->nodeType = NODE_ID ;
            newNode->child = parseInt() ;
            return newNode ;
        }

        Node* parseRet(){
            proceed(TOKEN_KW) ;
            Node *newNode = new Node() ;
            newNode->nodeType = NODE_RET ;
            newNode->child = parseInt() ;
            return newNode ;
        }

        Node* parsePeek(){
            proceed(TOKEN_KW) ;
            Node *newNode = new Node() ;
            newNode->nodeType = NODE_PEEK ;
            proceed(TOKEN_LP) ;
            newNode->child = parseInt() ;
            proceed(TOKEN_RP) ;
            return newNode ;
        }

        Node *parseKW(){
            if(currentToken->tokenValue == "ret"){
                return parseRet() ;
            }
            else if(currentToken->tokenValue == "peek"){
                return parsePeek() ;
            }
            else{
                std::cout << "Syntax Error - Undefined keyword !!!" << std::endl ;
                exit(1) ;
            }
        }

        Node* parseTree(){
            Node* ace = new Node() ;
            ace->nodeType = NODE_ACE ;
            while(currentToken->tokenType != TOKEN_EOF){
                switch (currentToken->tokenType)
                {
                    case TOKEN_ID:
                        ace->subTree.push_back(parseID()) ;
                        break ;

                    case TOKEN_KW:
                        ace->subTree.push_back(parseKW()) ;
                        break ;
                    
                    default:
                        std::cout << "Syntax Error !!!" << std::endl ;
                        exit(1) ;
                        break;
                }
                proceed(TOKEN_SCLN) ;
            }
            return ace ;
        }
} ;

#endif