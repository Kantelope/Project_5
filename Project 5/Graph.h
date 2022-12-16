//
// Created by jacob on 12/1/22.
//

#ifndef PROJECT_5_GRAPH_H
#define PROJECT_5_GRAPH_H
#include <map>
#include <set>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>


class Graph {
private:
    std::map<size_t,std::set<size_t>> edges;
    std::map<size_t,bool> visited;
    std::vector<size_t> postOrder;
    std::vector<std::vector<size_t>> scc;
    std::vector<size_t> pOrder;
    size_t amount;
public:
    Graph(size_t a);
    void addEdge(size_t i, size_t e);
    std::string toString();
    Graph returnReverse();
    void DFS(size_t pos);
    void DFSForest(std::vector<size_t> order);
    void fillPostOrder();
    std::vector<size_t> reversePost();
    size_t size();
    std::vector<std::vector<size_t>> get_scc();
    void markUnvisited();
};


#endif //PROJECT_5_GRAPH_H
