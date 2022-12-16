//
// Created by jacob on 9/27/22.
//

#include "Predicate.h"
Predicate::Predicate(std::string id){
    firstID = id;
}
Predicate::~Predicate(){
    for(size_t i = 0; i < params.size();++i){
        delete params.at(i);
    }
}

void Predicate::addParam(Parameter* p){
    params.push_back(p);
}

std::string Predicate::to_string(){
    std::ostringstream os;
    os << firstID << "(";
    for(size_t i = 0; i < params.size(); i++){
        os << params.at(i)->to_string();
        if (i < params.size()-1){
            os << ",";
        }
    }
    os << ")";
    return os.str();
}

std::string Predicate::returnID(){
    return firstID;
}
size_t Predicate::returnSize(){
    return params.size();
}
std::string Predicate::at(size_t a){
    return params.at(a)->to_string();
}