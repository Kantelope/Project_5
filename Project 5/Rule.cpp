//
// Created by jacob on 9/27/22.
//

#include "Rule.h"
Rule::Rule(Predicate* hp){
    headPred = hp;
}

Rule::~Rule(){
    delete headPred;
    for(size_t i = 0; i < bodyPreds.size(); i++){
        delete bodyPreds.at(i);
    }
}

void Rule::addPred(Predicate* pred){
    bodyPreds.push_back(pred);
}

Predicate* Rule::getPred() {
    if (!bodyPreds.empty()) {
        return bodyPreds.at(bodyPreds.size() - 1);
    }
    else{
        return headPred;
    }
}

Predicate* Rule::getHeadPred(){
    return headPred;
}
std::string Rule::to_string(){
    std::ostringstream os;
    os << headPred->to_string() << " :- ";
    for (size_t i = 0; i < bodyPreds.size(); i++){
        os << bodyPreds.at(i)->to_string();
        if(i < bodyPreds.size()-1){
            os << ",";
        }
    }
    os << ".";
    return os.str();
}

Predicate* Rule::at(size_t n){
    return bodyPreds.at(n);
}
size_t Rule::getSize(){
    return bodyPreds.size();
}

bool Rule::dependsOnSelf(){
    bool r = false;
    for(size_t i = 0; i < bodyPreds.size(); i++){
        if(headPred->returnID() == bodyPreds.at(i)->returnID()){
            r = true;
        }
    }
    return r;
}