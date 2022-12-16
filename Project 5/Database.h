//
// Created by jacob on 10/22/22.
//

#ifndef PROJECT_2_DATABASE_H
#define PROJECT_2_DATABASE_H
#include <map>
#include "Relation.h"
#include "DatalogProgram.h"
#include "Graph.h"

class Database {
private:
    std::map<std::string, Relation> tables;
    std::vector<Predicate*> schemes;
    std::vector<Predicate*> facts;
    std::vector<Predicate*> queries;
    std::vector<Rule*> rules;
public:
    Database(std::vector<Predicate*> s, std::vector<Predicate*> f, std::vector<Predicate*> q, std::vector<Rule*> r);
    std::string toString();
    void fill();
    std::string evaluate();
    Relation evaluatePredicate(Predicate* p);
    Relation naturalJoin(Relation r1, Relation r2, std::string ID);
    Relation Union(Relation r1, Relation r2, std::string Id);
    Relation disUnion(Relation r1, Relation r2, std::string id);
    std::string evaluateRules(Rule* r);
    std::string runRules();
    Graph populateGraph();
    std::string quickRules();
    };


#endif //PROJECT_2_DATABASE_H
