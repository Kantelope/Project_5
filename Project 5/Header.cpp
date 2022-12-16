//
// Created by jacob on 10/22/22.
//

#include "Header.h"

void Header::addAttribute(std::string s) {
    attributes.push_back(s);
}
std::string Header::at(size_t a){
    return attributes.at(a);
}
size_t Header::size(){
    return attributes.size();
}

std::string Header::toString() {
    std::ostringstream os;
    for (size_t i; i < attributes.size(); ++i){
        if(i < attributes.size()-1){
            os << attributes.at(i) << ",";
        }
        else{
            os << attributes.at(i);
        }
    }
    return os.str();
}