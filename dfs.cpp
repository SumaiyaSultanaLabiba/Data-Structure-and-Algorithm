#include<iostream>
#include<vector>
using namespace std;



void DFS(vector<vector<int>>& adjList, int root, int& currentTime, vector<int>& startTime, vector<int>& finishTime, vector<bool>& visited, vector<bool>& inProgress, vector<bool>& allDone)
{
    startTime[root]=currentTime;
    currentTime++;
    visited[root]=true;
    inProgress[root]=true;

    for(int v: adjList[root])
    {
        if(!visited[v])
        {
            DFS(adjList, v, currentTime, startTime, finishTime, visited, inProgress, allDone);
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
    DFS(adjList, root, currentTime, startTime, finishTime, visited, inProgress, allDone);


    //checking the start and finish time for each node
    for(int i=1; i<=n; i++)
    {
        cout<<i<<", start: "<<startTime[i]<<", finish: "<<finishTime[i]<<endl;
    }

    return 0;
}