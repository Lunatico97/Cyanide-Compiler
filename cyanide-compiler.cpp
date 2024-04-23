#include <iostream>
#include <fstream>
#include <sstream>
#include "cyanide-lexer.hpp"

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
    
    std::cout << "Source Code: \n" <<  buffer.str() << std::endl ;
    CyanideLexer lexer(buffer.str()) ;
    std::vector<Token*> tokens = lexer.tokenizeCode() ;
    std::cout << "------------------------" << std::endl ;
    for(Token* token : tokens){
        std::cout << token->tokenValue << " -> " << lexer.getType(token->tokenType) << std::endl ; 
    }
    return 0 ;
}