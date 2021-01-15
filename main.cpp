#include <bits/stdc++.h>

using namespace std;
struct Node{
    const int id;
    unordered_set <Node *> connections;
    int pathFromSource;
    int lowX, lowY, highX, highY;
    Node(int id):id(id){}
};

//each nodes id corresponds to visited arr index
void bfs(Node * start, Node * destination, int nodesCount){
    queue< pair<Node *, Node *> > pq;//node, source

    vector<bool> visited(nodesCount, false);
    pq.push(pair<Node *, Node * > (start, start));

    start->pathFromSource = 0;
    visited[start->id] = true;

    while(!pq.empty()){
        Node * n = pq.front().first;
        Node * comingFrom = pq.front().second;
        for(auto another : n->connections){
            if(another != comingFrom && !visited[another->id]){
                pq.push(pair<Node *, Node *>(another, n));
                another->pathFromSource = n->pathFromSource + 1;
                visited[another->id] = true;
                if(another == destination){
                    return;
                }
            }
        }
        pq.pop();
    }
}
int main(){
    int sizeX, sizeY, nodesCount, pointsCount;
    int startPointX, startPointY, endPointX, endPointY;

    cin >> sizeX >> sizeY >> nodesCount >> pointsCount;

    cin >> startPointX >> startPointY;
    cin >> endPointX >> endPointY;

    /*
        stands for placement of points.
        vector is used as there can be up to 4 rectangles in one point. (case when 4 rectangles have same edge)
        structure is sth like this - 
        unordered map holds the points in X used by rectangles. This provides us up to 2*10^6 points in each of these. 
        There are points in Y asix standing for the point and the Node that it belongs to. 
    */
    unordered_map < int, map <int, vector<Node *> > > pointsX; 
    unordered_map < int, map <int, vector<Node *>> > pointsY; 

    vector<Node *> nodes;
    for(int i = 0 ; i < nodesCount; i ++){
        int lowX, lowY, highX, highY;
        cin >> lowX >> lowY >> highX >> highY;
        Node * createdNode = new Node(i);
        createdNode->lowX = lowX; 
        createdNode->lowY = lowY; 
        createdNode->highX = highX; 
        createdNode->highY = highY; 

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
    
    Node * startingNode = nullptr;
    Node * endingNode = nullptr;

    O(n)
    //assigning startingPoint and endPoint to rectangles
    for(auto n : nodes){
        if(startPointX >= n->lowX && startPointX <= n->highX &&
         startPointY >= n->lowY && startPointY <= n->highY){
             //match
            startingNode = n;
         }
        if(endPointX >= n->lowX && endPointX <= n->highX &&
         endPointY >= n->lowY && endPointY <= n->highY){
             //match
            endingNode = n;
         }
    }

    //brute force O(n^2) assgning points to rectangles
    for(int i = 0; i < pointsCount; i ++){
        int pointX, pointY;
        cin >> pointX >> pointY;
        for(auto it = nodes.begin(); it != nodes.end();++it){
            auto n = *it;
            if(pointX >= n->lowX && pointX <= n->highX 
                && pointY >= n->lowY && pointY <= n->highY){
                //match
                for(auto it = n->connections.begin(); it != n->connections.end();){
                    Node * connected = *it;
                    ++it;
                    connected->connections.erase(n);
                    n->connections.erase(connected);
                }
                break;
            }
        }
    }

    bfs(startingNode, endingNode, nodesCount);
    cout<<endingNode->pathFromSource + 1;
}