#ifndef MESSAGES_H
#define MESSAGES_H

#include <iostream>
#include <stdlib.h>

void bulletin(std::string s, bool b = true){
    if(b){
        std::cout << "\033[32m • " << s << "\033[m" << std::endl;
    }else{
        std::cout << "\033[31m × " << s << "\033[m" << std::endl;
    }
}

void error(std::string s, bool exit){
    std::cout << "\033[31m" << s << "\033[m" << std::endl;
    if(exit){
        std::abort();
    }
}

#endif // MESSAGES_H
