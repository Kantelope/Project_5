//
// Created by jacob on 10/22/22.
//

#include "Database.h"

Database::Database(std::vector<Predicate*> s, std::vector<Predicate*> f,std::vector<Predicate*> q, std::vector<Rule*> r){
    schemes = s;
    facts = f;
    queries = q;
    rules = r;
}

void Database::fill() {
    //std::vector<Predicate*> schemes = dp.returnSchemes();
    //std::vector<Predicate*> facts = dp.returnFacts();
    for(size_t i = 0; i < schemes.size();++i){
        std::string id = schemes.at(i)->returnID();
        Relation newR =  Relation(id);
        for(size_t f = 0; f < schemes.at(i)->returnSize(); ++f){
            newR.setAttribute(schemes.at(i)->at(f));
        }
        tables.insert({id,newR});
    }
    for(size_t i = 0; i < facts.size();++i){
        std::string id = facts.at(i)->returnID();
        Tuple t;
        for(size_t f = 0; f < facts.at(i)->returnSize(); ++f){
            t.pushback(facts.at(i)->at(f));
        }
        tables.at(id).addTuple(t);
    }
}

std::string Database::toString(){
    std::ostringstream os;
    for (auto& [key, val] : tables) //consider alternate iterator
    {
        os << val.toString() << std::endl;
    }
    return os.str();
}
Relation Database::evaluatePredicate(Predicate* p){ // should be exact same as evaluate just don't return a string
        std::string name = p->returnID();
        Relation WorkingR = tables.at(name);
        std::string param;
        std::vector<std::string> paramList;
        std::vector<size_t> indexList;
        for(size_t f = 0; f <p->returnSize();++f) {
            param = p->at(f);
            if (param[0] == '\'') {
                WorkingR = WorkingR.select(f, p->at(f));
            } else {
                std::vector<std::string> newHeader;
                for(size_t z = 0; z < WorkingR.getHeadSize(); z++){
                    if(z!=f){
                        newHeader.push_back(WorkingR.getHeadAt(z));
                    }
                    else{
                        newHeader.push_back(param);
                    }
                }
                WorkingR=WorkingR.rename(newHeader);
                for (size_t j = 0; j < paramList.size(); j++) {
                    if (param == paramList.at(j)) {
                        WorkingR = WorkingR.select(indexList.at(j), f);
                    }
                }
                paramList.push_back(param); // this won't work when x = x
                indexList.push_back(f);
            }
        }
        if(WorkingR.getTSize() != 0){
            WorkingR = WorkingR.project(indexList);
        }
    return WorkingR;
}

std::string Database::evaluate(){
    std::ostringstream os;
    os << "Query Evaluation" << std::endl;
    for(size_t i = 0; i < queries.size(); ++i){
        std::string name = queries.at(i)->returnID();
        Relation WorkingR = tables.at(name);
        std::string param;
        std::vector<std::string> paramList;
        std::vector<size_t> indexList;
        for(size_t f = 0; f <queries.at(i)->returnSize();++f) {
            param = queries.at(i)->at(f);
            if (param[0] == '\'') {
                WorkingR = WorkingR.select(f, queries.at(i)->at(f));
            } else {
                std::vector<std::string> newHeader;
                for(size_t z = 0; z < WorkingR.getHeadSize(); z++){
                    if(z!=f){
                        newHeader.push_back(WorkingR.getHeadAt(z));
                    }
                    else{
                        newHeader.push_back(param);
                    }
                }
                WorkingR=WorkingR.rename(newHeader);
                for (size_t j = 0; j < paramList.size(); j++) {
                    if (param == paramList.at(j)) {
                        WorkingR = WorkingR.select(indexList.at(j), f);
                    }
                }
                paramList.push_back(param); // this won't work when x = x
                indexList.push_back(f);
            }
        }
        if(WorkingR.getTSize() != 0){
        os << queries.at(i)->to_string() << "? Yes(" << WorkingR.getTSize() << ")" << std::endl;
        WorkingR = WorkingR.project(indexList);
        os << WorkingR.altToString();
        }
        else{
            os << queries.at(i)->to_string() << "? No" << std::endl;
        }
    }
    return os.str();
}

