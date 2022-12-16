//
// Created by jacob on 10/22/22.
//

#ifndef PROJECT_2_TUPLE_H
#define PROJECT_2_TUPLE_H
#include <vector>
#include <string>
#include <sstream>
//todo I need to fix this class
class Tuple {
private:
    std::vector<std::string> values;
public:
    bool operator< (const Tuple &rhs) const {
        return values < rhs.values;
    }
    std::string at(size_t a);
    void pushback(std::string s);
    std::string toString();
};


#endif //PROJECT_2_TUPLE_H
