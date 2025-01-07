#include<bits/stdc++.h>
using namespace std;

class DisjoinSet{
    private: 
        vector<int>rank,parent,size;
    
    public:
        DisjoinSet(int n){
            rank.resize(n+1,0);
            parent.resize(n+1);
            size.resize(n+1,1);
            for(int i = 0;i <= n;i ++){
                parent[i] = i;
            }
        }
        int findUp(int node){
            if(node == parent[node]){
                return node;
            }
            return parent[node] = findUp(parent[node]);
        }

        void unionByRank(int u, int v){
            int u_up = findUp(u);
            int v_up = findUp(v);
            if(rank[u_up] < rank[v_up]){
                parent[u_up] = v_up;
            }
            else if(rank[u_up] > rank[v_up]){
                parent[v_up] = u_up;
            }
            else{
                parent[u_up] = v_up;
                rank[v_up] ++;
            }
        }
        void unionBySize(int u, int v){
            int u_up = findUp(u);
            int v_up = findUp(v);
            if(u_up <  v_up){
                parent[u_up] = v_up;
                size[v_up] += size[u_up];
            }
            else{
                parent[v_up] = u_up;
                size[u_up] += size[v_up];
            }

        }
        bool isComponent(int v , int u){
            return findUp(v) == findUp(u);
        }
};