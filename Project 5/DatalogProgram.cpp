//
// Created by jacob on 9/27/22.
//

#include "DatalogProgram.h"
#include <algorithm>
DatalogProgram::DatalogProgram(std::vector<Token*> t) {
    tokens = t;
    index = 0;
    sL =0;
    fL =0;
    rL =0;
    qL =0;
    isScheme = false;
    isFact = false;
    isRule = false;
    isQuery = false;
    success = true;
}

DatalogProgram::~DatalogProgram() {
    //size_t tokenL = tokens.size();
    size_t schemeL = schemes.size();
    size_t factL = facts.size();
    size_t ruleL = rules.size();
    size_t queriesL = queries.size();
    /* i think i am double freeing this somehow?
    for (size_t i = 0; i < tokenL; i++){
        delete tokens.at(i);
    }
    */
    for (size_t i = 0; i < schemeL; i++){
        delete schemes.at(i);
    }
    for (size_t i = 0; i < factL; i++){
        delete facts.at(i);
    }
    for (size_t i = 0; i < ruleL; i++){
        delete rules.at(i);
    }
    for (size_t i = 0; i <queriesL; i++){
        delete queries.at(i);
    }
}

void DatalogProgram::Match(TokenType type){
    if(!success){
        //do nothing
        ++index;
    }
    else if (tokens[index]->getType() == type){
        ++index;
    }
    else{
        success = false;
        errorMessage = tokens[index]->to_string();
    }
}
void DatalogProgram::ParseDatalogProgram(){
    isScheme = true;
    Match(TokenType::SCHEMES);
    Match(TokenType::COLON);
    ParseScheme();
    ParseSchemeList();
    if(!success){
        return;
    }
    isScheme = false;
    isFact = true;
    Match(TokenType::FACTS);
    Match(TokenType::COLON);
    ParseFactList();
    if(!success){
        return;
    }
    isFact = false;
    isRule = true;
    Match(TokenType::RULES);
    Match(TokenType::COLON);
    ParseRuleList();
    if(!success){
        return;
    }
    isRule = false;
    isQuery = true;
    Match(TokenType::QUERIES);
    Match(TokenType::COLON);
    ParseQuery();
    ParseQueryList();
    if(!success){
        return;
    }
    isScheme = true;
    Match(TokenType::EF);
}
void DatalogProgram::ParseSchemeList(){
    if(tokens[index]->getType() == TokenType::ID){
        ParseScheme();
        ParseSchemeList();
    }
}
void DatalogProgram::ParseScheme(){
    if(tokens[index]->getType() == TokenType::ID){
        Match(TokenType::ID);
        Predicate* newScheme = new Predicate(tokens[index-1]->getString());
        schemes.push_back(newScheme);
        Match(TokenType::LEFT_PAREN);
        Match(TokenType::ID);
        Parameter* newParam = new Parameter(tokens[index-1]->getString());
        schemes.at(sL)->addParam(newParam);
        ParseIdList();
        Match(TokenType::RIGHT_PAREN);
        sL++;
    }
    if(schemes.empty()){
        success = false;
        errorMessage = tokens[index]->to_string();
    }
}
void DatalogProgram::ParseIdList(){
    if(tokens[index]->getType() == TokenType::COMMA) {
        Match(TokenType::COMMA);
        Match(TokenType::ID);
        Parameter* newP = new Parameter(tokens[index-1]->getString());
        if(isScheme){
            schemes.at(sL)->addParam(newP);
        }
        else if(isRule){
            rules.at(rL)->getPred()->addParam(newP);
        }
        ParseIdList();
    }
}
void DatalogProgram::ParseFactList(){
    if(tokens[index]->getType() == TokenType::ID){
        ParseFact();
        ParseFactList();
    }
}
void DatalogProgram::ParseFact(){
    if(tokens[index]->getType() == TokenType::ID){
        Match(TokenType::ID);
        Predicate* newPred = new Predicate(tokens[index-1]->getString());
        facts.push_back(newPred);
        Match(TokenType::LEFT_PAREN);
        Match(TokenType::STRING);
        Parameter* newP = new Parameter(tokens[index-1]->getString());
        facts.at(fL)->addParam(newP);
        addDomain(newP);
        ParseStringList();
        Match(TokenType::RIGHT_PAREN);
        Match(TokenType::PERIOD);
        fL++;
    }
    if(facts.empty()){
        success = false;
        errorMessage = tokens[index]->to_string();
    }
}
void DatalogProgram::ParseStringList(){
    if(tokens[index]->getType() == TokenType::COMMA){
        Match(TokenType::COMMA);
        Match(TokenType::STRING);
        if(success) {
            Parameter *newP = new Parameter(tokens[index - 1]->getString());
            facts.at(fL)->addParam(newP);
            addDomain(newP);
            ParseStringList();
        }
    }
}
//todo add rules
void DatalogProgram::ParseRuleList(){
    if(tokens[index]->getType() == TokenType::ID){
        ParseRule();
        ParseRuleList();
    }
}
void DatalogProgram::ParseRule(){
    if(tokens[index]->getType() == TokenType::ID){
        ParseHeadPredicate();
        Match(TokenType::COLON_DASH);
        ParsePredicate();
        ParsePredicateList();
        Match(TokenType::PERIOD);
        rL++;
    }
    if(rules.empty()){
        success = false;
        errorMessage = tokens[index]->to_string();
    }
}
void DatalogProgram::ParseHeadPredicate(){
    if(tokens[index]->getType() == TokenType::ID){
        Match(TokenType::ID);
        Predicate* newPred = new Predicate(tokens[index-1]->getString());
        Rule* newRule = new Rule(newPred);
        rules.push_back(newRule);
        Match(TokenType::LEFT_PAREN);
        Match(TokenType::ID);
        Parameter* newP = new Parameter(tokens[index-1]->getString());
        rules.at(rL)->getPred()->addParam(newP);
        ParseIdList();
        Match(TokenType::RIGHT_PAREN);
    }
}
void DatalogProgram::ParsePredicate(){
    if(tokens[index]->getType() ==TokenType::ID){
        Match(TokenType::ID);
        Predicate* newPred = new Predicate(tokens[index-1]->getString());
        if(isRule){
            rules.at(rL)->addPred(newPred);
        }
        else if(isQuery){
            queries.push_back(newPred);
        }
        Match(TokenType::LEFT_PAREN);
        ParseParameter();
        ParseParameterList();
        Match(TokenType::RIGHT_PAREN);
    }
}
void DatalogProgram::ParsePredicateList(){
    if(tokens[index]->getType() == TokenType::COMMA){
        Match(TokenType::COMMA);
        ParsePredicate();
        ParsePredicateList();
    }
}
void DatalogProgram::ParseParameterList(){
    if(tokens[index]->getType() == TokenType::COMMA){
        Match(TokenType::COMMA);
        ParseParameter();
        ParseParameterList();
    }
}
void DatalogProgram::ParseParameter(){
    if(tokens[index]->getType() == TokenType::STRING){
        Match(TokenType::STRING);
        Parameter* newParam = new Parameter(tokens[index-1]->getString());
        if(isRule){
            rules.at(rL)->getPred()->addParam(newParam);
        }
        else if (isQuery){
            queries.at(qL)->addParam(newParam);
        }
    }
    else if(tokens[index]->getType() == TokenType::ID){
        Match(TokenType::ID);
        Parameter* newParam = new Parameter(tokens[index-1]->getString());
        if(isRule){
            rules.at(rL)->getPred()->addParam(newParam);
        }
        else if (isQuery){
            queries.at(qL)->addParam(newParam);
        }
    }
}
void DatalogProgram::ParseQueryList(){
    if(tokens[index]->getType() == TokenType::ID){
        ParseQuery();
        ParseQueryList();
    }
}
void DatalogProgram::ParseQuery(){
    if(tokens[index]->getType() == TokenType::ID){
        ParsePredicate();
        Match(TokenType::Q_MARK);
        qL++;
    }
    if(queries.empty()){
        success = false;
        errorMessage = tokens[index]->to_string();
    }
}
void DatalogProgram::addDomain(Parameter *newP) {
    bool isIn = false;
    for (size_t i = 0; i < domain.size(); i++){
        if (domain.at(i) == newP->to_string()) {
            isIn = true;
        }
    }
    if(!isIn){
        domain.push_back(newP->to_string());
    }
}
std::string DatalogProgram::to_string() {
    if(success){
        std::ostringstream os;
        os << "Success!" << std::endl << "Schemes(" << schemes.size() << "):" << std::endl;
        for(size_t i = 0; i< schemes.size(); i++){
            os << "  " << schemes.at(i)->to_string() << std::endl;
        }
        os << "Facts(" << facts.size() << "):" << std::endl;
        for(size_t i = 0; i < facts.size(); i++){
            os << "  " << facts.at(i)->to_string() << "." << std::endl;
        }
        os << "Rules(" << rules.size() << "):" << std::endl;
        for(size_t i = 0; i < rules.size(); i++){
            os << "  " << rules.at(i)->to_string() << "." << std::endl;
        }
        os << "Queries(" << queries.size() << "):" << std::endl;
        for(size_t i = 0; i < queries.size(); ++i){
            os << "  " << queries.at(i)->to_string() << "?" << std::endl;
        }
        os << "Domain(" << domain.size() << "):" << std::endl;
        std::sort(domain.begin(),domain.end());
        for (size_t i = 0; i < domain.size(); i++ ){
            os << domain.at(i) << std::endl;
        }
        return os.str();
    }
    else{
        std::ostringstream os;
        os << "Failure!" << std::endl << errorMessage;
        return os.str();
    }
}

std::vector<Predicate*> DatalogProgram::returnSchemes(){
    return schemes;
}
std::vector<Predicate*> DatalogProgram::returnFacts(){
    return facts;
}
std::vector<Predicate*> DatalogProgram::returnQueries(){
    return queries;
}
std::vector<Rule*> DatalogProgram::returnRules(){
    return rules;
}


