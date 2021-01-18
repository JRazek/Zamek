#include <bits/stdc++.h>

using namespace std;
struct Node{
    const int id;
    unordered_set <Node *> connections;
    int pathFromSource = -1;
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
struct Point{
    int x, y;
    Node * n;
    Point(int x, int y, Node * n):x(x), y(y), n(n){}
};
int main(){
    int sizeX, sizeY, nodesCount, pointsCount;
    int startPointX, startPointY, endPointX, endPointY;

    cin >> sizeX >> sizeY >> nodesCount >> pointsCount;

    cin >> startPointX >> startPointY;
    cin >> endPointX >> endPointY;

   // unordered_map < int, map <int, vector<Node *> > > pointsX; //stands for horizontal placement of points
    //unordered_map < int, map <int, vector<Node *>> > pointsY;

    vector<Node *> nodes;
    vector<Point> points;
    for(int i = 0 ; i < nodesCount; i ++){
        int lowX, lowY, highX, highY;
        cin >> lowX >> lowY >> highX >> highY;
        Node * createdNode = new Node(i);
        createdNode->lowX = lowX; 
        createdNode->lowY = lowY; 
        createdNode->highX = highX; 
        createdNode->highY = highY; 
        points.push_back(Point(lowX, lowY, createdNode));
        points.push_back(Point(lowX, highY, createdNode));
        points.push_back(Point(highX, lowY, createdNode));
        points.push_back(Point(highX, highY, createdNode));

        nodes.push_back(createdNode);
        //cout<<sizeof(points.back());
    }
    
    sort(points.begin(), points.end(), [](const Point p1, const Point p2){
        if(p1.x != p2.x)
            return p1.x < p2.x;
        return p1.y < p2.y;
    });

    unordered_set<int> stack1;//Node id
    list<pair<int, bool>> batch1;//Node id
    for(int i = 0; i < points.size(); i ++){
        Point p = points[i];
        batch1.push_back(pair<int, bool>(p.n->id, false));
        if(i == points.size() - 1 || points[i + 1].y != p.y || points[i + 1].x != p.x){
            for(auto &key : batch1){
                if(stack1.erase(key.first)){
                    key.second = true;
                }
            }
            for(auto &key : batch1){
                if(!key.second){
                    for(auto key2 : stack1){
                        Node * n2 = nodes[key2];
                        n2->connections.insert(nodes[key.first]);
                        nodes[key.first]->connections.insert(n2);
                    }
                    stack1.insert(key.first);
                }
            }
            batch1.clear();
        }
        if(points[i + 1].x != p.x || i == points.size() - 1){
            stack1.clear();
        }
    }

    points.clear();

    Node * startingNode = nullptr;
    Node * endingNode = nullptr;

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

    //brute force O(n^2)
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