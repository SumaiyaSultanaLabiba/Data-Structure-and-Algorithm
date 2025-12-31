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

    //starting BFS
    int root;
    cout<<"Enter the root of BFS: ";
    cin>>root;

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

    //printing level of each node
    for(int i=1; i<=n; i++)
    {
        cout<<"Node: "<<i<<", level: "<<level[i]<<endl;
    }
    return 0;
}