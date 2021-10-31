#include <iostream>
#include<vector>
#include <fstream>
#include <float.h>
#include <cmath>
#include <algorithm>

using namespace std;

class Node{
    public: 
        double x;
        double y;
        bool visited;
        vector<pair<int, double> > neighbors;
        Node(double x=0, double y=0, bool visited = false){
            this->x = x;
            this->y = y;
            this->visited = visited;
        }
};

double calcDistance(double x1, double y1, double x2, double y2){

    return sqrt(pow(x2-x1,2) + pow(y2-y1,2) * 1.0);
}

int main(int argc,char*argv[]){
    ifstream myFile(argv[1]);
    if(!myFile.is_open()) throw runtime_error("could not open file");
    
    string line;
    getline(myFile,line);

    vector<Node> nodes;

    int count = stoi(line);
    for(int i=0;i<count;i++){
        getline(myFile,line,' ');
        double x = stod(line);
        getline(myFile,line);
        double y = stod(line);
        nodes.push_back(Node(x, y, false));
    }

    getline(myFile,line);


    count = stoi(line);

    //if m is 0 all nodes have edges with each other
    if(count==0){
        for(int i=0;i<nodes.size();i++){
            for(int j=i+1;j<nodes.size();j++){
                double distance = calcDistance(nodes[i].x, nodes[i].y,nodes[j].x,nodes[j].y);
                nodes[i].neighbors.push_back(make_pair(j,distance));
                nodes[j].neighbors.push_back(make_pair(i,distance));
            }
        }
    }
    else{
        for(int i=0;i<count;i++){
            getline(myFile,line,' ');
            int f = stoi(line);
            getline(myFile,line);
            int s = stoi(line);
            double distance = calcDistance(nodes[f].x, nodes[f].y, nodes[s].x, nodes[s].y);
            nodes[f].neighbors.push_back(make_pair(s,distance));
            nodes[s].neighbors.push_back(make_pair(f,distance));
        }
    }

    vector<pair<int, int> > answer;

    vector<int> vstd;
    vstd.push_back(0);
    nodes[0].visited = true;
    while(vstd.size()<nodes.size()){
        double tempd= DBL_MAX;
        int edge1;
        int edge2;
        for(int i=0;i<vstd.size();i++){
            for(int j=0;j<nodes[vstd[i]].neighbors.size();j++){
                if(nodes[vstd[i]].neighbors[j].second<tempd
                &&nodes[nodes[vstd[i]].neighbors[j].first].visited==false){
                    tempd = nodes[vstd[i]].neighbors[j].second;
                    edge1 = vstd[i];
                    edge2 = nodes[vstd[i]].neighbors[j].first;
                }
            }
        }
        nodes[edge2].visited = true;
        vstd.push_back(edge2);
        if(edge1<edge2) answer.push_back(make_pair(edge1,edge2));
        else answer.push_back(make_pair(edge2,edge1));
    }

    sort(answer.begin(), answer.end(),[](pair<int, int> p1, pair<int, int>p2){
        if(p1.first==p2.first) return p1.second<p2.second;
        return p1.first<p2.first;
    });

    for(int i=0;i<answer.size();i++){
        cout<<answer[i].first<<" "<<answer[i].second<<endl;
    }

    return 0;
}
