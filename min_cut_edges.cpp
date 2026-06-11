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


long long int edmonds_karp(int n, int m, int s, int t, vector<vector<long long int>>& graph, vector<vector<long long int>>& residual_graph)
{
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
      for(auto p: augmenting_path)
      {
        if(p.second<min_weight) min_weight=p.second;
      }

      max_flow+=min_weight;
      for(auto p: augmenting_path)
      {
        int u=p.first.first;
        int v=p.first.second;
        residual_graph[u][v]-=min_weight;
        residual_graph[v][u]+=min_weight;
      }
    }
    return max_flow;
}

// NEW FUNCTION: find min-cut edges
void find_min_cut(int n, int s, vector<vector<long long int>>& graph, vector<vector<long long int>>& residual_graph)
{
    vector<bool> visited(n+1, false);
    queue<int> q;
    q.push(s);
    visited[s]=true;

    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int v=1; v<=n; v++)
        {
            if(residual_graph[u][v]>0 && !visited[v])
            {
                visited[v]=true;
                q.push(v);
            }
        }
    }

    cout<<"Min-cut edges:\n";
    for(int u=1; u<=n; u++)
    {
        for(int v=1; v<=n; v++)
        {
            if(graph[u][v]>0 && visited[u] && !visited[v])
            {
                cout<<u<<" -> "<<v<<"\n";
            }
        }
    }
}

int main()
{
    int n, m; // n = number of nodes, m = number of directed edges
    cin>>n>>m;
    int s, t;// s = source, t = sink
    cin>>s>>t;

    vector<vector<long long int>> graph(n+1, vector<long long int>(n+1, 0));
    vector<vector<long long int>> residual_graph(n+1, vector<long long int>(n+1, 0));

    for(int i=1; i<=m; i++)
    {
        int u, v;
        long long int w;
        cin>>u>>v>>w;
        graph[u][v]+=w;
    }

    long long int max_flow = edmonds_karp(n, m, s, t, graph, residual_graph);
    cout<<"Max Flow: "<<max_flow<<endl;

    find_min_cut(n, s, graph, residual_graph);

    return 0;
}
