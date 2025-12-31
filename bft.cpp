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
    vector<int> parent(n+1, -1);

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
                parent[v]=current;
                visited[v]=true;
            }
        }
    }

    
    //printing the path between any two given nodes, following BFT
    int source, destination;
    cout<<"Enter the source node:";
    cin>>source;
    cout<<"Enter the destination node:";
    cin>>destination;

    vector<int> source_lineage;
    vector<int> destination_lineage;
    int a=source, b=destination;
    while(a!=-1)
    {
        source_lineage.push_back(a);
        a=parent[a];
    }
    while(b!=-1)
    {
        destination_lineage.push_back(b);
        b=parent[b];
    }

    int common_parent=-1; 
    for(int i=0; i<source_lineage.size(); i++)
    {
        for(int j=0; j<destination_lineage.size(); j++)
        {
            if(source_lineage[i]==destination_lineage[j])
            {
                common_parent=source_lineage[i];
                break;
            }
        }
        if(common_parent!=-1) break;
    }

    //after the above two layered loop, if the common_parent is still -1, then destination is not reachable from node. Otherwise reachable
    if(common_parent==-1) cout<<"Destination is not reachable from Source"<<endl;
    else{
        int i=0;
        while(source_lineage[i]!=common_parent)
        {
            cout<<source_lineage[i++]<<" ";
        }
        for(int i=destination_lineage.size()-1; i>=0; i--)
        {
            if(destination_lineage[i]==common_parent)

            {
                while(i>=0)
                {
                    cout<<destination_lineage[i--]<<" ";
                }
                break;
            }
        }
    }
    return 0;
}