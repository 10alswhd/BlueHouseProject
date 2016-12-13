/*
 * Astart search for the shortest path in a matrix
 * Priority to search to node with minimal euler distance
 *
 * Yang Shi
 * yshi1@andrew.cmu.edu
 */

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <utility>
#include <functional>

using namespace std;

/* Node to store the state of search */
struct Node{
    int x;
    int y;
    int dis;
    int eulerDis;

    Node(int x, int y, int dis, int eulerDis):
        x(x), y(y), dis(dis), eulerDis(eulerDis){};
};


/* Comparer for the two node in the priority queue */
struct comparer{
    bool operator() (const Node& a, const Node& b){
        return a.eulerDis > b.eulerDis;
    }
};


/*
 * Astart search for the shortest path in a matrix
 * Priority to search to node with minimal euler distance
 */
int AstartBfs(vector< vector<int> > matrix, int start_x, int start_y, int end_x, int end_y){
    //check if there is a obstacle in the end point
    if(matrix[end_x][end_y] == 1 || matrix[start_x][start_y] == 1)
        return -1;

    //queue for bfs
    priority_queue< Node, vector<Node>, comparer> searchQueue;

    int direction[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    int eulerDis = (end_y - start_y)*(end_y - start_y) + (end_x - start_x)*(end_x - start_x);
    searchQueue.push(Node(start_x, start_y, 0, eulerDis));

    while(!searchQueue.empty()){
        //get the node with the minimal euler distance to search
        Node node = searchQueue.top();
        searchQueue.pop();

        for(int i = 0; i < 4; i++){
            int xx = node.x + direction[i][0];
            int yy = node.y + direction[i][1];

            if(xx >= 0 && xx < matrix.size() && yy >= 0 && yy < matrix[0].size()){
                if(matrix[xx][yy] == 0){
                    if(xx == end_x && yy == end_y){
                        return node.dis + 1;
                    }else{
                        eulerDis = (end_y - yy)*(end_y - yy)
                                    + (end_x - xx)*(end_x - xx);
                        searchQueue.push(Node(xx, yy, node.dis + 1, eulerDis));
                    }
                }
            }
        }
    }

    return -1;
}

int main(){
    int n;

    cin>>n;

    cout<<n<<endl;

    vector< vector<int> > matrix(n, vector<int>(n, 0));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin>>matrix[i][j];
        }
    }

    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<AstartBfs(matrix, 0, 0, 1, n-1)<<endl;
}
