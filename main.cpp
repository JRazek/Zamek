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

    unordered_map < int, map <int, Node *> > pointsX; //stands for horizontal placement of points
    unordered_map < int, map <int, Node *> > pointsY;

    vector<Node *> nodes;
    for(int i = 0 ; i < nodesCount; i ++){
        int lowX, lowY, highX, highY;
        cin >> lowX >> lowY >> highX >> highY;
        Node * createdNode = new Node(i);



//lowX stuff

        if(pointsX.find(lowX) == pointsX.end()){
            pointsX[lowX] = map < int, Node * >();
        }
        if(pointsX.find(highX) == pointsX.end()){
            pointsX[highX] = map < int, Node * >();
        }

        pointsX[lowX][lowY] = createdNode;
        pointsX[lowX][highY] = createdNode;

//highX stuff



        pointsX[highX][lowY] = createdNode;
        pointsX[highX][highY] = createdNode;

        nodes.push_back(createdNode);

        cout<<"";
        
    }
    /*
        if(pointsY.find(lowY) == pointsY.end()){
            pointsY[lowY] = map < int, Node * >();
        }
        if(pointsY.find(highY) == pointsY.end()){
            pointsY[highY] = map < int, Node * >();
        }
    */
}