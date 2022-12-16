//
// Created by jacob on 12/1/22.
//

#include "Graph.h"

Graph::Graph(size_t a){
    amount = a;
}
void Graph::addEdge(size_t i, size_t e){
    edges[i].emplace(e);
}

std::string Graph::toString(){
    std::ostringstream os;
    for(size_t i = 0; i < amount; i++){
        os << "R" << i << ":";
        size_t j = 0;
        for(size_t val: edges[i]){
            if (j < edges[i].size()-1){
                os << "R" << val << ",";
                j++;
            }
            else{
                os << "R" << val;
            }
        }
        os << std::endl;
    }
    return os.str();
}

Graph Graph::returnReverse(){
    Graph newGraph(amount);
    for(size_t i = 0; i <edges.size(); i++){
        for(size_t val: edges[i]){
            newGraph.addEdge(val,i);
        }
    }
    return newGraph;
}

void Graph::DFS(size_t pos){
    visited[pos] = true;
    for(size_t val : edges[pos]){
        if(!visited[val]){
            DFS(val);
        }
    }
    pOrder.push_back(pos);
}

void Graph::DFSForest(std::vector<size_t> order){
    markUnvisited();
    for(size_t i = 0; i < order.size();i++){
        if(!visited[order[i]]){
            DFS(order[i]);
            scc.push_back(pOrder);
            pOrder.clear();
        }
    }
    fillPostOrder();
    for(size_t i = 0; i < scc.size(); i++){
        sort(scc.at(i).begin(),scc.at(i).end());
    }

}

void Graph::markUnvisited(){
    for(size_t i = 0; i < amount; i++){
        visited[i] = false;
    }
}
void Graph::fillPostOrder() {
    for (size_t i = 0; i < scc.size(); i++){
        for (size_t j = 0; j < scc.at(i).size(); j++) {
            postOrder.push_back(scc.at(i).at(j));
        }
    }
}

std::vector<size_t> Graph::reversePost(){
    std::vector<size_t> newVector = postOrder;
    std::reverse(newVector.begin(),newVector.end());
    return newVector;
}

size_t Graph::size(){
    return amount;
}

std::vector<std::vector<size_t>> Graph::get_scc(){
    return scc;
}
