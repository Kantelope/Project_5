//
// Created by jacob on 10/22/22.
//

#include "Relation.h"

Relation::Relation(std::string n){
    name = n;
}

void Relation::setAttribute(std::string k) {
    attributes.addAttribute(k);
}
void Relation::setHeader(Header h){
    attributes = h;
}
std::string Relation::getHeadAt(size_t a){
    return attributes.at(a);
}

void Relation::addTuple(Tuple t) {
    tuples.insert(t);
}

std::string Relation::toString(){
    std::ostringstream os;
    os << name << "(";
    os << attributes.toString() << ")" << std::endl;
    for(Tuple t : tuples){
        os << t.toString();
    }
    return os.str();
}

Relation Relation::select(size_t index, std::string value) {
    Relation newR = Relation(name);
    newR.setHeader(attributes);
    for(Tuple t : tuples){
        if(t.at(index) == value){
            newR.addTuple(t);
        }
    }
    return newR;
}
Relation Relation::select(size_t index1, size_t index2){
    Relation newR = Relation(name);
    newR.setHeader(attributes);
    for(Tuple t : tuples){
        if(t.at(index1) == t.at(index2)){
            newR.addTuple(t);
        }
    }
    return newR;
}
Relation Relation::project(std::vector<size_t> indices){
    Relation newR = Relation(name);
    for(size_t i = 0; i < indices.size(); ++i){
        newR.setAttribute(attributes.at(indices.at(i)));
    }
    for(Tuple t : tuples){
        Tuple newT;
        for(size_t i = 0; i < indices.size();++i){
            newT.pushback(t.at(indices.at(i)));
        }
        newR.addTuple(newT);
    }
    return newR;
}
Relation Relation::rename(std::vector<std::string> newH){
    Relation newR = Relation(name);
    for(size_t i = 0; i < newH.size(); i++){
        newR.setAttribute(newH.at(i));
    }
    for(Tuple t : tuples){
        newR.addTuple(t);
    }
    return newR;
}
size_t Relation::getTSize(){
    return tuples.size();
}
size_t Relation::getHeadSize(){
    return attributes.size();
}
std::string Relation::altToString(){
    std::ostringstream os;
    if(attributes.size()>0) {
        for (Tuple t: tuples) {
            std::vector<std::string> pastAttributes;
            os << "  ";
            for (size_t i = 0; i < attributes.size(); i++) {
                bool isIn = false;
                for (size_t r = 0; r < pastAttributes.size(); r++){
                    if(attributes.at(i)==pastAttributes.at(r)){
                        isIn = true;
                    }
                }
                if(!isIn) {
                    if (i > 0) {
                        os << ", " << attributes.at(i) << "=" << t.at(i);
                    } else {
                        os << attributes.at(i) << "=" << t.at(i);
                    }
                    pastAttributes.push_back(attributes.at(i));
                }
            }
            os << std::endl;
        }
    }
    return os.str();
}
const std::set<Tuple>& Relation::getTable(){
    return tuples;
}




