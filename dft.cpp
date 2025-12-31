#include<iostream>
#include<vector>
using namespace std;



void DFS(vector<vector<int>>& adjList, int root, int& currentTime, vector<int>& startTime, vector<int>& finishTime, vector<bool>& visited, vector<bool>& inProgress, vector<bool>& allDone, vector<int>& parent, int root_parent)
{
    startTime[root]=currentTime;
    parent[root]=root_parent;
    currentTime++;
    visited[root]=true;
    inProgress[root]=true;

    for(int v: adjList[root])
    {
        if(!visited[v])
        {
            DFS(adjList, v, currentTime, startTime, finishTime, visited, inProgress, allDone, parent, root);
        }
    }
    
    inProgress[root]=false;
    finishTime[root]=currentTime++;
    allDone[root]= true;
}



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

    //starting DFS
    int root;
    cout<<"Enter the root of DFS: ";
    cin>>root;
    int currentTime=0;
    vector<int> startTime(n+1);
    vector<int> finishTime(n+1);
    vector<bool> visited(n+1, false);
    vector<bool> inProgress(n+1, false);
    vector<bool> allDone(n+1, false);
    vector<int> parent(n+1, -1);
    int root_parent=-1;
    DFS(adjList, root, currentTime, startTime, finishTime, visited, inProgress, allDone, parent, root_parent);


    //printing the path between any two given nodes, following DFT
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