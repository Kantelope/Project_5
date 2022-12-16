//
// Created by jacob on 9/27/22.
//

#ifndef PROJECT_2_PARAMETER_H
#define PROJECT_2_PARAMETER_H
#include <string>


class Parameter {
private:
    std::string p;
public:
    Parameter(const std::string &input) {p = input;}
    std::string to_string() {return p;}
};


#endif //PROJECT_2_PARAMETER_H