Relation Database::naturalJoin(Relation r1, Relation r2, std::string ID){
    std::vector<std::pair<size_t,size_t>> commons;
    for(size_t i = 0 ; i < r1.getHeadSize(); i++  ){
        for(size_t j = 0; j < r2.getHeadSize(); j++){
            if (r1.getHeadAt(i) == r2.getHeadAt(j)){
                commons.push_back(std::make_pair(i,j));
            }
        }
    }
    Header newHead;
    for(size_t i = 0; i < r1.getHeadSize(); i++  ){
        newHead.addAttribute(r1.getHeadAt(i));
    }
    std::vector<size_t> addindex;
    for(size_t j = 0; j < r2.getHeadSize(); j++){
        bool isAlreadyIn = false;
        for(size_t k = 0; k < newHead.size(); k++){
            if(r2.getHeadAt(j) == newHead.at(k)){
                isAlreadyIn = true;
            }
        }
        if(!isAlreadyIn) {
            newHead.addAttribute(r2.getHeadAt(j));
            addindex.push_back(j);
        }
    }

    Relation workingR(ID);
    workingR.setHeader(newHead);
    if(commons.empty()){
        const std::set<Tuple> table1 = r1.getTable();
        const std::set<Tuple> table2 = r2.getTable();
        for(Tuple tab1 : table1){
            for(Tuple tab2 : table2){
                Tuple newTup;
                for(size_t q = 0; q < r1.getHeadSize();++q){
                    newTup.pushback(tab1.at(q));
                }
                for(size_t q = 0; q < r2.getHeadSize();++q){
                    newTup.pushback(tab2.at(q));
                }
                workingR.addTuple(newTup);
                }
            }
    }
    const std::set<Tuple> table1 = r1.getTable();
    const std::set<Tuple> table2 = r2.getTable();
    for(Tuple tab1 : table1) {
        for (Tuple tab2: table2) {
            bool isMatch = true;
            for (size_t c = 0; c < commons.size(); ++c) {
                if (!(tab1.at(commons.at(c).first) == tab2.at(commons.at(c).second))) {
                    isMatch = false;
                }
            }
            if (isMatch) {
                Tuple newTup;
                for (size_t q = 0; q < r1.getHeadSize(); ++q) {
                    newTup.pushback(tab1.at(q));
                }
                for (size_t q = 0; q < addindex.size(); ++q) {
                    newTup.pushback(tab2.at(addindex.at(q)));
                }
                workingR.addTuple(newTup);
            }
        }
    }
    return workingR;
}
Relation Database::Union(Relation r1, Relation r2, std::string Id){
    const std::set<Tuple> table2 = r2.getTable();
    std::vector<size_t> locations;
    for(size_t i = 0; i <r1.getHeadSize();i++){
        for(size_t j = 0; j < r2.getHeadSize();j++){
            if(r1.getHeadAt(i)==r2.getHeadAt(j)){
                locations.push_back(j);
            }
        }
    }
    for(Tuple tab2 : table2){
        Tuple newTup;
        for(size_t i = 0; i < locations.size(); i++){
            newTup.pushback(tab2.at(locations.at(i)));
        }
        r1.addTuple(newTup);
    }
    return r1;
}

Relation Database::disUnion(Relation r1, Relation r2, std::string id){
    Relation workingR(id);
    Header newHead;
    for(size_t i = 0; i < r1.getHeadSize(); i++  ){
        newHead.addAttribute(r1.getHeadAt(i));
    }
    workingR.setHeader(newHead);
    const std::set<Tuple> table1 = r1.getTable();
    const std::set<Tuple> table2 = r2.getTable();
    for(Tuple tab1 : table1){
        bool isIn = false;
        for(Tuple tab2 : table2) {
            if(!((tab1 < tab2)||(tab2 <tab1))){
                isIn = true;
            }
        }
        if(!isIn){
            workingR.addTuple(tab1);
        }
    }
    return workingR;
}

std::string Database::evaluateRules(Rule* R) {
    std::ostringstream os;
    Relation lhs = evaluatePredicate(R->at(0));
    if (R->getSize()>1) {
        for (size_t j = 1; j < R->getSize(); j++) {
            lhs = naturalJoin(lhs, evaluatePredicate(R->at(j)),"temp");
        }
    }
    std::vector<std::size_t> newHeadr;

    for(size_t j = 0; j< R->getHeadPred()->returnSize();j++) {
        for(size_t k = 0; k< lhs.getHeadSize();k++){
            if (R->getHeadPred()->at(j) == lhs.getHeadAt(k)) {
                newHeadr.push_back(k);
            }
        }
    }
    std::vector<std::string> oldHeadr;
    Relation head = evaluatePredicate(R->getHeadPred());
    for(size_t del = 0; del < tables.at(R->getHeadPred()->returnID()).getHeadSize();del++){
        oldHeadr.push_back(tables.at(R->getHeadPred()->returnID()).getHeadAt(del));
    }
    lhs = lhs.project(newHeadr);
    Relation altlhs = lhs;
    lhs = lhs.rename(oldHeadr);
    Relation outlhs = disUnion(lhs,head,R->getHeadPred()->returnID());
    os << outlhs.altToString();
    lhs = Union(head,altlhs,R->getHeadPred()->returnID());
    lhs = lhs.rename(oldHeadr);
    tables.at(R->getHeadPred()->returnID()) = lhs;
    return os.str();
}

