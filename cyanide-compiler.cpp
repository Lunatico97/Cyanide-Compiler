#include <iostream>
#include <fstream>
#include <sstream>
#include "cyanide-lexer.hpp"
#include "cyanide-parser.hpp"

int main(int argc, char *argv[]){
    if(argc < 2){
        std::cerr << "cyanide example.cy" << std::endl ;
        exit(1) ;
    }

    std::cout << "Input: " << argv[1] << std::endl ;
    std::ifstream fileStr(argv[1]) ;
    std::stringstream buffer ;
    char temp ;

    while(fileStr.get(temp)){
        buffer << temp ;
    }
    std::cout << "------------------------" << std::endl ;
    std::cout << "Source Code: \n" <<  buffer.str() << std::endl ;
    CyanideLexer lexer(buffer.str()) ;
    std::vector<Token*> tokens = lexer.tokenizeCode() ;
    std::cout << "------------------------" << std::endl ;
    if(tokens.back()->tokenType != TOKEN_EOF){
        Token *token = new Token ;
        token->tokenType == TOKEN_EOF ;
        tokens.push_back(token) ;
    }
    std::cout << "Token Types: " << std::endl ;
    for(Token* token : tokens){
        std::cout << token->tokenValue << " -> " << lexer.getType(token->tokenType) << std::endl ; 
    }
    std::cout << "------------------------" << std::endl ;
    CyanideParser parser(tokens) ;
    Node* ace = parser.parseTree() ;
    std::cout << "No. of statements: " << ace->subTree.size() << std::endl ;
    return 0 ;
}