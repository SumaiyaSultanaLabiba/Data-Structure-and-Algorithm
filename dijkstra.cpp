#include<iostream>
#include<bits/stdc++.h>
using namespace std;


int main()
{
    int n, m; // n= number of nodes, m= number of edges
    cin>>n>>m;
    vector<vector<pair<int, int>>> adjList(n+1);

    for(int i=1; i<=m; i++)
    {
        int u, v, w;// an edge (u,v) with a weight w.
        cin>>u>>v>>w;
        adjList[u].push_back({v,w});
        adjList[v].push_back({u,w});
    }

    //starting Dijkstra
    int root;
    cout<<"Enter the root of Dijkstra: ";
    cin>>root;
    priority_queue<pair<int,int>, vector<pair<int, int>>, greater<pair<int,int>>> not_sure;// stores (distance, node) pairs
    vector<int> shortest_distance(n+1, INF);
    vector<bool> sure(n+1, false);
    shortest_distance[root]=0;
    not_sure.push({0, root});

    while(!not_sure.empty())
    {
        int current_dist=not_sure.top().first;
        int current_node=not_sure.top().second;
        not_sure.pop();
        for(pair<int,int> p: adjList[current_node])
        {
            int v=p.first, w=p.second;
            if(!sure[v] && shortest_distance[v]>shortest_distance[current_node]+w)
            {
                shortest_distance[v]=shortest_distance[current_node]+w;
                not_sure.push({shortest_distance[v], v});
            }
        }
        sure[current_node]=true;
    }

    //printing the shortest distances for all nodes
    for(int i=1; i<=n; i++)
    {
        cout<<"Node: "<<i<<", Distance: "<<shortest_distance[i]<<endl;
    }

    return 0;
}