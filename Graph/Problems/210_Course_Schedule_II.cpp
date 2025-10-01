#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// -------------------soln 1 (my soln with improvements)  --------------------------
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {

        int n = prerequisites.size();
        vector<int> ans;
        //-------------indegree can be implemented----------
        vector<vector<int>> parent(numCourses);

        vector<vector<int>> child(numCourses);

        for (int i = 0; i < n; i++) {
            int a = prerequisites[i][0];
            int b = prerequisites[i][1];

            parent[a].push_back(b);
            child[b].push_back(a);
        }


        //----------------if indegree implemented no need of this inefficient code----
        vector<bool> vis(numCourses, 0);
        vector<bool> pushed(numCourses, 0);
        int visited = numCourses;
        auto isparentvis = [&](int ele) -> bool {
            for (int i = 0; i < parent[ele].size(); i++) {
                if (!vis[parent[ele][i]])
                    return false;
            }

            return true;
        };


        queue<int> que;

        for (int i = 0; i < numCourses; i++) {
            if (parent[i].size() == 0)
                que.push(i), pushed[i] = 1;
        }


        while (!que.empty()) {
            //-----------------This can also be removed if use indegree-----
            int sz = que.size();
            int ele;
            while (sz) {
                ele = que.front();
                que.pop();
                if (isparentvis(ele))
                    break;
                que.push(ele);
                sz--;
            }
            if (!sz) {
                // see how to return empty set w/o defining
                // ans = {};
                return {};
            }



            visited--;
            vis[ele] = 1;
            ans.push_back(ele);

            for (int i = 0; i < child[ele].size(); i++) {
                int ch = child[ele][i];
                if (!pushed[ch])
                    que.push(ch), pushed[ch] = 1;
            }
        }

        if (ans.size() == numCourses)
            return ans;

        return {};
    }
};


/*-----------------------------------------------------------------------------------------------------------------------------------------------------*/


//-----------------Efficient Soln -(BFS) Kahn's Algorithm---------------
/* 
Kahn’s Algorithm (Topo Sort):

Compute indegree of all nodes.

Put all nodes with indegree = 0 into a queue.

Repeatedly pop from queue → add to order → reduce indegree of its neighbors → if neighbor’s indegree = 0, push into queue.

Continue until queue is empty.

If all nodes processed → valid topo order, else cycle exists.

👉 Time: O(V+E)
👉 Space: O(V+E)
 */

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        int n = numCourses;
        vector<vector<int>>  adj(n);
        vector<int> indegree(n),topol;
        int u,v;
        for(auto&p:prerequisites){
            u = p[0], v = p[1];
            adj[v].push_back(u);
            indegree[u]++;
        }
        deque<int> q;
        for(int i=0;i<n;i++){
            if(indegree[i]==0)q.push_back(i);
        }

        while(!q.empty()){
            auto node = q.front();
            topol.push_back(node);
            q.pop_front();

            for(auto&nei:adj[node]){
                indegree[nei]--;
                if(!indegree[nei]){
                    q.push_back(nei);
                }
            }
        }

        if(topol.size() < n)return {};

        // reverse(topol.begin(),topol.end());
        return topol;

    }
};





/*-----------------------------------------------------------------------------------------------------------------------------------------------------*/

//------------------------------------------DFS Soln---------------------------------
/* 
- Basically here what we are doing calling rec for 'a' node and then recursively calling their childs
    (i.e the node dependent on a). And Before calling them recursively we set todo[a] = 1. Why?
    to detect cycle if really cycle is there then a will again recursively get called and 
    cycle get detected

- Also, why here we make order in reverse and reversed it?
    because if we push before rec call it will create mess 
    E.g. if c want a & b prereq (i.e. a->c , b->c)
        correct way - a called, order=[] => c called, order=[c] => a backtrack, order=[c,a]
                     b called, order=[c,a] => c called -> done true (no effect on order) => b backtrack,order=[c,a,b]

        wrong way - a called, order=[a] => c called, order=[a,c] 
                    b called, order=[a,c,b]
                    SO, HERE ORDER GET WRONG B IS AFTER C

 */
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        graph g = buildGraph(numCourses, prerequisites);
        vector<int> order;
        vector<bool> todo(numCourses, false), done(numCourses, false);
        for (int i = 0; i < numCourses; i++) {
            if (!done[i] && !acyclic(g, todo, done, i, order)) {
                return {};
            }
        }
        reverse(order.begin(), order.end());
        return order;
    }
private:
    typedef vector<vector<int>> graph;
    
    graph buildGraph(int numCourses, vector<pair<int, int>>& prerequisites) {
        graph g(numCourses);
        for (auto p : prerequisites) {
            g[p.second].push_back(p.first);
        }
        return g;
    }
    
    bool acyclic(graph& g, vector<bool>& todo, vector<bool>& done, int node, vector<int>& order) {
        if (todo[node]) {
            return false;
        }
        if (done[node]) {
            return true;
        }
        todo[node] = done[node] = true;
        for (int neigh : g[node]) {
            if (!acyclic(g, todo, done, neigh, order)) {
                return false;
            }
        }
        order.push_back(node);
        todo[node] = false;
        return true;
    }
};



