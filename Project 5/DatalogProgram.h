//
// Created by jacob on 9/27/22.
//

#ifndef PROJECT_2_DATALOGPROGRAM_H
#define PROJECT_2_DATALOGPROGRAM_H
#include "Token.h"
#include <vector>
#include "Predicate.h"
#include "Rule.h"


class DatalogProgram {
private:
    std::vector<Token*> tokens;
    int index;
    bool success;
    int sL;
    int fL;
    int rL;
    int qL;
    bool isScheme;
    bool isFact;
    bool isRule;
    bool isQuery;
    std::string errorMessage;
    std::vector<Predicate*> schemes;
    std::vector<Predicate*> facts;
    std::vector<Rule*> rules;
    std::vector<Predicate*> queries;
    std::vector<std::string> domain;

public:
    DatalogProgram(std::vector<Token*> t);
    ~DatalogProgram();
    void Match(TokenType type);
    void ParseDatalogProgram();
    void ParseSchemeList();
    void ParseScheme();
    void ParseIdList();
    void ParseFactList();
    void ParseFact();
    void ParseStringList();
    void ParseRuleList();
    void ParseRule();
    void ParseHeadPredicate();
    void ParsePredicate();
    void ParsePredicateList();
    void ParseParameterList();
    void ParseParameter();
    void ParseQueryList();
    void ParseQuery();
    void addDomain(Parameter* newP);
    std::string to_string();
    std::vector<Predicate*> returnSchemes(); //this may induce super buggy behavoir
    std::vector<Predicate*> returnFacts();
    std::vector<Predicate*> returnQueries();
    std::vector<Rule*> returnRules();
};


#endif //PROJECT_2_DATALOGPROGRAM_H
