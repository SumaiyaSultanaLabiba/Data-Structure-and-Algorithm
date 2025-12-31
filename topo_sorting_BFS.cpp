#include<iostream>
#include<bits/stdc++.h>
using namespace std;


int main()
{
    int n, m; // n= number of nodes, m= number of edges
    cin>>n>>m;
    vector<vector<int>> adjList(n+1);
    vector<int> indegree(n+1, 0);
    for(int i=1; i<=m; i++)
    {
        int u, v;
        cin>>u>>v;
        adjList[u].push_back(v);
        indegree[v]++;
    }

    //starting topological sorting
    vector<int> topo_sort;
    queue<int> q;
    for(int u=1; u<=n; u++)
    {
        if(indegree[u]==0) q.push(u);
    }
    while(!q.empty())
    {
        int current=q.front();
        q.pop();
        topo_sort.push_back(current);
        for(int v: adjList[current])
        {
            indegree[v]--;
            if(indegree[v]==0) q.push(v);
        }
    }

    if(topo_sort.size()<n) cout<<"Topological sorting not possible, cycle detected"<<endl;
    else
    {
        for(int v: topo_sort) cout<<v<<" ";
    }
    
    
    return 0;
}