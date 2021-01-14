#include <bits/stdc++.h>

using namespace std;
struct Node{
    const int id;
    vector<Node *> connections;
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

    for(int i = 0 ; i < nodesCount; i ++){
        int lowX, lowY, highX, highY;
        cin >> lowX >> lowY >> highX >> highY;
        Node * n = new Node(i);

        if(pointsX.find(lowX) == pointsX.end()){
            pointsX[lowX] = map < int, Node * >();
        }

        if(pointsX[lowX].lower_bound(lowX) != pointsX[lowX].end()){
            Node * lowerNode = (*pointsX[lowX].lower_bound(lowX)).second;
            
        }
    }

}