/*
 * Yang Shi
 * yshi1@andrew.cmu.edu
 */
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <utility>

using namespace std;

/* use BFS to search the path from the the start point to the end point,
 * and currently from the end point to the start point
 */
int biBfs(vector< vector<int> > matrix, int start_x, int start_y, int end_x, int end_y){
    //check if there is a obstacle in the end point
    if(matrix[end_x][end_y] == 1 || matrix[start_x][start_y] == 1)
        return -1;

    //queue for bfs
    queue< pair<int, int> > startSearchQueue;
    queue< pair<int, int> > endSearchQueue;

    int direction[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    startSearchQueue.push(make_pair(start_x, start_y));
    endSearchQueue.push(make_pair(end_x, end_y));

    //record the visited points' distance
    vector< vector<int> > dis1(matrix.size(), vector<int>(matrix[0].size(), -1));
    vector< vector<int> > dis2(matrix.size(), vector<int>(matrix[0].size(), -1));

    dis1[start_x][start_y] = 0;
    dis2[end_x][end_y] = 0;

    while(!startSearchQueue.empty() || !endSearchQueue.empty()){
        //The search direction from the start point
        int x = startSearchQueue.front().first;
        int y = startSearchQueue.front().second;
        startSearchQueue.pop();

        for(int i = 0; i < 4; i++){
            int xx = x + direction[i][0];
            int yy = y + direction[i][1];

            if(xx >= 0 && xx < matrix.size() && yy >= 0 && yy < matrix[0].size()){
                if(matrix[xx][yy] == 0 && dis1[xx][yy] == -1){
                    if(dis2[xx][yy] != -1){
                        //the two direction searches meet
                        return dis1[x][y] + dis2[xx][yy] + 1;
                    }else{
                        dis1[xx][yy] = dis1[x][y] + 1;
                        startSearchQueue.push(make_pair(xx, yy));
                    }
                }
            }
        }

        //The search direction from the end point
        x = endSearchQueue.front().first;
        y = endSearchQueue.front().second;
        endSearchQueue.pop();

        for(int i = 0; i < 4; i++){
            int xx = x + direction[i][0];
            int yy = y + direction[i][1];

            if(xx >= 0 && xx < matrix.size() && yy >= 0 && yy < matrix[0].size()){
                if(matrix[xx][yy] == 0 && dis2[xx][yy] == -1){
                    if(dis1[xx][yy] != -1){
                        //the two direction searches meet
                        return dis2[x][y] + dis1[xx][yy] + 1;
                    }else{
                        dis2[xx][yy] = dis2[x][y] + 1;
                        endSearchQueue.push(make_pair(xx, yy));
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

    cout<<biBfs(matrix, 0, 0, 1, n-1)<<endl;
}
