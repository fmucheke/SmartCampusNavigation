#include "FileUtils.h"
#include <cctype>

std:: string StandardizeName(const std:: string& name){

    size_t start= 0;

    while (start< name.length() && std:: isspace(static_cast<unsigned char>(name[start]))){
        start++;
    }

    size_t end= name.length();

    while (end> start && std:: isspace(static_cast<unsigned char>(name[end-1]))){
        end--;
    }

    std::string result= name.substr(start, end-start);

    for (char& c: result) {

        c= static_cast<char>(std:: toupper(static_cast<unsigned char>(c)));
    }

    return result
}

