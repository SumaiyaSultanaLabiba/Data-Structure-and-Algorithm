//this is the regular edmonds-karp algorithm
// here we consider a graph with directed, without any antiparallel edges
// also we do not distinguish between forward edge and back edge


#include<iostream>
#include<bits/stdc++.h>
using namespace std;


void BFS(int n, int s, int t, vector<vector<long long int>>& residual_graph, vector<pair<pair<int,int>, long long int>>& augmenting_path)
{
    queue<int> q;
    vector<bool> visited(n+1, false);
    vector<int> parent(n+1, -1);

    q.push(s);
    visited[s]=true;

    while(!q.empty())
    {
        int current=q.front();
        q.pop();
        for(int v=1; v<=n; v++)
        {
            if(residual_graph[current][v]>0 && !visited[v])
            {
                parent[v]=current;
                visited[v]=true;
                q.push(v);
            }
        }
    }

    if(!visited[t]) return;
    int u=parent[t];
    int v=t;
    while(u!=-1)
    {
        augmenting_path.push_back({{u,v}, residual_graph[u][v]});
        v=u;
        u=parent[v];
    }
}



long long int edmonds_karp(int n, int m, int s, int t, vector<vector<long long int>>& graph)
{
    vector<vector<long long int>> residual_graph(n+1, vector<long long int>(n+1, 0));
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
        {
            residual_graph[i][j]=graph[i][j];
        }
    }

    long long int max_flow=0;
    while(true)
    {
      vector<pair<pair<int,int>, long long int>> augmenting_path;
      BFS(n, s, t, residual_graph, augmenting_path);

      if(augmenting_path.size()==0) break;

      long long int min_weight=INT_MAX;
      for(pair<pair<int,int>, long long int> p: augmenting_path)
      {
        if(p.second<min_weight) min_weight=p.second;
      }

      max_flow+=min_weight;
      for(pair<pair<int,int>, long long int> p: augmenting_path)
      {
        int u=p.first.first;
        int v=p.first.second;
        residual_graph[u][v]-=min_weight;
        residual_graph[v][u]+=min_weight;
      }
    }
    return max_flow;
}



int main()
{
    int n, m; // n = number of nodes, m = number of directed edges
    cin>>n>>m;
    int s, t;// s = source, t = sink
    cin>>s>>t;

    vector<vector<long long int>> graph(n+1, vector<long long int>(n+1, 0));//stores the capacity of the (u,v) edge, actually is an adjacency matrix

    for(int i=1; i<=m; i++)
    {
        int u, v;
        long long int w;
        cin>>u>>v>>w;
        graph[u][v]+=w;
    }

    cout<<edmonds_karp(n, m, s, t, graph)<<endl;
    return 0;
}

/*
8 11 1 8
1 2 4
1 3 2
1 4 6
2 5 3
2 6 6
3 6 3
7 3 3
4 7 10
5 8 4
6 8 4
7 8 4

output: 11
*/
