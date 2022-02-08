#include<iostream>
#include<string>
#include<vector>
#include<queue>
using namespace std;

// rotting oranges // amazon ========================================================================
vector<vector<int>> dir = {{1,0},{-1,0},{0,1},{0,-1}};
    int orangesRotting(vector<vector<int>>& grid) {
        int time = -1;
        int n = grid.size();
        int m = grid[0].size();
        queue<int> q;

        for(int i=0;i<n;i++){
            for(int j = 0;j<m;j++){
                if(grid[i][j] == 2){     // can store no. of fresh oranges here too;
                    q.push(i*m+j);
                }
            }
        }
        
        // if fresh orange == 0 return 0;
        
        while(!q.empty()){
            int size = q.size();
            while(size-->0){
                int rvtx = q.front();q.pop();
                for(vector<int> & d:dir){
                    int  r = rvtx/m + d[0];
                    int c = rvtx%m + d[1];
                    if(r>=0 && c>= 0 && r<n && c<m && grid[r][c] == 1){
                        grid[r][c] = 0;
                        q.push(r*m+c);   // freshorange -- ; if (freshorange == 0)  return time + 1;
                    }
                }
            }
            time ++;
        }
          
        for(int i=0;i<n;i++){  // if fresh orange != 0 return -1;  // no need to do o(n) loop then ;
            for(int j = 0;j<m;j++){
                if(grid[i][j] == 1){
                    return -1;
                }
            }
        }
        return time ==-1 ? 0 : time;
    }

// lc 1091 ==================================================
int shortestPathBinaryMatrix(vector<vector<int>> &grid)
{
    int n = grid.size();
    if (n == 0)
        return -1;
    int m = grid[0].size();
    if (m == 0)
        return -1;

    if (grid[0][0] == 1 || grid[n - 1][m - 1] == 1)
        return -1;

    int dirA[8][2] = {{-1, -1}, {-1, 0}, {0, -1}, {-1, 1}, {1, -1}, {0, 1}, {1, 0}, {1, 1}};
    queue<int> que;
    que.push(0);
    grid[0][0] = 1;

    int level = 1;
    while (que.size() != 0)
    {
        int size = que.size();
        while (size-- > 0)
        {
            int rvtx = que.front();
            que.pop();

            int r = rvtx / m;
            int c = rvtx % m;

            if (r == n - 1 && c == m - 1)
                return level;

            for (int d = 0; d < 8; d++)
            {
                int x = r + dirA[d][0];
                int y = c + dirA[d][1];

                if (x >= 0 && x < n && y >= 0 && y < m && grid[x][y] == 0)
                {
                    que.push((x * m + y));
                    grid[x][y] = 1;
                }
            }
        }
        level++;
    }

    return -1;
}

// lintcode , leetcode 286 ==========================================
// INF  -1  0  INF
// INF INF INF  -1
// INF  -1 INF  -1
//   0  -1 INF INF
// the answer is:
//   3  -1   0   1
//   2   2   1  -1
//   1  -1   2  -1
//   0  -1   3   4

void wallsAndGates(vector<vector<int>> &grid)
{
    if (grid.size() == 0 || grid[0].size() == 0)
        return;

    int n = grid.size();
    int m = grid[0].size();

    int dirA[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
    queue<int> que;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (grid[i][j] == 0)
                que.push((i * m + j));

    int level = 1;
    while (que.size() != 0)
    {
        int size = que.size();
        while (size-- > 0)
        {
            int rvtx = que.front();
            que.pop();

            int r = rvtx / m;
            int c = rvtx % m;

            for (int d = 0; d < 4; d++)
            {
                int x = r + dirA[d][0];
                int y = c + dirA[d][1];

                if (x >= 0 && x < n && y >= 0 && y < m && grid[x][y] == 2147483647)
                {
                    que.push((x * m + y));
                    grid[x][y] = level;
                }
            }
        }
        level++;
    }
}


 int main(){
     
 }