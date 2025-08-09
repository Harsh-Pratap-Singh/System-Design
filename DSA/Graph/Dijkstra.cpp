#include <bits/stdc++.h>

using namespace std;
vector<int>dijkstra(vector<vector<pair<int,int>>>&adj,int  V, int s){
    vector<int>dis(V,INT_MAX);
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>>pq;
    pq.push({0,s});
    dis[s] = 0;
    while(!pq.empty()){
        int d = pq.top().first;
        int node = pq.top().second;
        pq.pop();
        if(d > dis[node]){
            continue;
        }
        for(auto& it : adj[node]){
            int weight = it.first;
            int adjNode = it.second;
            if(d + weight < dis[adjNode]){
                dis[adjNode] = d + weight;
                pq.push({dis[adjNode], adjNode});
            }
        }
    }
    return dis;

}
