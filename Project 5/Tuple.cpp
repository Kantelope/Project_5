//
// Created by jacob on 10/22/22.
//

#include "Tuple.h"

std::string Tuple::at(size_t a){
    return values.at(a);
}

void Tuple::pushback(std::string s){
    values.push_back(s);
}

std::string Tuple::toString(){
    std::ostringstream os;
    os << "(";
    for(size_t i = 0; i < values.size(); i++) {
        if (i < values.size() - 1) {
            os << values.at(i) << ",";
        } else {
            os << values.at(i);
        }
    }
    os << ")" << std::endl;
    return os.str();
}