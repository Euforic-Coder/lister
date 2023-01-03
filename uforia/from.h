#ifndef FROM_H
#define FROM_H

#include <iostream>
#include <vector>
#include <fstream>

std::string from(std::vector<std::string> vec, char seperator = ' '){
    std::string buffer;
    for(unsigned short int i = 0; i < vec.size(); ++i){
        buffer = buffer + seperator + vec[i];
    }
    return buffer;
}

std::vector<std::string> from(std::string s, char delimiter){
    std::vector<std::string> buffer;
    int pos = 0, len;
    for(unsigned short int i = 0; i < s.length(); ++i){
        if(s[i] != delimiter){
            len++;
        }else{
            buffer.push_back(s.substr(pos + 1, len));
            len = 0;
            pos = i;
        }
    }

    if(s[s.length()] != delimiter){
        buffer.push_back(s.substr(pos + 1, len));
    }
    return buffer;
}

std::vector<std::string> from(std::string file, bool lines){
    std::ifstream ifs(file);
    std::string buffer;
    std::vector<std::string> vec;
    if(lines){
        while(std::getline(ifs, buffer)){
            vec.push_back(buffer);
        }
    }else{
        while(ifs >> buffer){
            vec.push_back(buffer);
        }
    }
    return vec;
}

#endif // FROM_H
