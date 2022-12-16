//
// Created by jacob on 10/22/22.
//

#ifndef PROJECT_2_RELATION_H
#define PROJECT_2_RELATION_H
#include "Tuple.h"
#include "Header.h"
#include <set>

class Relation {
private:
    std::string name;
    Header attributes;
    std::set<Tuple> tuples;
public:
    Relation(std::string n);
    void setHeader(Header h);
    std::string getHeadAt(size_t a);
    void setAttribute(std::string k);
    void addTuple(Tuple t);
    std::string toString();
    Relation select(size_t index, std::string value);
    Relation select(size_t index1, size_t index2);
    Relation project(std::vector<size_t> indices);
    Relation rename(std::vector<std::string> newH);
    size_t getTSize();
    size_t getHeadSize();
    std::string altToString();
    const std::set<Tuple>& getTable();
};


#endif //PROJECT_2_RELATION_H
