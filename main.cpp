#include <bits/stdc++.h>

using namespace std;
struct Node{
    const int id;
    unordered_set <Node *> connections;
    Node(int id):id(id){}
};

int main(){
    int sizeX, sizeY, nodesCount, pointsCount;
    int startPointX, startPointY, endPointX, endPointY;

    cin >> sizeX >> sizeY >> nodesCount >> pointsCount;

    cin >> startPointX >> startPointY;
    cin >> endPointX >> endPointY;

    unordered_map < int, map <int, vector<Node *> > > pointsX; //stands for horizontal placement of points
    unordered_map < int, map <int, vector<Node *>> > pointsY;

    vector<Node *> nodes;
    for(int i = 0 ; i < nodesCount; i ++){
        int lowX, lowY, highX, highY;
        cin >> lowX >> lowY >> highX >> highY;
        Node * createdNode = new Node(i);



//lowX stuff
        if(pointsX.find(lowX) == pointsX.end()){
            pointsX[lowX] = map < int, vector<Node *> >();
        }
        if(pointsX[lowX].find(lowY) == pointsX[lowX].end()){
            pointsX[lowX][lowY] = vector<Node *> ();
        }
        if(pointsX[lowX].find(highY) == pointsX[lowX].end()){
            pointsX[lowX][highY] = vector<Node *> ();
        }
        pointsX[lowX][lowY].push_back(createdNode);
        pointsX[lowX][highY].push_back(createdNode);

//highX stuff
        if(pointsX.find(highX) == pointsX.end()){
            pointsX[highX] = map < int, vector<Node *> >();
        }
        if(pointsX[highX].find(lowY) == pointsX[lowX].end()){
            pointsX[highX][lowY] = vector<Node *> ();
        }
        if(pointsX[highX].find(highY) == pointsX[lowX].end()){
            pointsX[highX][highY] = vector<Node *> ();
        }
        pointsX[highX][lowY].push_back(createdNode);
        pointsX[highX][highY].push_back(createdNode);
        
//lowY stuff
        if(pointsY.find(lowY) == pointsY.end()){
            pointsY[lowY] = map < int, vector<Node *> >();
        }
        if(pointsY[lowY].find(lowX) == pointsY[lowY].end()){
            pointsY[lowY][lowX] = vector<Node *> ();
        }
        if(pointsY[lowY].find(highX) == pointsY[lowY].end()){
            pointsY[lowY][highX] = vector<Node *> ();
        }
        pointsY[lowY][lowX].push_back(createdNode);
        pointsY[lowY][highX].push_back(createdNode);

//highY stuff
        if(pointsY.find(highY) == pointsY.end()){
            pointsY[highY] = map < int, vector<Node *> >();
        }
        if(pointsY[highY].find(lowX) == pointsY[highY].end()){
            pointsY[highY][lowX] = vector<Node *> ();
        }
        if(pointsY[highY].find(highX) == pointsY[highY].end()){
            pointsY[highY][highX] = vector<Node *> ();
        }
        pointsY[highY][lowX].push_back(createdNode);
        pointsY[highY][highX].push_back(createdNode);


        nodes.push_back(createdNode);

        cout<<"";
        
    }
    for(auto it = pointsX.begin(); it != pointsX.end(); ++it){
        unordered_set <Node *> nodesOnStack;
        for(auto it2 = (*it).second.begin(); it2 != (*it).second.end(); ++it2){
            vector<Node *> * nodesVector = &(*it2).second;//up to 4 nodes per point
            for(auto it3 = nodesVector->begin(); it3 != nodesVector->end(); ++it3){
                Node * n = (*it3);
                if(!nodesOnStack.erase(n)){
                    for(auto it4 = nodesOnStack.begin(); it4 != nodesOnStack.end(); ++it4){
                        Node * ns = *it4;
                        n->connections.insert(ns);
                        ns->connections.insert(n);
                    }
                    nodesOnStack.insert(n);
                }
            }
        }
    }
    for(auto it = pointsY.begin(); it != pointsY.end(); ++it){
        unordered_set <Node *> nodesOnStack;
        for(auto it2 = (*it).second.begin(); it2 != (*it).second.end(); ++it2){
            vector<Node *> * nodesVector = &(*it2).second;//up to 4 nodes per point
            for(auto it3 = nodesVector->begin(); it3 != nodesVector->end(); ++it3){
                Node * n = (*it3);
                if(!nodesOnStack.erase(n)){
                    for(auto it4 = nodesOnStack.begin(); it4 != nodesOnStack.end(); ++it4){
                        Node * ns = *it4;
                        n->connections.insert(ns);
                        ns->connections.insert(n);
                    }
                    nodesOnStack.insert(n);
                }
            }
        }
    }
    /*
        if(pointsY.find(lowY) == pointsY.end()){
            pointsY[lowY] = map < int, Node * >();
        }
        if(pointsY.find(highY) == pointsY.end()){
            pointsY[highY] = map < int, Node * >();
        }
    */
        cout<<"";
}