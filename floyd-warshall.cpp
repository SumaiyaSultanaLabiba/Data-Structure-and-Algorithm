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
        //adjList[v].push_back({u,w});
    }


    //starting Floyd-Warshall
    vector<vector<int>> D(n+1, vector<int>(n+1, INT_MAX));// D is a 2-D matrix for storing shortest distances between all (u,v) pairs
    vector<vector<int>> next(n+1, vector<int>(n+1, -1));// next is a 2D matrix which each cell (u,v) the next node of u in the shortest path of u->v

    for(int i=1; i<=n; i++) {D[i][i]=0; next[i][i]=i;}
    
    for(int u=1; u<=n; u++)
    {
        for(int j=0; j<adjList[u].size(); j++)
        {
           int v=adjList[u][j].first;
           int w=adjList[u][j].second;
           if(w<D[u][v]) //if there are multiple edges from u->v, take the edge with minimum weight
           {
              D[u][v]=w;
              next[u][v]=v;
           }
        }
    }

    for(int count=1; count<=n; count++)
    {
       for(int i=1; i<=n; i++)
       {
          for(int j=1; j<=n; j++)
          {
            if(D[i][count]!=INT_MAX && D[count][j]!=INT_MAX)
            {
                if(D[i][count]+D[count][j] < D[i][j])
                {
                    D[i][j]= D[i][count]+D[count][j];
                    next[i][j]=next[i][count];
                }
            }
          }
       }
    }

    //checking if there exists any negative weight cycle
    bool neg_cycle_present=false;
    int node_inside_neg_cycle=-1;
    for(int i=1; i<=n; i++)
    {
        if(D[i][i]<0)
        {
            neg_cycle_present=true;
            node_inside_neg_cycle=i;
            break;
        }
    }
    
    if(!neg_cycle_present)
    {
        for(int u=1; u<=n; u++)
        {
           for(int v=1; v<=n; v++)
           {
            cout<<"From "<<u<<" to "<<v<<" shortest distance: "<<D[u][v]<<endl;
           }
        }
    }

    else
    {
        cout<<"Negative cycle detected!!"<<endl;
        int node= node_inside_neg_cycle;
        for(int i=0; i<n; i++) node=next[node][node_inside_neg_cycle];//to ensure that 'node' is actually taking part in a negative cycle formation
        cout<<node<<" ";
        int x=next[node][node];
        while(x!=node)
        {
            cout<<x<<" ";
            x= next[x][node];
        }
        cout<<x<<endl;
    }

    return 0;
}