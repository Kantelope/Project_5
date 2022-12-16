//
// Created by jacob on 10/22/22.
//

#ifndef PROJECT_3_HEADER_H
#define PROJECT_3_HEADER_H
#include <vector>
#include <string>
#include <sstream>

class Header {
private:
    std::vector<std::string> attributes;
public:
    void addAttribute(std::string s);
    std::string toString();
    std::string at(size_t a);
    size_t size();
};


#endif //PROJECT_3_HEADER_H
