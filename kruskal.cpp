#include<iostream>
#include<algorithm>
#include<bits/stdc++.h>
using namespace std;


//find operation with path compression
int find(vector<int>& parent, int child)
{
   if(parent[child]==child) return child;
   else
   {
      parent[child]=find(parent, parent[child]);
      return parent[child];
   }
}


int main()
{
    int n, m;//n= number of nodes, m=number of edges
    cin>>n>>m;

    priority_queue<pair<int,pair<int,int>>, vector<pair<int,pair<int,int>>>, greater<pair<int,pair<int,int>>>> pq; //a min-heap to automatically order the edges

    for(int i=0; i<m; i++)
    {
        int u, v, w;
        cin>>u>>v>>w;
        pq.push({w,{u,v}});
    }


    //starting kruskal
    vector<pair<int,int>> edges(m); // list of (u,v) pairs in non-decreasing cost order 
    vector<int> cost(m); // corresponding ordered cost for each edge
    for(int i=0; i<m; i++)
    {
        pair<int,pair<int,int>> p=pq.top();
        pq.pop();
        edges[i]={p.second.first, p.second.second};
        cost[i]=p.first;
    }

    vector<int> parent(n, -1);
    for(int i=0; i<n; i++) parent[i]=i;

    vector<int> rank(n, 0); // height of each subtree rooted at the index node

    vector<pair<int,int>> chosen_edges;
    int total_cost=0;

    for(int i=0; i<m; i++)
    {
        int u, v, w;
        u=edges[i].first;
        v=edges[i].second;
        w=cost[i];

        int parent_u=find(parent,u);
        int parent_v=find(parent,v);

        if(parent_u!=parent_v)
        {
           if(rank[parent_u]>rank[parent_v])
           {
             parent[parent_v]=parent_u;
           } 
           else if(rank[parent_u]<rank[parent_v]) 
           {
             parent[parent_u]=parent_v; 
           }
           else
           {
             parent[parent_v]=parent_u; 
             rank[parent_u]++;
           }
    
           chosen_edges.push_back({u,v});
           total_cost+=w;
        }
    }

    cout<<"Total_weight "<<total_cost<<endl;
    for(pair<int,int> p: chosen_edges)
    {
        cout<<p.first<<" "<<p.second<<endl;
    }
    
    return 0;
}