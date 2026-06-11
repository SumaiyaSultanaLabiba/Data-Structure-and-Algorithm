#include<iostream>
#include<bits/stdc++.h>
using namespace std;



int main()
{
    int n, m;//n= number of nodes, m=number of edges
    cin>>n>>m;

    vector<vector<pair<int, int>>> adjList(n);//stores all input edges
    
    for(int i=0; i<m; i++)
    {
        int u, v, w;
        cin>>u>>v>>w;
        adjList[u].push_back({v,w});
        adjList[v].push_back({u,w});
    }

    int root=0;
    cin>>root;

    //starting prim
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> not_visited;// a min-heap to store all nodes with their keys like (key,node) pair
    vector<pair<int,int>> chosen_edges;
    vector<bool> visited(n, false);
    vector<int> keys(n, INT_MAX);
    vector<int> parent(n, -1);
    not_visited.push({0, root});
    keys[root]=0;
    parent[root]=root;
    int total_cost=0;

    while(!not_visited.empty())
    {
      pair<int,int> current=not_visited.top();
      not_visited.pop();
      int u=current.second;
      if(visited[u]) continue;

      for(pair<int,int> p: adjList[u])
      {
        int v,w;
        v=p.first;
        w=p.second;

        if(!visited[v] && keys[v]>w)
        {
        keys[v]=w;
        parent[v]=u;
        not_visited.push({keys[v],v});
        }
      }

      visited[u]=true;
      if(u!=root)
      {
        chosen_edges.push_back({parent[u], u});
        total_cost+=keys[u];
      }
    }

    cout<<"Total_weight "<<total_cost<<endl;
    cout<<"Root node "<<root<<endl;
    for(pair<int,int> p: chosen_edges)
    {
        cout<<p.first<<" "<<p.second<<endl;
    }

    if(count(visited.begin(), visited.end(), false)!=0)
    {
        cout<<"Graph is disconnected, partial MST can be built with the above listed edges"<<endl;
    }
    
    return 0;
}