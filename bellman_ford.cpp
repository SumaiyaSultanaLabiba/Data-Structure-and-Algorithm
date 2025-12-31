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

    //starting Bellman-Ford
    int root;
    cout<<"Enter the root of Bellman-Ford: ";
    cin>>root;
    
    vector<int> first_dist(n+1, INF);
    vector<int> second_dist(n+1, INF);
    vector<int> parent(n+1, -1);
    first_dist[root]=0;
    second_dist[root]=0;

    for(int i=1; i<=n-1; i++)
    {
        for(int u=1; u<=n; u++)
        {
            for(pair<int, int> p : adjList[u])
            {
                int v=p.first, w=p.second;
                if(first_dist[u]!=INF && first_dist[u]+w < first_dist[v])
                {
                    second_dist[v]=first_dist[u]+w;
                    parent[v]=u;
                }
            }
        }
        for(int k=1; k<=n; k++) first_dist[k]=second_dist[k];
    }


    //checking if there is any negative cycle
    for(int u=1; u<=n; u++)
    {
        for(pair<int, int> p : adjList[u])
        {
            int v=p.first, w=p.second;
            if(first_dist[u]!=INF && first_dist[u]+w < first_dist[v])
            {
                second_dist[v]=first_dist[u]+w;
                parent[v]=u;
            }
        }
    }
    bool is_neg_cycle_present=false;
    int reachable_node_from_neg_cycle=-1;
    for(int i=1; i<=n; i++)
    {
        if(first_dist[i]!= second_dist[i])
        {
            is_neg_cycle_present=true;
            reachable_node_from_neg_cycle=i;
            break;
        }
    }

    //if no negative cycle, print the shortest distances for each node. Otherwise, print the negative cycle
    if(!is_neg_cycle_present)
    {
        for(int i=1; i<=n; i++)
        {
            cout<<"Node: "<<i<<", Distance: "<<first_dist[i]<<endl;
        }
    }
    
    else
    {
      cout<<"Negative cycle detected!!"<<endl;
      int node_inside_cycle=reachable_node_from_neg_cycle;
      for(int i=1; i<=n-2; i++) node_inside_cycle=parent[node_inside_cycle];
      cout<<node_inside_cycle<<" ";
      int first_node=parent[node_inside_cycle];
      while(first_node!=node_inside_cycle)
      {
        cout<<first_node<<" ";
        first_node=parent[first_node];
      }
      cout<<first_node<<endl;
    }
    

    return 0;
}