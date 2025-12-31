//problem definition: You are given a tree consisting of 'n' nodes. Your task is to determine for each node the sum of the distances from the node to all other nodes
//solve using  direct BFS

#include<iostream>
#include<bits/stdc++.h>
using namespace std;



int main()
{
    int n, m; // n= number of nodes, m= number of edges
    cin>>n>>m;
    vector<vector<int>> adjList(n+1);
    for(int i=1; i<=m; i++)
    {
        int u, v;
        cin>>u>>v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    vector<int> sum_of_distances(n+1, 0);

    //running BFS for 'n' times
    for(int j=1; j<=n; j++)
    {
    int root=j;
    vector<bool> visited(n+1, false);
    vector<int> level(n+1, -1);

    level[root]=0;
    queue<int> q;
    q.push(root);
    visited[root]=true;

    while(!q.empty())
    {
        int current=q.front();
        q.pop();
        
        for(int v: adjList[current])
        {
            if(!visited[v])
            {
                q.push(v);
                level[v]=level[current]+1;
                visited[v]=true;
            }
        }
    }

    for(int i=1; i<=n; i++)
    {
       sum_of_distances[root]+=level[i];
    }
    }

    //printing the result
    for(int i=1; i<=n; i++) 
    {
        cout<<"Node: "<<i<<", Total distance: "<<sum_of_distances[i]<<endl;
    }
    return 0;
}