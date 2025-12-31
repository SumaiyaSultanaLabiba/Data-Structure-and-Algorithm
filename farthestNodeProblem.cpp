//problem definition: Can you find two farthest nodes of a graph if it is a tree??


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

    //starting first BFS
    int root1=1;

    vector<bool> visited1(n+1, false);
    vector<int> level1(n+1, -1);

    level1[root1]=0;
    queue<int> q1;
    q1.push(root1);
    visited1[root1]=true;

    while(!q1.empty())
    {
        int current=q1.front();
        q1.pop();
        
        for(int v: adjList[current])
        {
            if(!visited1[v])
            {
                q1.push(v);
                level1[v]=level1[current]+1;
                visited1[v]=true;
            }
        }
    }

    int u=-1;
    int max1=INT_MIN;
    for(int i=1; i<=n; i++)
    {
      if(level1[i]>max1)
      {
        max1=level1[i];
        u=i;
      } 
    }


    //starting second BFS
    int root2=u;

    vector<bool> visited2(n+1, false);
    vector<int> level2(n+1, -1);

    level2[root2]=0;
    queue<int> q2;
    q2.push(root2);
    visited2[root2]=true;

    while(!q2.empty())
    {
        int current=q2.front();
        q2.pop();
        
        for(int v: adjList[current])
        {
            if(!visited2[v])
            {
                q2.push(v);
                level2[v]=level2[current]+1;
                visited2[v]=true;
            }
        }
    }

    int v=-1;
    int max2=INT_MIN;
    for(int i=1; i<=n; i++)
    {
      if(level2[i]>max2)
      {
        max2=level2[i];
        v=i;
      } 
    }

    //printing final results
    cout<<"Two farthest nodes are: ("<<u<<","<<v<<") with diameter: "<<level2[v]<<endl;

    return 0;
}