#include <iostream>
#include <fstream>
#include <sstream>
#include "cyanide-lexer.hpp"

int main(int argc, char *argv[]){
    if(argc < 2){
        std::cout << "cyanide example.cy" << std::endl ;
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
    std::cout << "------------------------" << std::endl ;

    return 0 ;
}