#include<iostream>
#include<bits/stdc++.h>
using namespace std;

#define ll long long

class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        queue<pair<int,int>> que;
        int m = mat.size();
        int n = mat[0].size();
        vector<vector<int>> ans(m , vector<int> (n , INT_MAX)); 

        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(mat[i][j] == 0){
                    que.push({i,j});
                    ans[i][j] = 0;
                }
            }
        }

        vector<pair<int,int>> dirs = {{1,0},{-1,0},{0,1},{0,-1}};

        while(!que.empty()){
            auto [x,y] = que.front();
            que.pop();

            for(auto [dx,dy]:dirs){
                int i = x+dx;
                int j = y+dy;
                if(i>=0 && i<m && j>=0 && j<n && (ans[i][j] > ans[x][y] + 1)){
                    ans[i][j] = ans[x][y] + 1;
                    que.push({i,j});
                }
            }
        }

        return ans;
    }
};



int main(){
    
    return 0;
}