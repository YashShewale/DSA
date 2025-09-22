#include<iostream>
#include<bits/stdc++.h>
using namespace std;

#define ll long long


//--------------------BFS Approach----------------

  bool isBipartite(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> color(n); // 0: uncolored; 1: color A; -1: color B
        
    queue<int> q; // queue, resusable for BFS    
	
    for (int i = 0; i < n; i++) {
      if (color[i]) continue; // skip already colored nodes
      
      // BFS with seed node i to color neighbors with opposite color
      color[i] = 1; // color seed i to be A (doesn't matter A or B) 
      for (q.push(i); !q.empty(); q.pop()) {
        int cur = q.front();
        for (int neighbor : graph[cur]) 
		{
          if (!color[neighbor]) // if uncolored, color with opposite color
          { color[neighbor] = -color[cur]; q.push(neighbor); } 
		  
          else if (color[neighbor] == color[cur]) 
            return false; // if already colored with same color, can't be bipartite!
        }        
      }
    }
    
    return true;
  }


  //---------------------------DFS Approach--------------------------
  class Solution {
public:

    bool dfs(int node, vector<vector<int>>& graph, vector<int> &vis){
        int n = graph.size();

        bool ret = true;
        for(auto i: graph[node]){
            if(vis[i] == -1 ){
                vis[i] = vis[node]==0?1:0 ;
                ret = ret && dfs(i , graph , vis) ;
                if(ret == false) return false ;
            }


            if(vis[i] == vis[node]) return false;
        }

        return ret;
    }



    bool isBipartite(vector<vector<int>>& graph) {

        int n = graph.size();
        if(n == 1)return true;

        vector<int> vis(n , -1); //0 & 1 - 2 colors
        int i = 0;

        bool ret = true;
        
        for(int j=0;j<n;j++){
            if(graph[j].size() != 0 && vis[j] == -1){
                ret = ret && dfs(j, graph , vis);
                if(ret == false) return false;
            }
        }

        return ret;

    }
};



int main(){
    
    return 0;
}