std::string Database::runRules(){
    std::ostringstream os;
    os << "Rule Evaluation" << std::endl;
    std::vector<std::string> previous;
    std::string current;
    size_t currentRuns=1;
    bool isNotSame = true;
    for(size_t i = 0; i < rules.size(); ++i){
        previous.push_back(evaluateRules(rules.at(i)));
        os << rules.at(i)->to_string()<<std::endl;
        os << previous.at(i);
    }
    while(isNotSame){
        isNotSame = false;
        for(size_t i = 0; i < rules.size();i++ ) {
            current = evaluateRules(rules.at(i));
            if ("" != current){
                os << rules.at(i)->to_string()<<std::endl;
                isNotSame = true;
                previous.at(i) = current;
                os << current;
            }
            else{
                os << rules.at(i)->to_string()<<std::endl;
            }
        }
    ++currentRuns;
    }
    os << std::endl << "Schemes populated after " << currentRuns << " passes through the Rules." << std::endl << std::endl;
    return os.str();
}

Graph Database::populateGraph(){
    Graph newGraph(rules.size());
    for(size_t i = 0; i < rules.size(); i++){
        for(size_t j = 0; j <rules.at(i)->getSize(); j++){
            for(size_t k = 0; k < rules.size(); k++){
                if(rules.at(i)->at(j)->returnID() == rules.at(k)->getHeadPred()->returnID()){
                    newGraph.addEdge(i,k);
                }
            }
        }
    }
    return newGraph;
}

std::string Database::quickRules() {
    std::ostringstream os;
    os << "Dependency Graph" << std::endl;
    Graph fGraph = populateGraph();
    os << fGraph.toString();
    Graph rGraph = fGraph.returnReverse();
    std::vector<size_t> order;
    for(size_t i = 0; i < fGraph.size(); i++){
        order.push_back(i);
    }
    rGraph.DFSForest(order);
    order = rGraph.reversePost();
    fGraph.DFSForest(order);
    std::vector<std::vector<size_t>> scc = fGraph.get_scc();
    os << std::endl << "Rule Evaluation" << std::endl;
    //todo I am currently evaluating the rules wrong basically if
    for(size_t i = 0; i <scc.size();i++){
        os << "SCC: ";
        std::vector<Rule*> subRules;
        for(size_t j = 0; j <scc.at(i).size(); j++){
            if ( j < scc.at(i).size() -1){
                os << "R" << scc.at(i).at(j) << ",";
            }
            else{
                os << "R" << scc.at(i).at(j);
            }
            subRules.push_back(rules.at(scc.at(i).at(j)));
        }
        bool dependent = false;
        for(size_t z = 0; z < subRules.size();++z){
            if(subRules.at(z)->dependsOnSelf()){
                dependent = true;
            }
        }
        os << std::endl;
        if((subRules.size() < 2) && (!dependent)){
            os << subRules.at(0)->to_string() << std::endl;
            os << evaluateRules(subRules.at(0));
            os << "1 passes: R" << scc.at(i).at(0);
        }
        else {
            std::vector<std::string> previous;
            std::string current;
            size_t currentRuns = 1;
            bool isNotSame = true;
            for (size_t z = 0; z < subRules.size(); ++z) {
                previous.push_back(evaluateRules(subRules.at(z)));
                os << subRules.at(z)->to_string() << std::endl;
                os << previous.at(z);
            }
            while (isNotSame) {
                isNotSame = false;
                for (size_t x = 0; x < subRules.size(); x++) {
                    current = evaluateRules(subRules.at(x));
                    if ("" != current) {
                        os << subRules.at(x)->to_string() << std::endl;
                        isNotSame = true;
                        previous.at(x) = current;
                        os << current;
                    }
                    else {
                            os << subRules.at(x)->to_string() << std::endl;
                    }
                }
                ++currentRuns;
            }
            os << currentRuns << " passes: ";
            for (size_t j = 0; j < scc.at(i).size(); j++) {
                if (j < scc.at(i).size() - 1) {
                    os << "R" << scc.at(i).at(j) << ",";
                } else {
                    os << "R" << scc.at(i).at(j);
                }
            }
        }
        os << std::endl;
    }
    os << std::endl;
    return os.str();
}


