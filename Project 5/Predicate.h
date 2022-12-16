//
// Created by jacob on 9/27/22.
//

#ifndef PROJECT_2_PREDICATE_H
#define PROJECT_2_PREDICATE_H
#include <string>
#include <vector>
#include <sstream>
#include"Parameter.h"

class Predicate {
private:
    std::string firstID;
    std::vector<Parameter*> params;
public:
    Predicate(std::string id);
    ~Predicate();
    void addParam(Parameter* p);
    std::string to_string();
    std::string returnID();
    size_t returnSize();
    std::string at(size_t a);
};


#endif //PROJECT_2_PREDICATE_H
