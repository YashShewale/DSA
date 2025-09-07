#include<iostream>
#include<bits/stdc++.h>
using namespace std;


class DSU{
    vector<int> rank;
    vector<int> parent;
    vector<int> size;

public: 
    DSU(int n){//n = no. of nodes
        rank.resize(n+1 , 0);
        size.resize(n+1 , 1);
        parent.resize(n+1);

        for(int i=0;i<n;i++){
            parent[i] = i;
        }
    }

    int findpar(int node){
        if(node == parent[node])
            return node;
        
        return parent[node] = findpar(parent[node]);
    }

    void union_by_rank(int u,int v){
        int pu = findpar(u);
        int pv = findpar(v);
        if(pu == pv)return;

        if(rank[pu] > rank[pv]){
            parent[pv] = pu;
        }
        else if(rank[pu] < rank[pv]){
            parent[pu] = pv;
        }
        else{
            parent[pv] = pu;
            rank[pu]++;
        }
    }

    void union_by_size(int u,int v){
        int pu = findpar(u);
        int pv = findpar(v);
        if(pu == pv)return;

        if(rank[pu] > rank[pv]){
            parent[pv] = pu;
            size[pu] += size[pv];
        }
        else{
            parent[pu] = pv;
            size[pv] += size[pu];
        }
    }
};


int main(){
    //code run
    return 0;
}