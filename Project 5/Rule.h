//
// Created by jacob on 9/27/22.
//

#ifndef PROJECT_2_RULE_H
#define PROJECT_2_RULE_H
#include "Predicate.h"
#include <vector>

class Rule {
private:
    Predicate* headPred;
    std::vector<Predicate*> bodyPreds;
public:
    Rule(Predicate* hp);
    ~Rule();
    void addPred(Predicate* pred);
    std::string to_string();
    Predicate* getPred();
    Predicate* at(size_t n);
    size_t getSize();
    Predicate* getHeadPred();
    bool dependsOnSelf();
};


#endif //PROJECT_2_RULE_H
