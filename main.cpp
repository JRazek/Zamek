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
        if(p1.y != p2.y)
            return p1.y < p2.y;
        return p1.x < p2.x;
    });
    unordered_set<int> stack2;//Node id
    list<pair<int, bool>> batch2;//Node id
    for(int i = 0; i < points.size(); i ++){
        Point p = points[i];
        batch2.push_back(pair<int, bool>(p.n->id, false));
        if(i == points.size() - 1 || points[i + 1].x != p.x || points[i + 1].y != p.y){
            for(auto &key : batch2){
                if(stack2.erase(key.first)){
                    key.second = true;
                }
            }
            for(auto &key : batch2){
                if(!key.second){
                    for(auto key2 : stack2){
                        Node * n2 = nodes[key2];
                        n2->connections.insert(nodes[key.first]);
                        nodes[key.first]->connections.insert(n2);
                    }
                    stack2.insert(key.first);
                }
            }
            batch2.clear();
        }
        if(points[i + 1].y != p.y || i == points.size() - 1){
            stack2.clear();
        }
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
    
    //sweeping line
    points.clear();

    map<int, vector<Node *> > xNodes;//contains all nodes in this axis. No matter if ending of starting
    for(auto n : nodes){
        if(xNodes.find(n->lowX) != xNodes.end()){
            xNodes[n->lowX] = vector<Node *>();
        }
        if(xNodes.find(n->highX) != xNodes.end()){
            xNodes[n->highX] = vector<Node *>();
        }
        xNodes[n->lowX].push_back(n);
        xNodes[n->highX].push_back(n);
    }
    map<int, vector<int> > dangers;
    for(int i = 0; i < pointsCount; i ++){
        int pointX, pointY;
        cin >> pointX >> pointY;
        if(dangers.find(pointX) == dangers.end()){
            dangers[i] = vector<int>();
        }
        dangers[i].push_back(pointX);
        dangers[i].push_back(pointY);
    }

    map<int, list<Node *>> currLayer;//up to 4 nodes in here. no problem if access is O(4)

    for(auto key : xNodes){
        int x = key.first;
        vector<Node *> * v = &key.second;
        for(auto it1 = v->begin(); it1 != v->end(); ++it1){
            if(x == (*it1)->lowX){
                if(currLayer.find(x) == currLayer.end()){
                    currLayer[x] = list<Node *>();
                }
                currLayer[x].push_back((*it1));
            }
            else{
                list<Node *> * layerNodes = &currLayer[(*it1)->lowY];
                
                for(auto it2 = layerNodes->begin(); it2 != layerNodes->end(); ++it2){
                    if((*it2) == (*it1)){
                        layerNodes->erase(it2);
                        break;
                    }
                }
            }
        }
    }    
    //bfs(startingNode, endingNode, nodesCount);
    //cout<<endingNode->pathFromSource + 1;//

    return 0;
}